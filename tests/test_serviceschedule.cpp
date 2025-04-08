#include <gtest/gtest.h>
#include "services/ServiceSchedule.h"

TEST(ServiceScheduleTest, GetFaculties) {
    HTTPClient client;
    ServiceSchedule service(client);
    
    std::vector<Faculty> faculties = service.getFaculties();
    EXPECT_FALSE(faculties.empty());
    EXPECT_GT(faculties.size(), 0);
}