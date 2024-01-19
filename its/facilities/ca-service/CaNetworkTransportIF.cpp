#include <CaNetworkTransportIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaNetworkTransportIF"

CaNetworkTransportIF::CaNetworkTransportIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CaNetworkTransportIF::~CaNetworkTransportIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaNetworkTransportIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void CaNetworkTransportIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CaNetworkTransportIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void CaNetworkTransportIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
