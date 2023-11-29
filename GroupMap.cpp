#include "GroupMap.h"

// Конструктор, в котором инициализируем хеш-мапу
GroupMap::GroupMap() {
    groupMap["22.Б07-мм"] = "366763";
    groupMap["22.Б08-мм"] = "366766";
    groupMap["22.Б09-мм"] = "366764";
    groupMap["22.Б10-мм"] = "366765";
}

// Метод для получения StudentGroupId по StudentGroupName
std::string GroupMap::getGroupId(const std::string& groupName) const {
    auto it = groupMap.find(groupName);
    if (it != groupMap.end()) {
        return it->second;
    }
    return ""; // Возвращаем пустую строку, если не найдено
}