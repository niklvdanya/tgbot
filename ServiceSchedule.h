#pragma once
#include "HTTPClient.h"
#include <string>
#include "json.hpp"
#include "Education.h"

/**
 * @file ServiceSchedule.h
 * @brief Заголовочный файл, содержащий класс ServiceSchedule для работы с расписанием.
 *
 * Класс использует HTTPClient для отправки запросов к API расписания и обработки полученных данных.
 */
class ServiceSchedule 
{
public:
    /**
     * @brief Конструктор ServiceSchedule.
     * @param client Экземпляр HTTPClient для отправки запросов.
     */
    explicit ServiceSchedule(HTTPClient client) : httpClient(client) {}

    /**
     * @brief Получает расписание с сервера и возвращает его в виде строки.
     * @param groupId Идентификатор группы.
     * @return Строка с расписанием.
     */
    std::string getSchedule(std::string groupId);

    /**
     * @brief Получает список факультетов.
     * @return Вектор объектов Faculty.
     */
    std::vector<Faculty> getFaculties();

    /**
     * @brief Получает уровни обучения для заданного факультета.
     * @param facultyAlias Псевдоним факультета.
     * @return Вектор объектов Level.
     */
    std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias);

    /**
     * @brief Получает программы обучения для заданного факультета и уровня обучения.
     * @param facultyAlias Псевдоним факультета.
     * @param levelId Идентификатор уровня обучения.
     * @return Вектор объектов Program.
     */
    std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId);

    /**
     * @brief Получает годы обучения для заданной программы.
     * @param facultyAlias Псевдоним факультета.
     * @param levelId Идентификатор уровня обучения.
     * @param programId Идентификатор программы обучения.
     * @return Вектор объектов Program.
     */
    std::vector<Program> getProgramYears(const std::string& facultyAlias, int levelId, int programId);

    /**
     * @brief Получает список групп для заданной программы обучения.
     * @param programId Идентификатор программы обучения.
     * @return Вектор объектов Group.
     */
    std::vector<Group> getGroups(std::string programId);

private:
    HTTPClient httpClient;
};