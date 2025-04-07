cmake_minimum_required(VERSION 3.10) 
project(TelegramBot VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

set(SOURCES
    src/main.cpp
    src/core/Bot.cpp
    src/services/HTTPClient.cpp
    src/controllers/MessageHandlers.cpp
    src/services/ServiceSchedule.cpp
    src/models/Education.cpp
    src/views/BotView.cpp
    src/views/factory/createView.cpp
    src/views/factory/createServiceSchedule.cpp
    src/config/Config.cpp    
)

set(HEADERS
    src/core/Bot.h
    src/services/HTTPClient.h
    src/controllers/MessageHandlers.h
    src/services/ServiceSchedule.h
    src/models/Education.h
    src/views/BotView.h
    src/views/factory/createView.h
    src/views/factory/createServiceSchedule.h
    src/config/Config.h
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src  
    /usr/local/include       
)

find_package(Boost 1.71 REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

add_executable(telegram_bot ${SOURCES} ${HEADERS})

target_link_libraries(telegram_bot PRIVATE
    TgBot
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${CURL_LIBRARIES}
)

target_include_directories(telegram_bot PRIVATE
    ${CMAKE_SOURCE_DIR}/src  
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
    /usr/local/include
)

set_target_properties(telegram_bot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)