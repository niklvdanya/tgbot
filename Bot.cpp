#include "Bot.h"

Bot::Bot(const std::string& token) : bot(token) {
    setupHandlers();
}

void Bot::setupHandlers() {
    bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        commandHandlers.handleStartCommand(message);
    });

    bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        commandHandlers.handleCallbackQuery(query);
    });

    bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message) {
        commandHandlers.handleAnyMessage(message);
    });
}

void Bot::run() {
    try {
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
