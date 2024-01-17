#include <iostream>

#include <Constants.h>
#include <LocationDataProvider.h>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "Ecal"

LocationDataProvider::LocationDataProvider() {
    printf("%s constructor\n", MODULE_NAME);
    eCAL::Initialize(0, nullptr, "V2X Stack");
}

LocationDataProvider::~LocationDataProvider() {
    printf("%s destructor\n", MODULE_NAME);

    eCAL::Finalize();

    if(mLocSub) {
        delete mLocSub;
        mLocSub = nullptr;
    }

    if(mVehSub) {
        delete mVehSub;
        mVehSub = nullptr;
    }
}

void LocationDataProvider::Start() {
    printf("%s started\n", MODULE_NAME);

    printf("%s start location subscriber\n", MODULE_NAME);
    mLocSub = new eCAL::protobuf::CSubscriber<LocationPackage::GpsData>(LOC_TOPIC);
    auto loc_callback = bind(&LocationDataProvider::RecvLocMsg, this, std::placeholders::_1, std::placeholders::_2);
    mLocSub->AddReceiveCallback(loc_callback);
    if(!mLocSub->IsCreated()) {
        printf("%s failed to create location subscriber!\n", MODULE_NAME);
    }

    printf("%s start vehicle subscriber\n", MODULE_NAME);
    mVehSub = new eCAL::protobuf::CSubscriber<VehiclePackage::Vehicle>(VEH_TOPIC);
    auto veh_callback = bind(&LocationDataProvider::RecvVehMsg, this, std::placeholders::_1, std::placeholders::_2);
    mVehSub->AddReceiveCallback(veh_callback);
    if(!mVehSub->IsCreated()) {
        printf("%s failed to create vehicle subscriber!\n", MODULE_NAME);
    }
}

void LocationDataProvider::RecvLocMsg(const char*, const LocationPackage::GpsData&) {
    printf("%s received location message\n", MODULE_NAME);
}

void LocationDataProvider::RecvVehMsg(const char*, const VehiclePackage::Vehicle&) {
    printf("%s received vehicle message\n", MODULE_NAME);
}
