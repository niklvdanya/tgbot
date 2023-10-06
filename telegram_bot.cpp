#include <tgbot/tgbot.h>
#include <iostream>

class MyBot {
public:
    MyBot(const std::string& token) : bot(token) {}

    void run() {
        setupHandlers();
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
    void setupHandlers() {
        bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
            onStartCommand(message);
        });

        bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
            onCallbackQuery(query);
        });
    }

    void onStartCommand(TgBot::Message::Ptr message) {
        std::string welcomeMessage = "Welcome, " + message->from->firstName + "!\n";
        welcomeMessage += "Follow the instructions to configure\n";
        welcomeMessage += "-----------------------------------------\n";
        bot.getApi().sendMessage(message->chat->id, welcomeMessage);

        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        addKeyboardButton(keyboard, "The name of the group", "group_name");
        addKeyboardButton(keyboard, "Program navigation", "program_navigation");
        addKeyboardButton(keyboard, "Full name of the teacher", "teacher_name");

        bot.getApi().sendMessage(message->chat->id, "Choose a direction, get a shedule by: ", false, 0, keyboard);
    }

    void addKeyboardButton(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::string& text, const std::string& callbackData) {
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = text;
        button->callbackData = callbackData;
        row.push_back(button);
        keyboard->inlineKeyboard.push_back(row);
    }

    void onCallbackQuery(TgBot::CallbackQuery::Ptr query) {
        if (query->data == "group_name") {
            bot.getApi().sendMessage(query->message->chat->id, "You chose: Group name");
        } else if (query->data == "program_navigation") {
            bot.getApi().sendMessage(query->message->chat->id, "You chose: Program navigation");
        } else if (query->data == "teacher_name") {
            bot.getApi().sendMessage(query->message->chat->id, "You chose: Teacher name");
        }
    }

    TgBot::Bot bot;
};

int main() {
    const std::string token = "PLACE YOUR TOKEN";
    MyBot bot(token);
    bot.run();
    return 0;
}
