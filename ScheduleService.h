#pragma once

#include <string>
#include "CurlHTTPClient.h"

class ScheduleService {
public:
    ScheduleService(HTTPClient* httpClient);

    std::string getSchedule(const std::string& groupId);

private:
    HTTPClient* httpClient;
};
