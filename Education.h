#pragma once
#include <string>
/**
 * Вспомогательные классы, Education - интерфейс
*/
class Education
{
public:
    virtual std::string getName() const = 0;
    virtual std::string getCallbackData() const = 0;
    virtual ~Education() = default;
};

class Faculty : public Education
{
public:
    Faculty(std::string alias, std::string name)
        : alias(alias), name(name) {}
    std::string getCallbackData() const;
    std::string getName() const;

private:
    std::string alias;
    std::string name;
};

class Level : public Education
{
public:
    Level(unsigned int id, std::string name): id(id), studyLevelName(name) {}
    std::string getCallbackData() const;

    std::string getName() const;


private:
    unsigned int id;
    std::string studyLevelName;
};

class Group : public Education
{
public:
    Group(unsigned int id, std::string name): groupId(id), groupName(name) {}
    std::string getCallbackData() const;

    std::string getName() const;

private:
    unsigned int groupId;
    std::string groupName;
};


class Program : public Education
{
public:
    Program(unsigned int id, std::string name): id(id), programName(name) {}
    Program(std::string year, std::string id): year(year), studyProgramId(id) {}
    
    unsigned int getId() const;
    std::string getProgramName() const;
    std::string getCallbackData() const;
    std::string getName() const;


private:
    unsigned int id;
    std::string programName;
    std::string year;
    std::string studyProgramId;
};
