#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include <gps.pb.h>
#include <vehicle.pb.h>

#include <CAM.h>
#include <VehicleDataProvider.h>

class CaService {
public:
    CaService();
    virtual ~CaService();

    void Start();
    void OnLocationChanged(const LocationPackage::GpsData&);
    void OnVehicleChanged(const VehiclePackage::Vehicle&);
    
    void CheckSendCam();

private:
    bool IsCamTrigger();
    void SingleShot(int delay);

    CAM_t CollectMandatoryData();
    bool IsOptionalContainers();
    void CollectOptionalContainers(CAM_t *cam);

private:
    CAM_t mCurrentCam;
    CAM_t mLastCam;

    uint16_t mGeneratedCamNum;
    uint16_t mTGenCam;
    uint16_t mNGenCam;
    uint16_t mTCheckGenCam;
    uint16_t mTGenCam_DCC;

    ItsPduHeader_t mHeader;

    bool mFastSending;

    std::chrono::high_resolution_clock::time_point mStartTime;
    std::chrono::high_resolution_clock::time_point mLastLowFreq;
    std::chrono::system_clock::duration mElapsed;

    StationType_t mStationType;

    bool mIsLocValid;
    LocationPackage::GpsData mLastLocData;
};
