#pragma once

class CaService;

class CamReceptionMgmt {
public:
    CamReceptionMgmt();
    virtual ~CamReceptionMgmt();

    void Initialize(CaService*);
    void Start();
    void ProcessRecvCam();

private:
    CaService* mParent;
};
