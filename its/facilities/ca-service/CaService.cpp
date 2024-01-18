#include <CaService.h>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaService"

#define MSG_LENGTH  500
#define DEFAULT_N_GEN_CAM 3

#define T_GenCamMin 100
#define T_GenCamMax 1000

static bool IsFirstCam = true;

void CaService::SingleShot(int delay) {
    std::thread timerThread([this, delay]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        this->CheckSendCam();
    });
    timerThread.detach();
}

CaService::CaService() {
    printf("[%s] constructor\n", MODULE_NAME);

    mGeneratedCamNum = 1;
    mNGenCam = DEFAULT_N_GEN_CAM;
    mTCheckGenCam = T_GenCamMax;
    mTGenCam = T_GenCamMax;
    mTGenCam_DCC = T_GenCamMax;

    mStationType = StationType_passengerCar;  // TODO: don't use fixed code

    mHeader.messageID = messageID_cam;
    mHeader.protocolVersion = 1;  // TODO: don't use fixed code
    mHeader.stationID = 1;  // TODO: don't use fixed code

    mIsLocValid = false;
}

CaService::~CaService() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaService::Start() {
    printf("[%s] started\n", MODULE_NAME);

    mFastSending = false;
    mStartTime = std::chrono::high_resolution_clock::now();
    SingleShot(T_GenCamMin);
}

void CaService::OnLocationChanged(const LocationPackage::GpsData& data) {
    // printf("[%s] location data changed\n", MODULE_NAME);

    if(!mIsLocValid) {
        mIsLocValid = true;

        mLastLocData.set_timestamp(data.timestamp());
        mLastLocData.set_latitude(data.latitude());
        mLastLocData.set_longitude(data.longitude());
        mLastLocData.set_altitude(data.altitude());
        mLastLocData.set_speed(data.speed());
        mLastLocData.set_bearing(data.bearing());
    }
}

void CaService::OnVehicleChanged(const VehiclePackage::Vehicle& data) {
    // printf("[%s] vehicle data changed\n", MODULE_NAME);
}

bool CaService::IsCamTrigger() {
    // printf("[%s] Check CAM is ready for sending\n", MODULE_NAME);

    if(IsFirstCam) {
        mFastSending = false;
        mTGenCam = T_GenCamMax;
        return true;
    }

    auto mElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mStartTime);
    if(mElapsed.count() >= T_GenCamMin) {
        if(mIsLocValid) {
            // if(mLastLocData.bearing() * 10 > 40.0f) {
            //     mTGenCam = mElapsed.count();
            //     mGeneratedCamNum = 1;
            //     mFastSending = true;
            //     mIsLocValid = false;
            //     return true;
            // }

            if(mLastLocData.speed() * 10 > 50.0f) {
                mTGenCam = mElapsed.count();
                mGeneratedCamNum = 1;
                mFastSending = true;
                mIsLocValid = false;
                return true;
            }
        }

        if(mFastSending && mElapsed.count() >= mTGenCam) {
            mGeneratedCamNum++;
            if(mGeneratedCamNum > mNGenCam) {
                mGeneratedCamNum = 0;
                mTGenCam = T_GenCamMax;
                mFastSending = false;
            }
            return true;
        }
    }

    if(mElapsed.count() >= mTGenCam && mElapsed.count() >= mTGenCam_DCC)
        return true;

    return false;
}

void CaService::CheckSendCam() {
    CAM_t cam;

    if(IsCamTrigger()) {
        printf("[%s] Making CAM %d\n", MODULE_NAME, mGeneratedCamNum);
        cam = CollectMandatoryData();

        if(IsOptionalContainers()) {
            printf("[%s] Add optional containers\n", MODULE_NAME);
            CollectOptionalContainers(&cam);
            mLastLowFreq = std::chrono::high_resolution_clock::now();
        }

        IsFirstCam = false;
        mLastCam = cam;
        mStartTime = std::chrono::high_resolution_clock::now();
        SingleShot(T_GenCamMin);
    } else {
        SingleShot(T_GenCamMin);
    }
}

CAM_t CaService::CollectMandatoryData() {
    // printf("[%s] Collect mandatory for CAM\n", MODULE_NAME);
}

bool CaService::IsOptionalContainers() {
    // printf("[%s] Check if optional containers are needed\n", MODULE_NAME);

    if(mStationType != StationType_roadSideUnit) {
        if(IsFirstCam)
            return true;

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastLowFreq);
        if(duration.count() >= 500)
            return true;
    }

    return false;
}

void CaService::CollectOptionalContainers(CAM_t *cam) {
    // printf("[%s] Collect optional container data\n", MODULE_NAME);
}