#include "simulator.hpp"

simulator::simulator() {
    mLocUnit = new location_unit(this);
    mVehUnit = new vehicle_data_unit();
    mNetwork = new network_mgr();
}

simulator::~simulator() {
    if(mLocUnit) {
        delete mLocUnit;
        mLocUnit = nullptr;
    }

    if(mVehUnit) {
        delete mVehUnit;
        mVehUnit = nullptr;
    }

    if(mNetwork) {
        delete mNetwork;
        mNetwork = nullptr;
    }
}

void simulator::runFeatureTesting() {
    mLocUnit->runFeatureTesting();
    mVehUnit->runFeatureTesting();
}

void simulator::runLoadTesting() {
    
}
