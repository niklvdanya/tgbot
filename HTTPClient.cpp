#include "HTTPClient.h"

size_t HTTPClient::Writer(char* buffer, size_t size, size_t nmemb, std::string& html) 
{
    if (buffer) 
    {
        html.append(buffer, size * nmemb);
        return size * nmemb;
    }
    return 0;
}

std::string HTTPClient::get_request(const std::string& link) 
{
    CURL* curl;
    std::string data;
    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return data;
}