#ifndef GROUP_MAP_H
#define GROUP_MAP_H

#include <string>
#include <unordered_map>

/**
 * @brief Класс для хранения уникального идентификатор группы(нужен для того, чтобы получать расписание)
 */
class GroupMap {
public:
    /**
     * @brief Конструктор класса GroupMap.
     * Заполняет мапу groupMap
     */
    GroupMap();

    /**
     * @brief Получает идентификатор группы по ее имени.
     * @param groupName Имя группы.
     * @return Идентификатор группы или пустая строка, если группа не найдена.
     */
    std::string getGroupId(const std::string& groupName) const;

private:
    std::unordered_map<std::string, std::string> groupMap; /**< Здесь будут храниться id всех групп */
};

#endif // GROUP_MAP_H