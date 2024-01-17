#pragma once

#include <iostream>

#include <gps.pb.h>
#include <vehicle.pb.h>

#include <CAM.h>
#include <VehicleDataProvider.h>

class CaService {
public:
    CaService();
    virtual ~CaService();

    void Start();
    void onLocationChanged(const LocationPackage::GpsData&);
    void onVehicleChanged(const VehiclePackage::Vehicle&);

private:
};
