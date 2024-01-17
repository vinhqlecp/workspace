#pragma once

class vehicle_data {
 public:
    vehicle_data();
    ~vehicle_data() {}

    void getMockingLeftTurnSignal(bool&);
    void getMockingRightTurnSignal(bool&);

 private:
    bool leftTurnSignal;
    bool rightTurnSignal;
};
