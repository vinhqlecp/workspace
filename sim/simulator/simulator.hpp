#pragma once

#include <iostream>

#include <network_mgr.hpp>
#include <location_unit.hpp>
#include <vehicle_data_unit.hpp>

class simulator {
 public:
    simulator();
    virtual ~simulator();

    void runFeatureTesting();
    void runLoadTesting();

    network_mgr* getNetworkIns() { return mNetwork; }

 private:
    location_unit* mLocUnit;
    vehicle_data_unit* mVehUnit;
    network_mgr* mNetwork;
};
