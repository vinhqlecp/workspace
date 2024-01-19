#include <CamTransmissionMgmt.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CamTransmissionMgmt"

CamTransmissionMgmt::CamTransmissionMgmt() {
    printf("[%s] constructor\n", MODULE_NAME);
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
}

void CamTransmissionMgmt::SendCam() {
    printf("[%s] send CAM\n", MODULE_NAME);
}

void CamTransmissionMgmt::ProcessRecvLocData() {
    printf("[%s] process received location data\n", MODULE_NAME);
}