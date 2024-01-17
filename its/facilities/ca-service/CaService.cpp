#include <CaService.h>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaService"

CaService::CaService() {
    printf("%s constructor\n", MODULE_NAME);
}

CaService::~CaService() {
    printf("%s destructor\n", MODULE_NAME);
}

void CaService::Start() {
    printf("%s started\n", MODULE_NAME);
}

void CaService::onLocationChanged(const LocationPackage::GpsData& data) {
    printf("%s location data changed\n", MODULE_NAME);

    printf("-------------------------------\n");
    printf("timestamp = %ld\n", data.timestamp());
    printf("latitude  = %.7f\n", data.latitude());
    printf("longitude = %.7f\n", data.longitude());
    printf("altitude  = %.7f\n", data.altitude());
    printf("speed     = %.3f\n", data.speed());
    printf("bearing   = %.3f\n", data.bearing());
    printf("-------------------------------\n");
}

void CaService::onVehicleChanged(const VehiclePackage::Vehicle& data) {
    printf("%s vehicle data changed\n", MODULE_NAME);
}