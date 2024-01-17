#include "location.hpp"
#include <loc_data_const.hpp>

#include <chrono>
#include <cmath>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "Location Unit"

location::location() {
    printf("%s constructor\n", MODULE_NAME);
    counter = 0;
    mlastLat = mcurLat = 0.0f;
    mlastLon = mcurLon = 0.0f;
}

location::~location() {
    printf("%s destructor\n", MODULE_NAME);
}

void location::getMockingData(LocationPackage::GpsData* data) {
    printf("%s get mocking data\n", MODULE_NAME);

    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

    if(counter >= constLocData.size())
        counter = 0;
    std::vector<double> pos = constLocData[counter++];

    data->set_speed(calculateSpeed(pos[0], pos[1]));
    data->set_timestamp(timestamp);
    data->set_latitude(pos[0]);
    data->set_longitude(pos[1]);
    data->set_altitude(pos[2]);
    data->set_bearing(calculateHeading(pos[0], pos[1]));

    mlastLat = pos[0];
    mlastLon = pos[1];
}

double location::calculateSpeed(double lat, double lon) {
    double speed = 0.0f;

    double earthRadius = 6371.0f;
    double dLat = (lat - mlastLat) * M_PI / 180.0f;
    double dLon = (lon - mlastLon) * M_PI / 180.0f;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(mlastLat  * M_PI / 180.0f) * std::cos(lat  * M_PI / 180.0f) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = earthRadius * c;

    speed = (distance * 1000) / (0.1f);

    return speed;
}

double location::calculateHeading(double lat, double lon) {
    double heading = 0.0f;

    double lat1Rad = mlastLat * M_PI / 180.0;
    double lon1Rad = mlastLon * M_PI / 180.0;
    double lat2Rad = lat * M_PI / 180.0;
    double lon2Rad = lon * M_PI / 180.0;

    double dLon = lon2Rad - lon1Rad;

    double y = std::sin(dLon) * std::cos(lat2Rad);
    double x = std::cos(lat1Rad) * std::sin(lat2Rad) - std::sin(lat1Rad) * std::cos(lat2Rad) * std::cos(dLon);
    heading = std::atan2(y, x);

    heading = heading * 180.0 / M_PI;

    if (heading < 0) {
        heading += 360.0;
    }

    return heading;
}
