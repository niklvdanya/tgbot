#pragma once
#include <tgbot/tgbot.h>
#include "MessageHandlers.h"

/**
 * @brief Класс для создания и запуска бота.
 */
class Bot 
{
    TgBot::Bot bot;
    MessageHandlers messageHandlers_;

public:
    /**
     * Конструктор класса Bot.
     * @param token Токен бота для авторизации.
     */
    explicit Bot(const std::string& token)
        : bot(token), messageHandlers_(bot) 
        {
        setupHandlers();
    }

    /**
     * Запускает работу бота.
     * Слушает сообщения и события в течение всего времени выполнения.
     */
    void run();

    /**
     * Настраивает обработчики событий для бота.
     */
    void setupHandlers();
};