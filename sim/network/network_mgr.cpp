#include <network_mgr.hpp>

#include <ecal.hpp>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "Network Manager"

network_mgr::network_mgr() {
    printf("%s constructor\n", MODULE_NAME);

    mEcalComm = new ecal();
    mEcalComm->start();
}

network_mgr::~network_mgr() {
    printf("%s destructor\n", MODULE_NAME);

    if(mEcalComm) {
        delete mEcalComm;
        mEcalComm = nullptr;
    }
}