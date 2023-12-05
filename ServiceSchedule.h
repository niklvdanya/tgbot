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
class Faculty {
public:
    Faculty(const std::string& alias, const std::string& name)
        : alias(alias), name(name) {}
    const std::string& getAlias() const { return alias; }
    const std::string& getName() const { return name; }

private:
    std::string alias;
    std::string name;
};

class Level {
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


class Program
{
public:
    Program(unsigned int id, std::string name): id(id), programName(name) {}
    unsigned int getId() const {
        return id;
    }

    std::string getProgramName() const {
        return programName;
    }


private:
    unsigned int id;
    std::string programName;
};


class ServiceSchedule 
{
    HTTPClient httpClient;

public:
    explicit ServiceSchedule(HTTPClient client) : httpClient(client) {}
    /**
     * Получает расписание с сервера и возвращает его в виде строки.
     * @return Строка с расписанием.
     */
    
    std::string get_schedule();
    std::vector<Faculty> getFaculties();
    std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias);
    std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId);
};