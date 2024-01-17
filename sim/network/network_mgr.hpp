#pragma once 

#include <networkif.hpp>

class network_mgr {
public:
    network_mgr();
    virtual ~network_mgr();

    networkif* getCurrentNet() { return mEcalComm; }

private:
    networkif* mEcalComm;
};
