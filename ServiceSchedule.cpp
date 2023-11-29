#include <string>
#include "ServiceSchedule.h"

std::string ServiceSchedule::get_schedule(std::string groupId) 
{
    auto js_obj = nlohmann::json::parse(httpClient.get_request("https://timetable.spbu.ru/api/v1/groups/" + groupId + "/events"));
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