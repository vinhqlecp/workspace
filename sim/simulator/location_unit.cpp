#include <location_unit.hpp>
#include <simulator.hpp>

#include <gps.pb.h>

#include <thread>
#include <chrono>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "Location Unit"

#include <gps.pb.h>

void threadFunc(location_unit* ins) {
    printf("%s thread is running...\n", MODULE_NAME);

    network_mgr* net = ins->getParent()->getNetworkIns();

    uint64_t counter = 1;
    while(true) {
        printf("%s preparing location data...\n", MODULE_NAME);

        // Prepare mocking location data
        LocationPackage::GpsData data;
        ins->prepareLocationData(&data);
        
        printf("-------------------------------\n");
        printf("counter   = %ld\n", counter++);
        printf("timestamp = %ld\n", data.timestamp());
        printf("latitude  = %.7f\n", data.latitude());
        printf("longitude = %.7f\n", data.longitude());
        printf("altitude  = %.7f\n", data.altitude());
        printf("speed     = %.3f\n", data.speed());
        printf("bearing   = %.3f\n", data.bearing());
        printf("-------------------------------\n");

        // Send to network layer
        net->getCurrentNet()->publishLocationData(data);

        printf("sent!\n\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

location_unit::location_unit(simulator* parent) {
    printf("%s constructor\n", MODULE_NAME);
    mParent = parent;
    mLoc = new location();
}

location_unit::~location_unit() {
    printf("%s destructor\n", MODULE_NAME);
    if(mLoc) {
        delete mLoc;
        mLoc = nullptr;
    }
}

void location_unit::runFeatureTesting() {
    if(mLoc != nullptr) {
        std::thread locThread([this]() {
            threadFunc(this);
        });
        locThread.detach();
    } else {
        printf("%s mLoc is NULL\n", MODULE_NAME);
    }
}

void location_unit::prepareLocationData(LocationPackage::GpsData* data) {
    if(mLoc != nullptr) {
        mLoc->getMockingData(data);
    } else {
        printf("%s mLoc is NULL\n", MODULE_NAME);
    }
}