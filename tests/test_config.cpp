#include <gtest/gtest.h>
#include "config/Config.h"
#include <stdexcept>

TEST(ConfigTest, LoadTokenFromEnv) {
    setenv("BOT_TOKEN", "test-token-123", 1);
    
    EXPECT_NO_THROW(Config::Load());
    EXPECT_EQ(Config::GetToken(), "test-token-123");
}

TEST(ConfigTest, MissingTokenThrows) {
    unsetenv("BOT_TOKEN");
    
    EXPECT_THROW(Config::Load(), std::runtime_error);
}