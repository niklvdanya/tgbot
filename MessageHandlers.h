
/**
 * @file MessageHandlers.h
 * @brief Заголовочный файл, содержащий класс MessageHandlers для обработки сообщений бота.
 */

#pragma once
#include <tgbot/tgbot.h>
#include "ServiceSchedule.h"
#include "Education.h"
#include <vector>
/**
 * @class MessageHandlers
 * @brief Класс для обработки входящих сообщений и команд от пользователя в Telegram боте.
 *
 * Этот класс содержит методы для обработки различных типов сообщений и запросов,
 * таких как команды, текстовые сообщения и callback-запросы.
 */


class MessageHandlers 
{
public:
    /**
     * Конструктор класса MessageHandlers.
     * @param bot Ссылка на объект бота, с которым будет работать обработчик.
     */
    explicit MessageHandlers(TgBot::Bot& bot)
    : bot(bot), serviceSchedule(httpClient) {}
    /**
     * Создает кнопку 
     * @param Education - интерфейс. Сюда может передаваться группа, программа итд.
    */
    void createButton(const Education* entity, TgBot::InlineKeyboardMarkup::Ptr& keyboard,const std::string& prefix, const std::string& postfix = "");
    /**
     * Настраивает обработчики событий для бота.
     */
    void setupHandlers();
    /**
     * Обрабатывает выбор пользователем кнопки "По названию группы"
    */
    void handleGroupButton(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем факультета
    */
    void handleFacultySelection(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем уровня образования
    */
    void handleLevelSelection(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем программы обучения
    */
    void handleProgramSelection(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем года поступления
    */
    void handleYearSelection(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем группы
    */
    void handleGroupSelection(const TgBot::CallbackQuery::Ptr& query);
    /**
     * Обрабатывает выбор пользователем кнопки "По ФИО преподавателя"
    */
    void handleTeacherButton(const TgBot::CallbackQuery::Ptr& query);
private:
    TgBot::Bot& bot;
    HTTPClient  httpClient;
    ServiceSchedule serviceSchedule;

    /**
     * Обработчик команды /start.
     * Отправляет приветственное сообщение и кнопки для выбора опций.
     * @param message Указатель на объект сообщения.
     */
    void onStartCommand(TgBot::Message::Ptr message);

    /**
     * Обработчик запросов обратного вызова (callback query) от пользователя.
     * @param query Указатель на объект callback query.
     */
    void onCallbackQuery(TgBot::CallbackQuery::Ptr query);

    /**
     * Обработчик любых текстовых сообщений, не являющихся командами.
     * Отвечает на текст сообщения.
     * @param message Указатель на объект сообщения.
     */
    void onAnyMessage(TgBot::Message::Ptr message);
    

};

