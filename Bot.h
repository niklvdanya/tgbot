#pragma once
#include "MessageHandlers.h"
#include "BotView.h" 
#include <memory>    

class Bot {
public:
    explicit Bot(const std::string& token)
        : bot(token), messageHandlers_(bot, std::static_pointer_cast<IBotView>(std::make_shared<BotView>(bot))) {
        setupHandlers();
    }

    void run();
    void setupHandlers();

private:
    TgBot::Bot bot;
    MessageHandlers messageHandlers_;
};