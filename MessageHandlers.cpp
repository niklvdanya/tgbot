#include "MessageHandlers.h"
#include <iostream>
#include <cctype>


void MessageHandlers::onStartCommand(TgBot::Message::Ptr message) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr groupBtn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr teacherBtn(new TgBot::InlineKeyboardButton);
    groupBtn->text = "Названию группы";
    groupBtn->callbackData = "group_btn";
    teacherBtn->text = "ФИО преподавателя";
    teacherBtn->callbackData = "teacher_btn";
    keyboard->inlineKeyboard.push_back({groupBtn});
    keyboard->inlineKeyboard.push_back({teacherBtn});
    std::string greeting = "Добро пожаловать, " + message->chat->firstName + "\n";
    greeting += "Cледуйте указаниям для настройки\n";
    greeting += "--------------------\n";
    greeting += "Получить расписание по: \n";
    bot.getApi().sendMessage(message->chat->id, greeting, false, 0, keyboard);
}

void MessageHandlers::handleGroupButton(const TgBot::CallbackQuery::Ptr& query)
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto facultiesArray = serviceSchedule.getFaculties();
    for (const auto& faculty : facultiesArray)
    {
    
        TgBot::InlineKeyboardButton::Ptr facultyBtn(new TgBot::InlineKeyboardButton);
        facultyBtn->text = faculty.getName();
        facultyBtn->callbackData = "faculty_" + faculty.getAlias();
        keyboard->inlineKeyboard.push_back({ facultyBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите факультет:", false, 0, keyboard);


} 
void MessageHandlers::handleFacultySelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string facultyAlias = query->data.substr(8); 
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto levelsArray = serviceSchedule.getLevelsForFaculty(facultyAlias);

    for (const auto& level : levelsArray)
    {
        TgBot::InlineKeyboardButton::Ptr levelBtn(new TgBot::InlineKeyboardButton);
        levelBtn->text = level.getStudyLevelName();
        levelBtn->callbackData = "level_" + std::to_string(level.getId()) + facultyAlias;
        keyboard->inlineKeyboard.push_back({ levelBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите уровень образования:", false, 0, keyboard);
}
void MessageHandlers::handleLevelSelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string alias = query->data.substr(7);
    int levelId = std::stoi(std::string(1, query->data[6]));
    auto programs = serviceSchedule.getPrograms(alias, levelId);


    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    for (const auto& program : programs)
    {
        std::string id = std::to_string(program.getId());
        TgBot::InlineKeyboardButton::Ptr programBtn(new TgBot::InlineKeyboardButton);
        programBtn->text = program.getProgramName();
        programBtn->callbackData = "program_"  + std::to_string(levelId) + id + alias;
        keyboard->inlineKeyboard.push_back({ programBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите программу обучения:", false, 0, keyboard);
} 
void MessageHandlers::handleProgramSelection(const TgBot::CallbackQuery::Ptr& query)
{
    int levelId = std::stoi(std::string(1, query->data[8]));
    std::string alias;
    int programId;

    if(isdigit(query->data[10])) 
    {
        alias = query->data.substr(11); 
        std::string numberStr = query->data.substr(9, 2);
        programId = std::stoi(numberStr); 
    } 
    else 
    {
        alias = query->data.substr(10); 
        std::string numberStr = query->data.substr(9, 1);
        programId = std::stoi(numberStr); 
    }

    auto programsWithYears = serviceSchedule.getProgramYears(alias, levelId, programId);
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& program : programsWithYears) 
    {
        TgBot::InlineKeyboardButton::Ptr yearBtn(new TgBot::InlineKeyboardButton);
        yearBtn->text = program.getYear();
        yearBtn->callbackData = "programYear_" + std::to_string(program.getStudyProgramId());
        keyboard->inlineKeyboard.push_back({ yearBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите год поступления для программы:", false, 0, keyboard);
}
void MessageHandlers::handleYearSelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string studyProgramId = query->data.substr(12);

    auto groups = serviceSchedule.getGroups(studyProgramId);
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& group : groups) 
    {
        TgBot::InlineKeyboardButton::Ptr yearBtn(new TgBot::InlineKeyboardButton);
        yearBtn->text = group.getGroupName();
        yearBtn->callbackData = "group_" + std::to_string(group.getGroupId());
        keyboard->inlineKeyboard.push_back({ yearBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите год поступления для программы:", false, 0, keyboard);

}
void MessageHandlers::handleGroupSelection(const TgBot::CallbackQuery::Ptr& query)
{
    std::string groupId = query->data.substr(6);
    std::string schedule = serviceSchedule.getSchedule(groupId);
    bot.getApi().sendMessage(query->message->chat->id, schedule);

}
void MessageHandlers::handleTeacherButton(const TgBot::CallbackQuery::Ptr& query)
    {
        bot.getApi().sendMessage(query->message->chat->id, "under development");
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
}
void MessageHandlers::onAnyMessage(TgBot::Message::Ptr message) 
{
    if (message->text[0] == '/')
    {
        return;
    }
    bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
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