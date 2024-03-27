#pragma once
#include "IServiceSchedule.h"

/**
 * @file ServiceSchedule.h
 * @brief Заголовочный файл, содержащий класс ServiceSchedule для работы с расписанием.
 *
 * Класс использует HTTPClient для отправки запросов к API расписания и обработки полученных данных.
 */
class ServiceSchedule : public IServiceSchedule
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
    std::string getSchedule(std::string groupId) override;

    /**
     * @brief Получает список факультетов.
     * @return Вектор объектов Faculty.
     */
    std::vector<Faculty> getFaculties() override;

    /**
     * @brief Получает уровни обучения для заданного факультета.
     * @param facultyAlias Псевдоним факультета.
     * @return Вектор объектов Level.
     */
    std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias) override;

    /**
     * @brief Получает программы обучения для заданного факультета и уровня обучения.
     * @param facultyAlias Псевдоним факультета.
     * @param levelId Идентификатор уровня обучения.
     * @return Вектор объектов Program.
     */
    std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId) override;

    /**
     * @brief Получает годы обучения для заданной программы.
     * @param facultyAlias Псевдоним факультета.
     * @param levelId Идентификатор уровня обучения.
     * @param programId Идентификатор программы обучения.
     * @return Вектор объектов Program.
     */
    std::vector<Program> getProgramYears(const std::string& facultyAlias, int levelId, int programId) override;

    /**
     * @brief Получает список групп для заданной программы обучения.
     * @param programId Идентификатор программы обучения.
     * @return Вектор объектов Group.
     */
    std::vector<Group> getGroups(std::string programId) override;

private:
    HTTPClient httpClient;
};