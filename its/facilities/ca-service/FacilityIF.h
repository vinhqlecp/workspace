#pragma once

#include <Interface.h>

#include <gps.pb.h>
#include <vehicle.pb.h>

class FacilityIF : public Interface {
public:
    FacilityIF();
    virtual ~FacilityIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

    void OnLocationChanged(const LocationPackage::GpsData&);
    void OnVehicleChanged(const VehiclePackage::Vehicle&);

private:
};