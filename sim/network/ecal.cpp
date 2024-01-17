#include <ecal.hpp>
#include <constants.hpp>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "Ecal"

ecal::ecal() {
    printf("%s constructor\n", MODULE_NAME);
    eCAL::Initialize(0, nullptr, "V2X Simulator");
}

ecal::~ecal() {
    printf("%s destructor\n", MODULE_NAME);

    eCAL::Finalize();

    if(mLocPub) {
        delete mLocPub;
        mLocPub = nullptr;
    }

    if(mVehPub) {
        delete mVehPub;
        mVehPub = nullptr;
    }

    if(mObjSub) {
        delete mObjSub;
        mObjSub = nullptr;
    }
}

void ecal::start() {
    printf("%s started\n", MODULE_NAME);
    
    printf("%s start location & vehicle publisher\n", MODULE_NAME);
    mLocPub = new eCAL::protobuf::CPublisher<LocationPackage::GpsData>(LOC_PUB_TOPIC);
    mVehPub = new eCAL::protobuf::CPublisher<VehiclePackage::Vehicle>(VEH_PUB_TOPIC);

    printf("%s start object subscriber\n", MODULE_NAME);
    mObjSub = new eCAL::protobuf::CSubscriber<StackPackage::Object>(OBJ_SUB_TOPIC);
    auto obj_callback = std::bind(&ecal::recvMsg, this, std::placeholders::_1, std::placeholders::_2);
    mObjSub->AddReceiveCallback(obj_callback);
    if(!mObjSub->IsCreated()) {
        printf("%s failed to create object subscriber!\n", MODULE_NAME);
    }
}

void ecal::recvMsg(const char*, const StackPackage::Object&) {
    printf("%s received message\n", MODULE_NAME);
}

void ecal::publishLocationData(const LocationPackage::GpsData data) {
    printf("%s published location message\n", MODULE_NAME);
    mLocPub->Send(data);
}

void ecal::publishVehicleData(const VehiclePackage::Vehicle data) {
    printf("%s published vehicle message\n", MODULE_NAME);
    mVehPub->Send(data);
}