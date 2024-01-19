#include <CaManagementIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaManagementIF"

CaManagementIF::CaManagementIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CaManagementIF::~CaManagementIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaManagementIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void CaManagementIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CaManagementIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void CaManagementIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
