#include <NetworkTransportIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "NetworkTransportIF"

NetworkTransportIF::NetworkTransportIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

NetworkTransportIF::~NetworkTransportIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void NetworkTransportIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void NetworkTransportIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void NetworkTransportIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void NetworkTransportIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
