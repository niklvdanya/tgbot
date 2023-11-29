#include "MessageHandlers.h"
#include "GroupMap.h"
GroupMap groupMap;

// Добавим мапу для отслеживания состояний пользователей
std::unordered_map<int, std::string> userStates;

void MessageHandlers::onStartCommand(TgBot::Message::Ptr message) 
{
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto groupBtn = std::make_shared<TgBot::InlineKeyboardButton>();
    TgBot::InlineKeyboardButton::Ptr teacherBtn(new TgBot::InlineKeyboardButton);
    groupBtn->text = "Названию группы";
    groupBtn->callbackData = "group_btn";
    teacherBtn->text = "ФИО преподавателя";
    teacherBtn->callbackData = "teacher_btn";
    keyboard->inlineKeyboard.push_back({groupBtn});
    keyboard->inlineKeyboard.push_back({teacherBtn});
    std::string greeting = "Добро пожаловать, " + message->chat->firstName + "\n";
    greeting += "Cледуйте указаниям для настройки\n";
    greeting += "--------------------\n";
    greeting += "Получить расписание по: \n";
    bot.getApi().sendMessage(message->chat->id, greeting, false, 0, keyboard);
}

void MessageHandlers::onCallbackQuery(TgBot::CallbackQuery::Ptr query) 
{
    if (query->data == "group_btn") 
    {
        // Устанавливаем состояние пользователя в "waiting_for_group"
        userStates[query->message->chat->id] = "waiting_for_group";

        // Отправляем сообщение, просим пользователя ввести название группы
        bot.getApi().sendMessage(query->message->chat->id, "Введите название группы, например, 22.Б09-мм.");
    } 
    // 

    else if (query->data == "teacher_btn") 
    {
        bot.getApi().sendMessage(query->message->chat->id, "under development");
    }
}

/**
 * Обработчик любых текстовых сообщений, не являющихся командами.
 * Отвечает на текст сообщения.
 * @param message Указатель на объект сообщения.
 */

void MessageHandlers::onAnyMessage(TgBot::Message::Ptr message) 
{
    if (message->text[0] == '/')
    {
        return;
    }
    auto it = userStates.find(message->chat->id);
    if (it != userStates.end() && it->second == "waiting_for_group") 
    {
        // Получаем введенное пользователем название группы
        std::string groupName = message->text;

        // Получаем StudentGroupId по StudentGroupName
        std::string groupId = groupMap.getGroupId(groupName);

        if (!groupId.empty()) 
        {
            // Теперь у вас есть StudentGroupId, используйте его для вызова get_schedule
            HTTPClient httpClient;
            ServiceSchedule serviceSchedule(httpClient);
            std::string schedule = serviceSchedule.get_schedule(groupId);

            // Отправляем пользователю расписание
            bot.getApi().sendMessage(message->chat->id, schedule);
        } 
        else 
        {
            // Обработка сценария, когда groupId не найден
            bot.getApi().sendMessage(message->chat->id, "Группа не найдена. Пожалуйста, убедитесь в правильности введенного названия группы.");
        }

        // Удаляем состояние "waiting_for_group" после обработки
        userStates.erase(it);
    } 
    
}

/**
 * Настраивает обработчики событий для бота.
 */

void MessageHandlers::setupHandlers() 
{
    bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) 
    {
        onStartCommand(message);
    });

    bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) 
    {
        onCallbackQuery(query);
    });

    bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message) 
    {
        onAnyMessage(message);
    });
}