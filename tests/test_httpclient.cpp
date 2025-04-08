#include <gtest/gtest.h>
#include "services/HTTPClient.h"

TEST(HTTPClientTest, GetRequest) {
    HTTPClient client;
    std::string response = client.get_request("https://api.github.com");
    
    EXPECT_FALSE(response.empty());
    EXPECT_TRUE(response.find("github") != std::string::npos);
}