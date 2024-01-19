#include <CaService.h>
#include <Constants.h>
#include <ApplicationIF.h>
#include <FacilityIF.h>
#include <ManagementIF.h>
#include <NetworkTransportIF.h>
#include <SecurityIF.h>
#include <CamEncodeDecode.h>
#include <CamTransmissionMgmt.h>
#include <CamReceptionMgmt.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaService"

CaService* CaService::mIns = nullptr;

CaService* CaService::GetInstance() {
    if(mIns == nullptr) {
        mIns = new CaService;
    }
    return mIns;
}

CaService::CaService() {
    printf("[%s] constructor\n", MODULE_NAME);

    mIF[InterfaceId_Application] = new ApplicationIF;
    mIF[InterfaceId_Management] = new ManagementIF;
    mIF[InterfaceId_NetworkTransport] = new NetworkTransportIF;
    mIF[InterfaceId_Security] = new SecurityIF;
    mIF[InterfaceId_Facility] = new FacilityIF;

    mEnDec = new CamEncodeDecode;
    mTrans = new CamTransmissionMgmt;
    mRecv = new CamReceptionMgmt;
}

CaService::~CaService() {
    printf("[%s] constructor\n", MODULE_NAME);

    for(uint16_t i = InterfaceId_Application; i < InterfaceId_Max; i++) {
        if(mIF[i] != nullptr) {
            delete mIF[i];
            mIF[i] = nullptr;
        }
    }

    if(mEnDec != nullptr) {
        delete mEnDec;
        mEnDec = nullptr;
    }

    if(mTrans != nullptr) {
        delete mTrans;
        mTrans = nullptr;
    }

    if(mRecv != nullptr) {
        delete mRecv;
        mRecv = nullptr;
    }
}

void CaService::Initialize() {
    printf("[%s] initalize\n", MODULE_NAME);

    for(uint16_t i = InterfaceId_Application; i < InterfaceId_Max; i++) {
        mIF[i]->Initialize(this);
    }
    mEnDec->Initialize(this);
    mTrans->Initialize(this);
    mRecv->Initialize(this);
}

void CaService::Start() {
    printf("[%s] start\n", MODULE_NAME);

    for(uint16_t i = InterfaceId_Application; i < InterfaceId_Max; i++) {
        mIF[i]->Start();
    }
    mEnDec->Start();
    mTrans->Start();
    mRecv->Start();
}