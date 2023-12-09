#pragma once
#include "HTTPClient.h"
#include <string>
#include "json.hpp"

class Faculty 
{
public:
    Faculty(const std::string& alias, const std::string& name)
        : alias(alias), name(name) {}
    const std::string& getAlias() const { return alias; }
    const std::string& getName() const { return name; }

private:
    std::string alias;
    std::string name;
};

class Level 
{
public:
    Level(unsigned int id, std::string name): id(id), studyLevelName(name) {}
    unsigned int getId() const {
        return id;
    }

    std::string getStudyLevelName() const {
        return studyLevelName;
    }


private:
    unsigned int id;
    std::string studyLevelName;
};

class Group 
{
public:
    Group(unsigned int id, std::string name): groupId(id), groupName(name) {}
    unsigned int getGroupId() const 
    {
        return groupId;
    }

    std::string getGroupName() const {
        return groupName;
    }


private:
    unsigned int groupId;
    std::string groupName;
};


class Program
{
public:
    Program(unsigned int id, std::string name): id(id), programName(name) {}
    Program(std::string year, int id): year(year), studyProgramId(id) {}
    
    unsigned int getId() const {
        return id;
    }

    std::string getProgramName() const {
        return programName;
    }
    int getStudyProgramId() const {
        return studyProgramId;
    }
    std::string getYear() const {
        return year;
    }


private:
    unsigned int id;
    std::string programName;
    std::string year;
    int studyProgramId;
};

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
    explicit ServiceSchedule(HTTPClient client);

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


