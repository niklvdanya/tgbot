#include "Config.h"
#include <cstdlib>

std::string Config::bot_token_;

void Config::Load() {
    const char* token = std::getenv("BOT_TOKEN");
    if (token == nullptr || std::string(token).empty()) {
        throw std::runtime_error("BOT_TOKEN environment variable is not set or empty");
    }
    bot_token_ = token;
}

std::string Config::GetToken() {
    if (bot_token_.empty()) {
        throw std::runtime_error("Bot token not loaded. Call Config::Load() first.");
    }
    return bot_token_;
}