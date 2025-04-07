cmake_minimum_required(VERSION 3.0)
project(TelegramBot)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

add_executable(telegram_bot
    telegram_bot.cpp
    Bot.cpp
    HTTPClient.cpp
    MessageHandlers.cpp
    ServiceSchedule.cpp
    Education.cpp
    BotView.cpp
    createView.cpp
    createServiceSchedule.cpp
)


target_link_libraries(telegram_bot
    TgBot
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${CURL_LIBRARIES}
)

include_directories(${CURL_INCLUDE_DIRS})