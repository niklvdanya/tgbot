#include "MessageHandlers.h"

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
    if (query->data == "group_btn") 
    {
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardButton::Ptr groupScheduleBtn(new TgBot::InlineKeyboardButton);
        groupScheduleBtn->text = "22-Б09";
        groupScheduleBtn->callbackData = "group_22B09_schedule";
        keyboard->inlineKeyboard.push_back({groupScheduleBtn});
        bot.getApi().sendMessage(query->message->chat->id, "Выберете группу:", false, 0, keyboard);
    } 
    else if (query->data == "group_22B09_schedule") 
    {
        HTTPClient httpClient;
        ServiceSchedule serviceSchedule(httpClient);
        std::string schedule = serviceSchedule.get_schedule();
        bot.getApi().sendMessage(query->message->chat->id, schedule);
    } 
    else if (query->data == "teacher_btn") 
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