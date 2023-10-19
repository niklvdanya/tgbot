#include <iostream>
#include <tgbot/tgbot.h>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string* html) {
        int result = 0;
        if (buffer) {
            html->append(buffer, size*nmemb);
            result = size*nmemb;
        }
        return result;
    }
std::string get_request(const std::string& link) {
        CURL *curl;
        std::string data;
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return data;
    }
class Bot {
public:
    Bot(const std::string& token) : bot(token) {
        setupHandlers();
    }

    void run() {
        try {
            std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;
            TgBot::TgLongPoll longPoll(bot);
            while (true) {
                std::cout << "Long poll started" << std::endl;
                longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            std::cout << "error: " << e.what() << std::endl;
        }
    }

private:
    TgBot::Bot bot;
    std::vector<std::string> bot_commands = {"start", "schedule"};

    std::string get_schedule() {
        auto js_obj = nlohmann::json::parse(get_request("https://timetable.spbu.ru/api/v1/groups/366764/events"));
        std::string schedule_info = "";
        for (int i = 0; i < js_obj["Days"].size(); i++){
            schedule_info += "**" + js_obj["Days"][i]["DayString"].get<std::string>() + "**\n";
            for (int j = 0; j < js_obj["Days"][i]["DayStudyEvents"].size(); j++){
                schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["Subject"].get<std::string>() + "\n";
                schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["TimeIntervalString"].get<std::string>() + "\n";
                schedule_info += js_obj["Days"][i]["DayStudyEvents"][j]["EducatorsDisplayText"].get<std::string>() + "\n\n";
            }
            schedule_info += "------------------------------------------\n";
        }
        return schedule_info;
    }

    void setupHandlers() {
        bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
            onStartCommand(message);
        });

        bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
            onCallbackQuery(query);
        });

        bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message) {
            onAnyMessage(message);
        });
    }

    void onStartCommand(TgBot::Message::Ptr message) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr groupBtn(new TgBot::InlineKeyboardButton);
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


    void onCallbackQuery(TgBot::CallbackQuery::Ptr query) {
    if (query->data == "group_btn") {
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardButton::Ptr groupScheduleBtn(new TgBot::InlineKeyboardButton);
        groupScheduleBtn->text = "22-Б09";
        groupScheduleBtn->callbackData = "group_22B09_schedule";
        keyboard->inlineKeyboard.push_back({groupScheduleBtn});
        bot.getApi().sendMessage(query->message->chat->id, "Выберете группу:", false, 0, keyboard);
    } else if (query->data == "group_22B09_schedule") {
        std::string schedule = get_schedule();
        bot.getApi().sendMessage(query->message->chat->id, schedule);
    } else if (query->data == "teacher_btn") {
        bot.getApi().sendMessage(query->message->chat->id, "under development");
    }
}

    void onAnyMessage(TgBot::Message::Ptr message) {
        for (const auto& command: bot_commands) {
            if ("/" + command == message->text) {
                return;
            }
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    }
};

int main() {
    Bot MyBot("PLACE YOUR TOKEN");
    MyBot.run();
    return 0;
}
