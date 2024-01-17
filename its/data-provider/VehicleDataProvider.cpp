#include <iostream>

#include <Constants.h>
#include <VehicleDataProvider.h>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "VehicleDataProvider"

VehicleDataProvider::VehicleDataProvider() {
    printf("%s constructor\n", MODULE_NAME);
    eCAL::Initialize(0, nullptr, "V2X Stack");
}

VehicleDataProvider::~VehicleDataProvider() {
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

void VehicleDataProvider::Start() {
    printf("%s started\n", MODULE_NAME);

    printf("%s start location subscriber\n", MODULE_NAME);
    mLocSub = new eCAL::protobuf::CSubscriber<LocationPackage::GpsData>(LOC_TOPIC);
    auto loc_callback = bind(&VehicleDataProvider::RecvLocMsg, this, std::placeholders::_1, std::placeholders::_2);
    mLocSub->AddReceiveCallback(loc_callback);
    if(!mLocSub->IsCreated()) {
        printf("%s failed to create location subscriber!\n", MODULE_NAME);
    }

    printf("%s start vehicle subscriber\n", MODULE_NAME);
    mVehSub = new eCAL::protobuf::CSubscriber<VehiclePackage::Vehicle>(VEH_TOPIC);
    auto veh_callback = bind(&VehicleDataProvider::RecvVehMsg, this, std::placeholders::_1, std::placeholders::_2);
    mVehSub->AddReceiveCallback(veh_callback);
    if(!mVehSub->IsCreated()) {
        printf("%s failed to create vehicle subscriber!\n", MODULE_NAME);
    }
}

void VehicleDataProvider::RecvLocMsg(const char*, const LocationPackage::GpsData&) {
    printf("%s received location message\n", MODULE_NAME);
}

void VehicleDataProvider::RecvVehMsg(const char*, const VehiclePackage::Vehicle&) {
    printf("%s received vehicle message\n", MODULE_NAME);
}
