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

class Group {
public:
    Group(unsigned int id, std::string name): groupId(id), groupName(name) {}
    unsigned int getGroupId() const {
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


class ServiceSchedule 
{
    HTTPClient httpClient;

public:
    explicit ServiceSchedule(HTTPClient client) : httpClient(client) {}
    /**
     * Получает расписание с сервера и возвращает его в виде строки.
     * @return Строка с расписанием.
     */
    
    std::string getSchedule(std::string groupId);
    std::vector<Faculty> getFaculties();
    std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias);
    std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId);
    std::vector<Program> getProgramYears(const std::string& facultyAlias, int levelId, int programId);
    std::vector<Group> getGroups(std::string programId);
};