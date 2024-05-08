cmake_minimum_required(VERSION 3.0)
project(TelegramBot)

# Установка версии C++ стандарта
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение заголовочных файлов
include_directories(/usr/local/include)

# Поиск необходимых пакетов
find_package(Boost REQUIRED COMPONENTS system locale)  # Объединение компонентов Boost
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

# Добавление исполняемого файла
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

# Линковка с библиотеками
target_link_libraries(telegram_bot
    TgBot
    Boost::system
    Boost::locale  # Добавление Boost.Locale к линковке
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${CURL_LIBRARIES}
)

# Включение заголовочных файлов библиотек
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenSSL_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIRS})
