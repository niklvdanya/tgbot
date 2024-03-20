#pragma once

#include <tgbot/tgbot.h>
#include <vector>
#include <string>
#include "Education.h" 
#include "IbotView.h"

class BotView : public IBotView{
public:
    explicit BotView(TgBot::Bot& bot) : bot(bot) {}

    void sendWelcomeMessage(const TgBot::Chat::Ptr& chat) override;
    void sendFacultyOptions(const TgBot::Chat::Ptr& chat, const std::vector<Faculty>& faculties) override;
    void sendLevelOptions(const TgBot::Chat::Ptr& chat, const std::vector<Level>& levels, const std::string& facultyAlias) override;    
    void createButton(const Education* entity, TgBot::InlineKeyboardMarkup::Ptr& keyboard,const std::string& prefix, const std::string& postfix = "") override; 
    void sendProgramOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programs, const std::string& alias, int levelId) override;
    void sendProgramYearsOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programsWithYears, const std::string& alias, int levelId, int programId) override;
    void sendGroupOptions(const TgBot::Chat::Ptr& chat, const std::vector<Group>& groups) override;
    void sendScheduleMessage(const TgBot::Chat::Ptr& chat, const std::string& schedule) override;
    void sendTeacherOptions(const TgBot::Chat::Ptr& chat, const std::string& message) override;
private:
    TgBot::Bot& bot;
};