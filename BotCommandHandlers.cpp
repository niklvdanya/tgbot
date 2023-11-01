#include "BotCommandHandlers.h"
#include "json.hpp"

BotCommandHandlers::BotCommandHandlers(TgBot::Bot& botInstance, ScheduleService& scheduleService)
: bot(botInstance), scheduleService(scheduleService) {}


void BotCommandHandlers::handleStartCommand(TgBot::Message::Ptr message) {
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
void BotCommandHandlers::handleCallbackQuery(TgBot::CallbackQuery::Ptr query) {
    if (query->data == "group_btn") {
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardButton::Ptr groupScheduleBtn(new TgBot::InlineKeyboardButton);
        groupScheduleBtn->text = "22-Б09";
        groupScheduleBtn->callbackData = "group_22B09_schedule";
        keyboard->inlineKeyboard.push_back({groupScheduleBtn});
        bot.getApi().sendMessage(query->message->chat->id, "Выберете группу:", false, 0, keyboard);
    } else if (query->data == "group_22B09_schedule") {
        std::string schedule = scheduleService.getSchedule("366764");
        bot.getApi().sendMessage(query->message->chat->id, schedule);
    } else if (query->data == "teacher_btn") {
        bot.getApi().sendMessage(query->message->chat->id, "Раздел в разработке");
    }
    // Добавьте обработку других callback запросов здесь
}




void BotCommandHandlers::handleAnyMessage(TgBot::Message::Ptr message) {
    if (!message->text.empty() && message->text.front() == '/') {
        return;
    }
    std::string response = "Ваше сообщение: " + message->text;
    bot.getApi().sendMessage(message->chat->id, response);
}

