#include <FacilityIF.h>
#include <CaService.h>
#include <CamTransmissionMgmt.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "FacilityIF"

FacilityIF::FacilityIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

FacilityIF::~FacilityIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void FacilityIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void FacilityIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void FacilityIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void FacilityIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}

void FacilityIF::OnLocationChanged(const LocationPackage::GpsData& data) {
    printf("[%s] Location data changed\n", MODULE_NAME);

    mParent->GetCamTranMgmtIns()->ProcessRecvLocData(data);
}

void FacilityIF::OnVehicleChanged(const VehiclePackage::Vehicle&) {
    printf("[%s] Vehicle data changed\n", MODULE_NAME);
}

