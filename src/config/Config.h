#pragma once
#include <string>
#include <stdexcept>

class Config {
public:
    static void Load(const std::string& path = ".env");
    static std::string GetToken();
    
private:
    static std::string bot_token_;
    static void ParseLine(const std::string& line);
};