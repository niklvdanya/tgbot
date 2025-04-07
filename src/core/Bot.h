#pragma once
#include "controllers/MessageHandlers.h"
#include "views/BotView.h" 
#include "views/factory/createView.h"
#include <memory>  
#include "views/factory/createServiceSchedule.h"  

class Bot {
public:
    explicit Bot(const std::string& token)
        : bot(token), messageHandlers_(bot, createView(bot), createServiceSchedule(httpClient)) {
        setupHandlers();
    }

    void run();
    void setupHandlers();

private:
    HTTPClient httpClient;
    TgBot::Bot bot;
    MessageHandlers messageHandlers_;
};