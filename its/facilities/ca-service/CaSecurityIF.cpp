#include <CaSecurityIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaSecurityIF"

CaSecurityIF::CaSecurityIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CaSecurityIF::~CaSecurityIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaSecurityIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void CaSecurityIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CaSecurityIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void CaSecurityIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
