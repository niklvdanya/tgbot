#pragma once
#include <string>
#include <curl/curl.h>

/**
 * @class HTTPClient
 * @brief Класс для отправки HTTP-запросов и получения ответов.
 *
 * Этот класс оборачивает функциональность libcurl для удобства использования
 * в других частях приложения.
 */
class HTTPClient 
{
public:
    /**
     * @brief Отправляет HTTP GET-запрос и возвращает полученные данные.
     * @param link URL-адрес, на который будет отправлен GET-запрос.
     * @return Строка с полученными данными.
     */
    std::string get_request(const std::string& link);

private:
    /**
     * @brief Обработчик записи данных в буфер.
     * @param buffer Указатель на буфер с данными.
     * @param size Размер каждого элемента данных.
     * @param nmemb Количество элементов данных.
     * @param html Указатель на строку, в которую будут записаны данные.
     * @return Количество записанных байт.
     */
    static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string& html);
};