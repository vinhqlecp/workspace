#include <CaApplicationIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CaApplicationIF"

CaApplicationIF::CaApplicationIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CaApplicationIF::~CaApplicationIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CaApplicationIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void CaApplicationIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CaApplicationIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void CaApplicationIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
