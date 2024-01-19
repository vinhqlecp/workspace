#include <CaService.h>
#include <Constants.h>
#include <CaApplicationIF.h>
#include <CaFacilityIF.h>
#include <CaManagementIF.h>
#include <CaNetworkTransportIF.h>
#include <CaSecurityIF.h>
#include <CamEncodeDecode.h>
#include <CamTransmissionMgmt.h>
#include <CamReceptionMgmt.h>
#include <VehicleDataProvider.h>

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

    mIF[InterfaceId_Application] = new CaApplicationIF;
    mIF[InterfaceId_Management] = new CaManagementIF;
    mIF[InterfaceId_NetworkTransport] = new CaNetworkTransportIF;
    mIF[InterfaceId_Security] = new CaSecurityIF;
    mIF[InterfaceId_Facility] = new CaFacilityIF;

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

void CaService::Initialize(VehicleDataProvider* vdp) {
    printf("[%s] initalize\n", MODULE_NAME);

    for(uint16_t i = InterfaceId_Application; i < InterfaceId_Max; i++) {
        mIF[i]->Initialize(this);
    }
    mEnDec->Initialize(this);
    mTrans->Initialize(this);
    mRecv->Initialize(this);
    
    mVdp = vdp;
    CaFacilityIF* facIfPtr = static_cast<CaFacilityIF*>(mIF[InterfaceId_Facility]);
    if(mIF[InterfaceId_Facility] != nullptr) {
        mVdp->RegisterLocCallback(std::bind(&CaFacilityIF::OnLocationChanged, facIfPtr, std::placeholders::_1));
        mVdp->RegisterVehCallback(std::bind(&CaFacilityIF::OnVehicleChanged, facIfPtr, std::placeholders::_1));
    }
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