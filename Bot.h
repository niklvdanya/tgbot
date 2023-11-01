#pragma once

#include <tgbot/tgbot.h>
#include <string>
#include "BotCommandHandlers.h"

class Bot {
public:
    explicit Bot(const std::string& token);

    void run();

private:
    TgBot::Bot bot;
    BotCommandHandlers commandHandlers;

    void setupHandlers();
};
