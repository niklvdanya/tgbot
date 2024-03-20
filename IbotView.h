#pragma once

#include <tgbot/tgbot.h>
#include <string>
#include <vector>
#include "Education.h" 

class IBotView {
public:
    virtual ~IBotView() {}

    virtual void sendWelcomeMessage(const TgBot::Chat::Ptr& chat) = 0;
    virtual void sendFacultyOptions(const TgBot::Chat::Ptr& chat, const std::vector<Faculty>& faculties) = 0;
    virtual void sendLevelOptions(const TgBot::Chat::Ptr& chat, const std::vector<Level>& levels, const std::string& facultyAlias) = 0;
    virtual void sendProgramOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programs, const std::string& alias, int levelId) = 0;
    virtual void sendProgramYearsOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programsWithYears, const std::string& alias, int levelId, int programId) = 0;
    virtual void sendGroupOptions(const TgBot::Chat::Ptr& chat, const std::vector<Group>& groups) = 0;
    virtual void sendScheduleMessage(const TgBot::Chat::Ptr& chat, const std::string& schedule) = 0;
    virtual void createButton(const Education* entity, TgBot::InlineKeyboardMarkup::Ptr& keyboard,const std::string& prefix, const std::string& postfix = "") = 0; 
    virtual void sendTeacherOptions(const TgBot::Chat::Ptr& chat, const std::string& message) = 0;   
};
