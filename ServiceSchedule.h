/**
 * @file ServiceSchedule.h
 * @brief Заголовочный файл, содержащий класс ServiceSchedule для работы с расписанием.
 */

#pragma once
#include "HTTPClient.h"
#include <string>
#include "json.hpp"

/**
 * @class ServiceSchedule
 * @brief Класс для получения и обработки расписания.
 *
 * Этот класс использует HTTPClient для отправки запросов к API расписания и
 * обработки полученных данных.
 */
class ServiceSchedule 
{
    HTTPClient httpClient;

public:
    explicit ServiceSchedule(HTTPClient client) : httpClient(client) {}
    /**
     * Получает расписание с сервера и возвращает его в виде строки.
     * @return Строка с расписанием.
     */
    std::string get_schedule(std::string groupId);
};