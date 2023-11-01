#pragma once

#include <string>

class HTTPClient {
public:
    virtual ~HTTPClient() = default;
    virtual std::string get(const std::string& url) = 0;
};

class CurlHTTPClient : public HTTPClient {
public:
    std::string get(const std::string& url) override;

private:
    static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string* html);
};
