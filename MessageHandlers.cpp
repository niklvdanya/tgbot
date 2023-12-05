#include "MessageHandlers.h"
#include <iostream>
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

void MessageHandlers::onCallbackQuery(TgBot::CallbackQuery::Ptr query) 
{
    HTTPClient  httpClient;
    ServiceSchedule serviceSchedule(httpClient);
    if (query->data == "group_btn") 
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
    else if (query->data.find("faculty_") == 0)
    {
        std::string facultyAlias = query->data.substr(8); 
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        // Получение списка уровней образования для выбранного факультета
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
else if (query->data.find("level_") == 0)
{
    std::string alias = query->data.substr(7);
    int levelId = std::stoi(std::string(1, query->data[6]));
    auto programs = serviceSchedule.getPrograms(alias, levelId);

    // Создание клавиатуры с кнопками программ
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& program : programs)
    {
        TgBot::InlineKeyboardButton::Ptr programBtn(new TgBot::InlineKeyboardButton);
        programBtn->text = program.getProgramName();
        programBtn->callbackData = "program_" + std::to_string(program.getId()); 
        keyboard->inlineKeyboard.push_back({ programBtn });
    }

    bot.getApi().sendMessage(query->message->chat->id, "Выберите программу обучения:", false, 0, keyboard);
} else if (query->data == "teacher_btn") 
    {
        bot.getApi().sendMessage(query->message->chat->id, "under development");
    }
}

/**
 * Обработчик любых текстовых сообщений, не являющихся командами.
 * Отвечает на текст сообщения.
 * @param message Указатель на объект сообщения.
 */

void MessageHandlers::onAnyMessage(TgBot::Message::Ptr message) 
{
    if (message->text[0] == '/')
    {
        return;
    }
    bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
}

/**
 * Настраивает обработчики событий для бота.
 */

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