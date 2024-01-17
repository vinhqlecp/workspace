#include "vehicle_data.hpp"

vehicle_data::vehicle_data(): 
    leftTurnSignal(false), 
    rightTurnSignal(false) {

}

void vehicle_data::getMockingLeftTurnSignal(bool& pVal) {
    pVal = leftTurnSignal;
}

void vehicle_data::getMockingRightTurnSignal(bool& pVal) {
    pVal = rightTurnSignal;
}