
/**
 * @file MessageHandlers.h
 * @brief Заголовочный файл, содержащий класс MessageHandlers для обработки сообщений бота.
 */

#pragma once
#include <tgbot/tgbot.h>
#include "ServiceSchedule.h"

/**
 * @class MessageHandlers
 * @brief Класс для обработки входящих сообщений и команд от пользователя в Telegram боте.
 *
 * Этот класс содержит методы для обработки различных типов сообщений и запросов,
 * таких как команды, текстовые сообщения и callback-запросы.
 */
class MessageHandlers 
{
    TgBot::Bot& bot;

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

public:
    /**
     * Конструктор класса MessageHandlers.
     * @param bot Ссылка на объект бота, с которым будет работать обработчик.
     */
    explicit MessageHandlers(TgBot::Bot& bot) : bot(bot) {}

    /**
     * Настраивает обработчики событий для бота.
     */
    void setupHandlers();
};