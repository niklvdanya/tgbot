#pragma once
#include "HTTPClient.h"
#include <string>
#include "json.hpp"
#include "Education.h"

class IServiceSchedule 
{
public:
    
    virtual std::string getSchedule(std::string groupId) = 0;

    virtual std::vector<Faculty> getFaculties() = 0;

    virtual std::vector<Level> getLevelsForFaculty(const std::string& facultyAlias) = 0;

    virtual std::vector<Program> getPrograms(const std::string& facultyAlias, int levelId) = 0;

    virtual std::vector<Program> getProgramYears(const std::string& facultyAlias, int levelId, int programId) = 0;

    virtual std::vector<Group> getGroups(std::string programId) = 0;
};