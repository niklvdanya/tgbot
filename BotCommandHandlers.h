#pragma once

#include <tgbot/tgbot.h>
#include "ScheduleService.h"
#include "ScheduleService.h"
class BotCommandHandlers {
public:
    BotCommandHandlers() = default;
    explicit BotCommandHandlers(TgBot::Bot& botInstance, ScheduleService& scheduleService);

    void handleStartCommand(TgBot::Message::Ptr message);
    void handleCallbackQuery(TgBot::CallbackQuery::Ptr query);
    void handleAnyMessage(TgBot::Message::Ptr message);

private:
    TgBot::Bot& bot;
    ScheduleService& scheduleService;
    std::string get_schedule();
    std::string get_request(const std::string& url);
};
