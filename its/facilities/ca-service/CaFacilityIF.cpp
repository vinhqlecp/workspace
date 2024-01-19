#include <CaFacilityIF.h>
#include <CaService.h>
#include <CamTransmissionMgmt.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaFacilityIF"

CaFacilityIF::CaFacilityIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CaFacilityIF::~CaFacilityIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaFacilityIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void CaFacilityIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CaFacilityIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void CaFacilityIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}

void CaFacilityIF::OnLocationChanged(const LocationPackage::GpsData& data) {
    printf("[%s] Location data changed\n", MODULE_NAME);

    mParent->GetCamTranMgmtIns()->ProcessRecvLocData(data);
}

void CaFacilityIF::OnVehicleChanged(const VehiclePackage::Vehicle&) {
    printf("[%s] Vehicle data changed\n", MODULE_NAME);
}

