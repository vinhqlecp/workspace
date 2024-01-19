#pragma once

#include <unordered_map>
#include <cstdint>

class Interface;
class CamEncodeDecode;
class CamTransmissionMgmt;
class CamReceptionMgmt;
class VehicleDataProvider;

class CaService {
public:
    static CaService* GetInstance();
    virtual ~CaService();

    void Initialize(VehicleDataProvider* vdp);
    void Start();

    // Getters
    CamEncodeDecode* GetEnDecIns() { return mEnDec; }
    Interface* GetInterfaceIns(uint16_t id) { return mIF[id]; }
    CamTransmissionMgmt* GetCamTranMgmtIns() { return mTrans; }
    CamReceptionMgmt* GetCamReptMgmtIns() { return mRecv; }

private:
    CaService();

private:
    static CaService* mIns;

    std::unordered_map<uint16_t, Interface*> mIF;

    CamEncodeDecode* mEnDec;
    CamTransmissionMgmt* mTrans;
    CamReceptionMgmt* mRecv;
    VehicleDataProvider* mVdp;
};
