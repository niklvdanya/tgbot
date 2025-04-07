#pragma once
#include "HTTPClient.h"
#include <string>
#include "json.hpp"
#include "models/Education.h"


/**
 * @file IServiceSchedule.h
 * @brief Заголовочный файл, содержащий класс-интерфейс IServiceSchedule для работы с расписанием.
 *
 * Класс используется для получения данных с сервера
 */


class IServiceSchedule 
{
public:
    
    virtual std::string getSchedule(std::string groupId) = 0;

    virtual std::vector<Faculty> getFaculties() = 0;

    virtual std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias) = 0;

    virtual std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId) = 0;

    virtual std::vector<Program> getProgramYears(const std::string& facultyAlias, int levelId, int programId) = 0;

    virtual std::vector<Group> getGroups(std::string programId) = 0;

    virtual std::vector<Teacher> getTeachersByLastName(const std::string& lastName) = 0;

    virtual Teacher getTeacher(const std::string& id) = 0;
};