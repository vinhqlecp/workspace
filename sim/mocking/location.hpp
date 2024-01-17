#pragma once

#include <iostream>
#include <gps.pb.h>

class location {
 public:
    location();
    virtual ~location();

    void getMockingData(LocationPackage::GpsData* data);

 private:
    double calculateSpeed(double lat, double lon);
    double calculateHeading(double lat, double lon);

 private:
    uint32_t counter;

    double mlastLat, mcurLat;
    double mlastLon, mcurLon; 
};
