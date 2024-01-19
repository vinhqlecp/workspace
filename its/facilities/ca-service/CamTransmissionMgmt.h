#pragma once

#include <gps.pb.h>
#include <vehicle.pb.h>

class CaService;

class CamTransmissionMgmt {
public:
    CamTransmissionMgmt();
    virtual ~CamTransmissionMgmt();

    void Initialize(CaService*);
    void Start();
    void SendCam();
    void ProcessRecvLocData(const LocationPackage::GpsData&);

private:
    CaService* mParent;
    LocationPackage::GpsData mLastGps, mCurGps;
};
