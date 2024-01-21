#pragma once

#include <thread>
#include <chrono>
#include <vector>

#include <gps.pb.h>
#include <vehicle.pb.h>

#include <CAM.h>

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
    bool IsCamTrigger();
    void TimerTrigger(int delay);

    CAM_t CollectMandatoryData();
    bool IsOptionalContainers();
    void CollectOptionalContainers(CAM_t *cam);

    bool IsGpsDataValid();
    bool IsPositionChanged();
    bool IsHeadingChanged();
    double CalculateDistance(double lat1, double lon1, double lat2, double lon2);
    double CalculateHeading(double lat1, double lon1, double lat2, double lon2);

private:
    CaService* mParent;

    uint16_t mGeneratedCamNum;
    uint16_t mTGenCam;
    uint16_t mNGenCam;
    uint16_t mTCheckGenCam;
    uint16_t mTGenCam_DCC;

    bool mIsFirstCam;
    bool mIsFastSending;
    CAM_t mLastCam;

    StationType_t mStationType;

    std::chrono::high_resolution_clock::time_point mStartTime;
    std::chrono::high_resolution_clock::time_point mLastLowFreq;
    std::chrono::system_clock::duration mElapsed;

    bool mLastLocValid;
    std::mutex mMutexLastLoc;
    LocationPackage::GpsData mLastLocData;

    std::vector<ReferencePosition_t> mReferencePositionList;
    std::vector<GenerationDeltaTime_t> mGeneratedDeltaTimeList;
};
