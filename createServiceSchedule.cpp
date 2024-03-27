#include "createServiceSchedule.h"
#include "ServiceSchedule.h"

std::shared_ptr<IServiceSchedule> createServiceSchedule(HTTPClient HTTPClient){
    return std::make_shared<ServiceSchedule>(HTTPClient);
}