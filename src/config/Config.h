#pragma once
#include <string>
#include <stdexcept>

class Config {
public:
    static void Load(); 
    static std::string GetToken();

private:
    static std::string bot_token_;
};