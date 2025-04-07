#include "Config.h"
#include <fstream>
#include <sstream>

std::string Config::bot_token_;

void Config::Load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        ParseLine(line);
    }
}

void Config::ParseLine(const std::string& line) {
    if (line.empty() || line[0] == '#') return;

    size_t delimiter_pos = line.find('=');
    if (delimiter_pos == std::string::npos) return;

    std::string key = line.substr(0, delimiter_pos);
    std::string value = line.substr(delimiter_pos + 1);

    if (key == "BOT_TOKEN") {
        bot_token_ = value;
    }
}

std::string Config::GetToken() {
    if (bot_token_.empty()) {
        throw std::runtime_error("Bot token not loaded. Call Config::Load() first.");
    }
    return bot_token_;
}