#pragma once

#include <iostream>

#include <gps.pb.h>

#include <location.hpp>

class simulator;
class location_unit {
 public:
    location_unit(simulator* parent);
    virtual ~location_unit();

    void runFeatureTesting();
    void prepareLocationData(LocationPackage::GpsData* data);

    simulator* getParent() {return mParent; }

 private:
    location* mLoc;
    simulator* mParent;
};
