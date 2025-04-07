#include "Bot.h"
#include <iostream>

void Bot::run()
{
    try 
    {
        std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) 
        {
            std::cout << "Long poll started" << std::endl;
            longPoll.start();
        }
    } 
    catch (TgBot::TgException& e) 
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}


void Bot::setupHandlers() 
{
    messageHandlers_.setupHandlers();
}