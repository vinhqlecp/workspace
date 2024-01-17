#pragma once

#include <gps.pb.h>

class networkif {
public:
    virtual void start() = 0;
    virtual void publishLocationData(const LocationPackage::GpsData data) = 0;
};
