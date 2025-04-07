#pragma once
#include <string>

enum class UserState {
    DEFAULT,
    AWAITING_TEACHER_NAME
};

struct UserData {
    UserState state = UserState::DEFAULT;
    std::string lastInput;
};