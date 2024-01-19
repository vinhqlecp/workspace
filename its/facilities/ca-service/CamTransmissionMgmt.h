#pragma once

class CaService;

class CamTransmissionMgmt {
public:
    CamTransmissionMgmt();
    virtual ~CamTransmissionMgmt();

    void Initialize(CaService*);
    void Start();
    void SendCam();
    void ProcessRecvLocData();

private:
    CaService* mParent;
};
