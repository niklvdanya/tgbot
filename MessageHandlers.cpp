#include "MessageHandlers.h"
#include <iostream>
#include <cctype>

void MessageHandlers::onStartCommand(TgBot::Message::Ptr message) {
    view->sendWelcomeMessage(message->chat);
}

void MessageHandlers::handleGroupButton(const TgBot::CallbackQuery::Ptr& query) {
    auto facultiesArray = serviceSchedule->getFaculties();
    view->sendFacultyOptions(query->message->chat, facultiesArray);
}
 
void MessageHandlers::handleFacultySelection(const TgBot::CallbackQuery::Ptr& query) {
    std::string facultyAlias = query->data.substr(8); 
    auto levelsArray = serviceSchedule->getLevelsForFaculty(facultyAlias);
    view->sendLevelOptions(query->message->chat, levelsArray, facultyAlias);
}

void MessageHandlers::handleLevelSelection(const TgBot::CallbackQuery::Ptr& query) {
    std::string alias = query->data.substr(7);
    int levelId = std::stoi(std::string(1, query->data[6]));
    auto programs = serviceSchedule->getPrograms(alias, levelId);

    view->sendProgramOptions(query->message->chat, programs, alias, levelId);
}

void MessageHandlers::handleProgramSelection(const TgBot::CallbackQuery::Ptr& query) {
    int levelId = std::stoi(std::string(1, query->data[8]));
    std::string alias;
    int programId;

    if(isdigit(query->data[10])) {
        alias = query->data.substr(11);
        programId = std::stoi(query->data.substr(9, 2));
    } else {
        alias = query->data.substr(10);
        programId = std::stoi(query->data.substr(9, 1));
    }

    auto programsWithYears = serviceSchedule->getProgramYears(alias, levelId, programId);
    view->sendProgramYearsOptions(query->message->chat, programsWithYears, alias, levelId, programId);
}

void MessageHandlers::handleYearSelection(const TgBot::CallbackQuery::Ptr& query) {
    std::string studyProgramId = query->data.substr(12);
    auto groups = serviceSchedule->getGroups(studyProgramId);
    view->sendGroupOptions(query->message->chat, groups);
}

void MessageHandlers::handleGroupSelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string groupId = query->data.substr(6);
    std::string schedule = serviceSchedule->getSchedule(groupId);
    view->sendScheduleMessage(query->message->chat, schedule);
}

void MessageHandlers::handleTeacherButton(const TgBot::CallbackQuery::Ptr& query)
{
    userStates[query->message->chat->id].state = UserState::AWAITING_TEACHER_NAME;
    view->sendTeacherOptions(query->message->chat);
}

void MessageHandlers::handleTeacherSelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string id = query->data.substr(8);
    auto teacher = serviceSchedule->getTeacher(id);
    view->sendTeacherSchedule(query->message->chat, teacher);
    
}

void MessageHandlers::onCallbackQuery(TgBot::CallbackQuery::Ptr query) {
    if (query->data == "group_btn") 
    {
        handleGroupButton(query);
    } 
    else if (query->data.find("faculty_") == 0) 
    {
        handleFacultySelection(query);
    } 
    else if (query->data.find("level_") == 0)
    {
        handleLevelSelection(query);
    } 
    else if (query->data.find("program_") == 0) 
    {
        handleProgramSelection(query);
    } 
    else if (query->data.find("programYear_") == 0) 
    {
        handleYearSelection(query);
    } 
    
    else if (query->data.find("group_") == 0) 
    {
        handleGroupSelection(query);
    } 
    else if (query->data == "teacher_btn") 
    {
        handleTeacherButton(query);
    }
    else if (query->data.find("teacher_") == 0)
    {
        handleTeacherSelection(query);
    }
}

void MessageHandlers::onAnyMessage(TgBot::Message::Ptr message) 
{
    auto& userData = userStates[message->chat->id];
    if (userData.state == UserState::AWAITING_TEACHER_NAME) 
    {
        auto teachers = serviceSchedule->getTeachersByLastName(message->text);
        if (teachers.empty()) {
            std::string response = "Преподаватель с такой фамилией не найден. Пожалуйста, введите фамилию еще раз:";
            bot.getApi().sendMessage(message->chat->id, response);
        } else {
        userData.lastInput = message->text;
        userData.state = UserState::DEFAULT;

        view->sendTeacherSearchResults(message->chat, teachers);
        }
    }
}

void MessageHandlers::setupHandlers() 
{
    bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) 
    {
        onStartCommand(message);
    });

    bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) 
    {
        onCallbackQuery(query);
    });

    bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message) 
    {
        onAnyMessage(message);
    });
}
