#include "vehicle_data_unit.hpp"

vehicle_data_unit::vehicle_data_unit() {
    mVeh = std::shared_ptr<vehicle_data>(new vehicle_data);
    if(mVeh != nullptr) {
        std::cout << "Vehicle data unit is started" << std::endl;
    }
}

void vehicle_data_unit::runFeatureTesting() {
    if(mVeh != nullptr) {
        bool leftTurnSignal, rightTurnSignal;
        mVeh->getMockingLeftTurnSignal(leftTurnSignal);
        mVeh->getMockingRightTurnSignal(rightTurnSignal);
    } else {
        std::cout << "mVeh is NULL" << std::endl;
    }
}