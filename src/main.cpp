#include "core/Bot.h"
#include "config/Config.h"
#include <iostream>

int main() {
    try {
        Config::Load(); 
        Bot MyBot(Config::GetToken());
        MyBot.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}