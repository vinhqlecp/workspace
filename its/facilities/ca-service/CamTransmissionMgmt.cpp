#include <CamTransmissionMgmt.h>

#include <iostream>
#include <cmath>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CamTransmissionMgmt"

#define DEFAULT_N_GEN_CAM 3
#define MAX_REFERENCEPOSITION 40

#define T_GenCamMin 100
#define T_GenCamMax 1000

CamTransmissionMgmt::CamTransmissionMgmt() {
    printf("[%s] constructor\n", MODULE_NAME);

    mLastLocValid = false;
    mIsFirstCam = true;
    mGeneratedCamNum = 1;
    mNGenCam = DEFAULT_N_GEN_CAM;
    mTCheckGenCam = T_GenCamMax;
    mTGenCam = T_GenCamMax;
    mTGenCam_DCC = T_GenCamMax;

    mStationType = StationType_passengerCar;  // TODO: don't use fixed code
}

CamTransmissionMgmt::~CamTransmissionMgmt() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CamTransmissionMgmt::Initialize(CaService* parent) {
    printf("[%s] initalize\n", MODULE_NAME);

    mParent = parent;
}

void CamTransmissionMgmt::Start() {
    printf("[%s] start\n", MODULE_NAME);

    mIsFastSending = false;
    mStartTime = std::chrono::high_resolution_clock::now();
    TimerTrigger(T_GenCamMin);
}

void CamTransmissionMgmt::SendCam() {
    printf("[%s] trigger sending CAM\n", MODULE_NAME);

    CAM_t cam;

    if(IsCamTrigger()) {
        printf("[%s] Making CAM %d\n", MODULE_NAME, mGeneratedCamNum);
        cam = CollectMandatoryData();

        if(IsOptionalContainers()) {
            printf("[%s] Add optional containers\n", MODULE_NAME);
            CollectOptionalContainers(&cam);
            mLastLowFreq = std::chrono::high_resolution_clock::now();
        }

        mIsFirstCam = false;
        mLastCam = cam;
        mStartTime = std::chrono::high_resolution_clock::now();
        TimerTrigger(T_GenCamMin);
    } else {
        TimerTrigger(T_GenCamMin);
    }
}

void CamTransmissionMgmt::ProcessRecvLocData(const LocationPackage::GpsData& data) {
    printf("[%s] process received location data\n", MODULE_NAME);
}

bool CamTransmissionMgmt::IsCamTrigger() {
    // printf("[%s] Check CAM is ready for sending\n", MODULE_NAME);

    if(mIsFirstCam) {
        mIsFastSending = false;
        mTGenCam = T_GenCamMax;
        return true;
    }

    auto mElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mStartTime);
    if(mElapsed.count() >= T_GenCamMin) {
        if(IsGpsDataValid()) {
            if(IsPositionChanged()) {
                mTGenCam = mElapsed.count();
                mGeneratedCamNum = 0;
                mIsFastSending = true;
                return true;
            }

            if(IsHeadingChanged()) {
                mTGenCam = mElapsed.count();
                mGeneratedCamNum = 0;
                mIsFastSending = true;
                return true;
            }
        }

        if(mIsFastSending && mElapsed.count() >= mTGenCam) {
            mGeneratedCamNum++;
            if(mGeneratedCamNum > mNGenCam) {
                mGeneratedCamNum = 0;
                mTGenCam = T_GenCamMax;
                mIsFastSending = false;
            }
            return true;
        }
    }

    if(mElapsed.count() >= mTGenCam && mElapsed.count() >= mTGenCam_DCC)
        return true;

    return false;
}

void CamTransmissionMgmt::TimerTrigger(int delay) {
    std::thread timerThread([this, delay]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        this->SendCam();
    });
    timerThread.detach();
}

CAM_t CamTransmissionMgmt::CollectMandatoryData() {
    // printf("[%s] Collect mandatory for CAM\n", MODULE_NAME);

    CAM_t cam;

    return cam;
}

bool CamTransmissionMgmt::IsOptionalContainers() {
    // printf("[%s] Check if optional containers are needed\n", MODULE_NAME);

    if(mStationType != StationType_roadSideUnit) {
        if(mIsFirstCam)
            return true;

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastLowFreq);
        if(duration.count() >= 500)
            return true;
    }

    return false;
}

void CamTransmissionMgmt::CollectOptionalContainers(CAM_t *cam) {
    // printf("[%s] Collect optional container data\n", MODULE_NAME);
}

bool CamTransmissionMgmt::IsGpsDataValid() {
    mMutexLastLoc.lock();

    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
    if (timestamp - mLastLocData.timestamp() >= 10 * 1000) {
        mLastLocValid = false;
    } else {
        mLastLocValid = true;
    }

    mMutexLastLoc.unlock();
    return mLastLocValid;
}

bool CamTransmissionMgmt::IsPositionChanged() {
    mMutexLastLoc.lock();

    double distance = CalculateDistance(mLastCam.cam.camParameters.basicContainer.referencePosition.latitude, \
                                        mLastCam.cam.camParameters.basicContainer.referencePosition.longitude, \
                                        mLastLocData.latitude(), \
                                        mLastLocData.longitude());
    if(distance > 5.0) {
        mMutexLastLoc.unlock();
        return true;
    }

    mMutexLastLoc.unlock();
    return mLastLocValid;
}

bool CamTransmissionMgmt::IsHeadingChanged() {
    mMutexLastLoc.lock();

    double currentHeading = CalculateHeading(mLastCam.cam.camParameters.basicContainer.referencePosition.latitude, \
                                        mLastCam.cam.camParameters.basicContainer.referencePosition.longitude, \
                                        mLastLocData.latitude(), \
                                        mLastLocData.longitude());
    if(currentHeading != -1) {
        double lastHeading = mLastCam.cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency.heading.headingValue;
        double deltaHeading = currentHeading - lastHeading;
		if (deltaHeading > 180) {
			deltaHeading -= 360;
		} else if (deltaHeading < -180) {
			deltaHeading += 360;
		}
		if(abs(deltaHeading) > 4.0) {
			mMutexLastLoc.unlock();
			return true;
		}
    }

    mMutexLastLoc.unlock();
    return mLastLocValid;
}

double CamTransmissionMgmt::CalculateDistance(double lat1, double lon1, double lat2, double lon2) {
	double R = 6371;  // km
	double dLat = (lat2-lat1) * M_PI/180.0;  //convert to rad
	double dLon = (lon2-lon1) * M_PI/180.0;
	lat1 = lat1 * M_PI/180.0;
	lat2 = lat2 * M_PI/180.0;

	double a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	return R * c * 1000;  //convert to m
}

double CamTransmissionMgmt::CalculateHeading(double lat1, double lon1, double lat2, double lon2) {
	if (CalculateDistance(lat1, lon1, lat2, lon2) < 0.4) {
		return -1;
	}

	double dLat = (lat2-lat1) * M_PI/180.0;  //convert to rad
	double dLon = (lon2-lon1) * M_PI/180.0;
	lat1 = lat1 * M_PI/180.0;

	double phi = atan2(sin(lat1)*dLon, dLat);  //between -pi and +pi
	phi = phi * 180.0/M_PI;  //convert to deg (-180, +180)
	if(phi < 0) {
		phi += 360;  //between 0 and 360 deg
	}
	return phi;
}
