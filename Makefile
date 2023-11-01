CXX := g++
CXXFLAGS := -std=c++14 -I/usr/local/include
LDFLAGS := -lTgBot -lboost_system -lssl -lcrypto -lpthread -lcurl
EXEC := telegram_bot
SRC := telegram_bot.cpp Bot.cpp BotCommandHandlers.cpp ScheduleService.cpp CurlHTTPClient.cpp
OBJ := $(SRC:.cpp=.o)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
