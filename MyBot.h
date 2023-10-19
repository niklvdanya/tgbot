#pragma once

#include <tgbot/tgbot.h>
#include <vector>
#include <string>
#include "json.hpp"

size_t Writer(char* buffer, size_t size, size_t nmemb, std::string* html);
std::string get_request(const std::string& link);

class Bot {
public:
    Bot(const std::string& token);

    void run();

private:
    TgBot::Bot bot;
    std::vector<std::string> bot_commands = {"start", "schedule"};

    std::string get_schedule();

    void setupHandlers();

    void onStartCommand(TgBot::Message::Ptr message);
    void onCallbackQuery(TgBot::CallbackQuery::Ptr query);
    void onAnyMessage(TgBot::Message::Ptr message);
};
