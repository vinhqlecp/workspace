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
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    CheckSendCam();
}

CaService::CaService() {
    printf("[%s] constructor\n", MODULE_NAME);

    mNGenCam = DEFAULT_N_GEN_CAM;
    mTCheckGenCam = T_GenCamMax;
    mTGenCam = T_GenCamMax;
    mTGenCam_DCC = T_GenCamMax;

    mHeader.messageID = messageID_cam;
    mHeader.protocolVersion = 1;  // TODO: don't use fixed code
    mHeader.stationID = 1;  // TODO: don't use fixed code
}

CaService::~CaService() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaService::Start() {
    printf("[%s] started\n", MODULE_NAME);

    mFastSending = false;
    mStart = std::chrono::high_resolution_clock::now();
    SingleShot(T_GenCamMin);
}

void CaService::OnLocationChanged(const LocationPackage::GpsData& data) {
    printf("[%s] location data changed\n", MODULE_NAME);

    printf("-------------------------------\n");
    printf("timestamp = %ld\n", data.timestamp());
    printf("latitude  = %.7f\n", data.latitude());
    printf("longitude = %.7f\n", data.longitude());
    printf("altitude  = %.7f\n", data.altitude());
    printf("speed     = %.3f\n", data.speed());
    printf("bearing   = %.3f\n", data.bearing());
    printf("-------------------------------\n\n");
}

void CaService::OnVehicleChanged(const VehiclePackage::Vehicle& data) {
    printf("[%s] vehicle data changed\n", MODULE_NAME);
}

bool CaService::IsCamTrigger() {
    printf("[%s] Check CAM is ready for sending\n", MODULE_NAME);

    if(IsFirstCam) {
        mFastSending = false;
        mTGenCam = T_GenCamMax;
        return true;
    }

    auto mElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mStart);
    if(mElapsed.count() >= T_GenCamMin) {

    }

    return false;
}

void CaService::CheckSendCam() {
    CAM_t cam;

    if(IsCamTrigger()) {
        printf("[%s] Making CAM\n", MODULE_NAME);
        cam = CollectMandatoryData();

        if(IsOptionalContainers()) {
            CollectOptionalContainers(&cam);
            mLastLowFreq = std::chrono::high_resolution_clock::now();
        }

        IsFirstCam = false;
        mLastCam = cam;
        mStart = std::chrono::high_resolution_clock::now();
        SingleShot(T_GenCamMin);
    } else {
        SingleShot(T_GenCamMin);
    }
}

CAM_t CaService::CollectMandatoryData() {
    printf("[%s] Collect mandatory for CAM\n", MODULE_NAME);
}

bool CaService::IsOptionalContainers() {
    printf("[%s] Check if optional containers are needed\n", MODULE_NAME);

    return false;
}

void CaService::CollectOptionalContainers(CAM_t *cam) {
    printf("[%s] Collect optional container data\n", MODULE_NAME);
}