#include "ScheduleService.h"
#include "json.hpp"

ScheduleService::ScheduleService(HTTPClient* httpClient) : httpClient(httpClient) {}

std::string ScheduleService::getSchedule(const std::string& groupId) {
    std::string url = "https://timetable.spbu.ru/api/v1/groups/" + groupId + "/events";
    auto response = httpClient->get(url);
    auto js_obj = nlohmann::json::parse(response);

    std::string schedule_info = "";
    for (int i = 0; i < js_obj["Days"].size(); i++){
        schedule_info += js_obj["Days"][i]["DayString"].get<std::string>() + "\n";
        for (int j = 0; j < js_obj["Days"][i]["DayStudyEvents"].size(); j++){
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["Subject"].get<std::string>() + "\n";
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["TimeIntervalString"].get<std::string>() + "\n";
            schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["EducatorsDisplayText"].get<std::string>() + "\n\n";
        }
        schedule_info += "------------------------------------------\n";
    }
    return schedule_info;
}
