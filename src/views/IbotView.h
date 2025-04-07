#pragma once

#include <tgbot/tgbot.h>
#include <string>
#include <vector>
#include "models/Education.h" 

/**
 * @file IBotView.h
 * @brief Заголовочный файл, содержащий класс-интерфейс IBotView для взаимодействия с пользователем
 *
 * Класс используется для отправки сообщений
 */

class IBotView {
public:
    virtual ~IBotView() {}

    /* отправка сообщения после ввода пользователем команды /start*/
    virtual void sendWelcomeMessage(const TgBot::Chat::Ptr& chat) = 0;
    
    /* отправка списка факультетов пользователю */
    virtual void sendFacultyOptions(const TgBot::Chat::Ptr& chat, const std::vector<Faculty>& faculties) = 0;

    /* отправка списка уровней обучения */
    virtual void sendLevelOptions(const TgBot::Chat::Ptr& chat, const std::vector<Level>& levels, const std::string& facultyAlias) = 0;
    
    /*  отправка списка программ обучения */
    virtual void sendProgramOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programs, const std::string& alias, int levelId) = 0;
    
    /* отправка списка годов обучения */
    virtual void sendProgramYearsOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programsWithYears, const std::string& alias, int levelId, int programId) = 0;
    
    /* отправка списка групп */
    virtual void sendGroupOptions(const TgBot::Chat::Ptr& chat, const std::vector<Group>& groups) = 0;
    
    /* отправка расписания*/
    virtual void sendScheduleMessage(const TgBot::Chat::Ptr& chat, const std::string& schedule) = 0;
    
    /* создание кнопки в telegram*/
    virtual void createButton(const Education* entity, TgBot::InlineKeyboardMarkup::Ptr& keyboard,const std::string& prefix, const std::string& postfix = "") = 0; 
    
    /* отправка сообщения после выбора пользователя кнопки teacher_btn */
    virtual void sendTeacherOptions(const TgBot::Chat::Ptr& chat) = 0;   

    virtual void sendTeacherSearchResults(const TgBot::Chat::Ptr& chat, const std::vector<Teacher>& teachers) = 0;

    virtual void sendTeacherSchedule(const TgBot::Chat::Ptr& chat, const Teacher& teacher) = 0;
};
