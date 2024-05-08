#include "BotView.h"

void BotView::sendWelcomeMessage(const TgBot::Chat::Ptr& chat) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr groupBtn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr teacherBtn(new TgBot::InlineKeyboardButton);
    
    groupBtn->text = "Названию группы";
    groupBtn->callbackData = "group_btn";
    teacherBtn->text = "ФИО преподавателя";
    teacherBtn->callbackData = "teacher_btn";
    
    keyboard->inlineKeyboard.push_back({groupBtn});
    keyboard->inlineKeyboard.push_back({teacherBtn});
    
    std::string greeting = "Добро пожаловать, " + chat->firstName + "\n";
    greeting += "Следуйте указаниям для настройки\n";
    greeting += "--------------------\n";
    greeting += "Получить расписание по: \n";
    
    bot.getApi().sendMessage(chat->id, greeting, false, 0, keyboard);
}

void BotView::sendFacultyOptions(const TgBot::Chat::Ptr& chat, const std::vector<Faculty>& faculties)
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& faculty : faculties)
    {
        createButton(&faculty, keyboard, "faculty_");
    }

    bot.getApi().sendMessage(chat->id, "Выберите факультет:", false, 0, keyboard);
}

void BotView::createButton(const Education* entity, TgBot::InlineKeyboardMarkup::Ptr& keyboard,
                                                    const std::string& prefix, const std::string& postfix) 
{
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = entity->getName();
    button->callbackData = prefix + entity->getCallbackData() + postfix;
    keyboard->inlineKeyboard.push_back({ button });
}

void BotView::sendLevelOptions(const TgBot::Chat::Ptr& chat, const std::vector<Level>& levels, 
                                                                    const std::string& facultyAlias) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    for (const auto& level : levels)
    {
        createButton(&level, keyboard, "level_", facultyAlias);
    }

    bot.getApi().sendMessage(chat->id, "Выберите уровень образования:", false, 0, keyboard);

}

void BotView::sendProgramOptions(const TgBot::Chat::Ptr& chat, const std::vector<Program>& programs, 
                                                                    const std::string& alias, int levelId) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& program : programs) {
        TgBot::InlineKeyboardButton::Ptr programBtn(new TgBot::InlineKeyboardButton);
        programBtn->text = program.getProgramName();
        programBtn->callbackData = "program_" + std::to_string(levelId) + std::to_string(program.getId()) + alias;
        keyboard->inlineKeyboard.push_back({ programBtn });
    }

    bot.getApi().sendMessage(chat->id, "Выберите программу обучения:", false, 0, keyboard);
}

void BotView::sendProgramYearsOptions(const TgBot::Chat::Ptr& chat, 
                                                    const std::vector<Program>& programsWithYears, 
                                                        const std::string& alias, int levelId, int programId) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& program : programsWithYears) {
        TgBot::InlineKeyboardButton::Ptr programYearBtn(new TgBot::InlineKeyboardButton);
        programYearBtn->text = program.getProgramName() + ": " + program.getName(); 
        programYearBtn->callbackData = "programYear_" + std::to_string(program.getId()); 
        keyboard->inlineKeyboard.push_back({ programYearBtn });
    }

    bot.getApi().sendMessage(chat->id, "Выберите год поступления для программы:", false, 0, keyboard);
}

void BotView::sendGroupOptions(const TgBot::Chat::Ptr& chat, const std::vector<Group>& groups) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    for (const auto& group : groups) {
        TgBot::InlineKeyboardButton::Ptr groupBtn(new TgBot::InlineKeyboardButton);
        groupBtn->text = group.getName(); 
        groupBtn->callbackData = "group_" + group.getCallbackData();
        keyboard->inlineKeyboard.push_back({groupBtn});
    }

    bot.getApi().sendMessage(chat->id, "Выберите группу:", false, 0, keyboard);
}

void BotView::sendScheduleMessage(const TgBot::Chat::Ptr& chat, const std::string& schedule) {
    bot.getApi().sendMessage(chat->id, schedule);
}

void BotView::sendTeacherOptions(const TgBot::Chat::Ptr& chat) {
    std::string message = "Введите фамилию преподавателя";
    bot.getApi().sendMessage(chat->id, message);
}

void BotView::sendTeacherSearchResults(const TgBot::Chat::Ptr& chat, const std::vector<Teacher>& teachers) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    for (const auto& teacher : teachers) {
        auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = teacher.getName();
        button->callbackData = "teacher_" + teacher.getCallbackData();
        std::vector<TgBot::InlineKeyboardButton::Ptr> row {button};
        keyboard->inlineKeyboard.push_back(row);
    }
    bot.getApi().sendMessage(chat->id, "Выберите преподавателя:", false, 0, keyboard);
}

void BotView::sendTeacherSchedule(const TgBot::Chat::Ptr& chat, const Teacher& teacher) {
    std::string message = "";
    for (const auto& day : teacher.getScheduleDays()) {
        message += day + "----------------------------------\n";
    }
    bot.getApi().sendMessage(chat->id, message);
}