#ifndef GROUP_MAP_H
#define GROUP_MAP_H

#include <string>
#include <unordered_map>

class GroupMap {
public:
    GroupMap();

    // Метод для получения StudentGroupId по StudentGroupName
    std::string getGroupId(const std::string& groupName) const;

private:
    // Хеш-мапа для сопоставления StudentGroupName с StudentGroupId
    std::unordered_map<std::string, std::string> groupMap;
};

#endif // GROUP_MAP_H
