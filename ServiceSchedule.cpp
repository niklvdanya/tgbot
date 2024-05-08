#include <string>
#include "ServiceSchedule.h"
#include <iostream>
#include <boost/locale.hpp>

std::string convertToUtf8(const std::string& data, const std::string& from_charset) {
    return boost::locale::conv::to_utf<char>(data, from_charset);
}

std::string url_encode(CURL* curl, const std::string& str) {
    char* output = curl_easy_escape(curl, str.c_str(), str.length());
    std::string encoded(output);
    curl_free(output);
    return encoded;
}

std::string ServiceSchedule::getSchedule(std::string groupId) 
{
    std::string url = "https://timetable.spbu.ru/api/v1/groups/" + groupId + "/events";
    auto js_obj = nlohmann::json::parse(httpClient.get_request(url));
    std::string schedule_info = "";
    for (int i = 0; i < js_obj["Days"].size(); i++)
    {
        schedule_info += js_obj["Days"][i]["DayString"].get<std::string>() + "\n";
        for (int j = 0; j < js_obj["Days"][i]["DayStudyEvents"].size(); j++)
        {
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["Subject"].get<std::string>() + "\n";
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["TimeIntervalString"].get<std::string>() + "\n";
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["EducatorsDisplayText"].get<std::string>() + "\n\n";
        }
        schedule_info += "------------------------------------------\n";
    }
    return schedule_info;
}


std::vector<Faculty> ServiceSchedule::getFaculties()
{
    std::vector<Faculty> faculties;
    auto facultiesJson = nlohmann::json::parse(httpClient.get_request("https://timetable.spbu.ru/api/v1/study/divisions"));
    for (const auto& facultyJson : facultiesJson)
    {
        std::string name = facultyJson["Name"].get<std::string>();
        std::string alias = facultyJson["Alias"].get<std::string>();
        faculties.emplace_back(alias, name);
    }

    return faculties;
}

std::vector<Level> ServiceSchedule::getLevelsForFaculty(const std::string& facultyAlias)
{
    std::vector<Level> levels;
    std::string apiUrl = "https://timetable.spbu.ru/api/v1/study/divisions/" + facultyAlias + "/programs/levels";
    auto levelsJson = nlohmann::json::parse(httpClient.get_request(apiUrl));
    levels.reserve(levelsJson.size());
     for (std::size_t i = 0; i < levelsJson.size(); ++i)
    {
        const auto& levelJson = levelsJson[i];

        std::string name = (levelJson["StudyLevelName"].get<std::string>());
        levels.emplace_back(i, name);
    }
    return levels;
}

std::vector<Program> ServiceSchedule::getPrograms(const std::string& facultyAlias, int levelId)
{
    std::vector<Program> programs;
    std::string url = "https://timetable.spbu.ru/api/v1/study/divisions/" + facultyAlias + "/programs/levels";
    
    auto levelsJson = nlohmann::json::parse(httpClient.get_request(url));

    if (levelId >= 0 && levelId < levelsJson.size()) 
    {

        const auto& levelJson = levelsJson[levelId];
        const auto& programsJson = levelJson["StudyProgramCombinations"];
        programs.reserve(programsJson.size());
        for (int i = 0; i < programsJson.size(); i++)
        {
            std::string name = programsJson[i]["Name"].get<std::string>();
            programs.emplace_back(i, name);
        }
    }

    return programs;
}

std::vector<Program> ServiceSchedule::getProgramYears(const std::string& facultyAlias, int levelId, int programId) {
    std::vector<Program> programs;
    std::string url = "https://timetable.spbu.ru/api/v1/study/divisions/" + facultyAlias + "/programs/levels";
    auto levelsJson = nlohmann::json::parse(httpClient.get_request(url));
    if (levelId >= 0 && levelId < levelsJson.size()) 
    {

        const auto& levelJson = levelsJson[levelId]; 
        const auto& programsJson = levelJson["StudyProgramCombinations"];

        if (programId >= 0 && programId < programsJson.size()) 
        {
            const auto& programJson = programsJson[programId]; 
            const auto& admissionYears = programJson["AdmissionYears"]; 
            programs.reserve(admissionYears.size());
            for (const auto& year : admissionYears) 
            {
                std::string yearName = year["YearName"].get<std::string>();
                int studyProgramId = year["StudyProgramId"].get<int>(); 
                programs.emplace_back(yearName, std::to_string(studyProgramId));
            }
        }
    }
    return programs;
}

std::vector<Group> ServiceSchedule::getGroups(std::string programId)
{
    std::vector<Group> groups;
    std::string url = "https://timetable.spbu.ru/api/v1/programs/" + programId + "/groups";
    const auto & levelsJson = nlohmann::json::parse(httpClient.get_request(url));
    const auto & groupsJson = levelsJson["Groups"];
    groups.reserve(groupsJson.size());
    for (const auto & group : groupsJson) 
    {
        std::string groupName = group["StudentGroupName"].get<std::string>();
        int groupId = group["StudentGroupId"].get<int>();
        groups.emplace_back(groupId, groupName);

    }
    return groups;
}

std::vector<Teacher> ServiceSchedule::getTeachersByLastName(const std::string& lastName) {
    std::vector<Teacher> teachers;
    CURL* curl = curl_easy_init();
    std::string encodedLastName = url_encode(curl, lastName);
    std::string url = "https://timetable.spbu.ru/api/v1/educators/search/" + encodedLastName;
    auto response = nlohmann::json::parse(httpClient.get_request(url));
    for (const auto& item : response["Educators"]) {
        auto id = item["Id"].get<int>();
        auto fullName = item["FullName"].get<std::string>();
        fullName += '\n';
        for (const auto& employment : item["Employments"]) {
            fullName += employment["Position"].get<std::string>() + " - " + employment["Department"].get<std::string>() + "\n";
        }
        teachers.emplace_back(id, fullName);
    }
    curl_easy_cleanup(curl);
    return teachers;
}

std::string formatEventDates(const nlohmann::json& dates) {
    std::string formattedDates;
    for (const auto& date : dates) {
        formattedDates += date.get<std::string>() + ", ";
    }
    if (!formattedDates.empty()) {
        formattedDates.pop_back();  
        formattedDates.pop_back(); 
    }
    return formattedDates;
}

Teacher ServiceSchedule::getTeacher(const std::string& id) {
    std::string url = "https://timetable.spbu.ru/api/v1/educators/" + id + "/events";
    std::string responseStr = httpClient.get_request(url);
    auto response = nlohmann::json::parse(responseStr);

    int teacherId = std::stoi(id);
    std::string fullName = response["EducatorLongDisplayText"].get<std::string>();
    std::vector<std::string> scheduleDays;

    for (const auto& day : response["EducatorEventsDays"]) {
        std::string dayInfo = day["DayString"].get<std::string>() + ":\n";
        bool hasEvents = false;

        for (const auto& event : day["DayStudyEvents"]) {
            hasEvents = true;
            dayInfo += "  - " + event["Subject"].get<std::string>() + ", "
                       + event["TimeIntervalString"].get<std::string>() + "\n"
                       + "    Даты: " + formatEventDates(event["Dates"]) + "\n"
                       + "    Место: " + event["EventLocations"][0]["DisplayName"].get<std::string>() + "\n"
                       + "    Группа: " + event["ContingentUnitNames"][0]["Item1"].get<std::string>() + "\n";
        }

        if (!hasEvents) {
            dayInfo += "  Нет запланированных занятий.\n";
        }

        scheduleDays.push_back(dayInfo);
    }

    return Teacher(teacherId, fullName, scheduleDays);
}