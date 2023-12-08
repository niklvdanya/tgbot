#include <string>
#include "ServiceSchedule.h"
#include <iostream>
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
        Faculty faculty(alias, name);

        faculties.push_back(faculty);
    }

    return faculties;
}

std::vector<Level> ServiceSchedule::getLevelsForFaculty(const std::string& facultyAlias)
{
    std::vector<Level> levels;
    std::string apiUrl = "https://timetable.spbu.ru/api/v1/study/divisions/" + facultyAlias + "/programs/levels";
    auto levelsJson = nlohmann::json::parse(httpClient.get_request(apiUrl));

     for (std::size_t i = 0; i < levelsJson.size(); ++i)
    {
        const auto& levelJson = levelsJson[i];

        std::string name = (levelJson["StudyLevelName"].get<std::string>());
        Level level(i, name);
        levels.push_back(level);
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
        for (int i = 0; i < programsJson.size(); i++)
        {
            std::string name = programsJson[i]["Name"].get<std::string>();
            Program program(i, name);

            programs.push_back(program);
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
            for (const auto& year : admissionYears) 
            {
                std::string yearName = year["YearName"].get<std::string>();
                int studyProgramId = year["StudyProgramId"].get<int>(); 
                programs.emplace_back(yearName, studyProgramId);
            }
        }
    }
    return programs;
}

std::vector<Group> ServiceSchedule::getGroups(std::string programId){
    std::vector<Group> groups;
    std::string url = "https://timetable.spbu.ru/api/v1/programs/" + programId + "/groups";
    const auto & levelsJson = nlohmann::json::parse(httpClient.get_request(url));
    const auto & groupsJson = levelsJson["Groups"];
    for (const auto & group : groupsJson) {
        std::string groupName = group["StudentGroupName"].get<std::string>();
        int groupId = group["StudentGroupId"].get<int>();
        groups.emplace_back(groupId, groupName);

    }
    return groups;
}