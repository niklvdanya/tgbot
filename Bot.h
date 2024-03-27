#pragma once
#include "MessageHandlers.h"
#include "BotView.h" 
#include "View.h"
#include <memory>  
#include "createServiceSchedule.h"  

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