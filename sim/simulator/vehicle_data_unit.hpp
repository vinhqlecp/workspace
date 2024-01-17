#pragma once

#include <iostream>
#include <memory>

#include "vehicle_data.hpp"

class vehicle_data_unit {
 public:
    vehicle_data_unit();
    ~vehicle_data_unit() {}

    void runFeatureTesting();

 private:
    std::shared_ptr<vehicle_data> mVeh;
};
