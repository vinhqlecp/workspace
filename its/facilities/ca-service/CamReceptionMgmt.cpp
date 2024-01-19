#include <CamReceptionMgmt.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CamReceptionMgmt"

CamReceptionMgmt::CamReceptionMgmt() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CamReceptionMgmt::~CamReceptionMgmt() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CamReceptionMgmt::Initialize(CaService* parent) {
    printf("[%s] initalize\n", MODULE_NAME);

    mParent = parent;
}

void CamReceptionMgmt::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CamReceptionMgmt::ProcessRecvCam() {
    printf("[%s] process received CAM\n", MODULE_NAME);
}