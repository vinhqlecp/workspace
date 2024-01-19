#include <ManagementIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "ManagementIF"

ManagementIF::ManagementIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

ManagementIF::~ManagementIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void ManagementIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void ManagementIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void ManagementIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void ManagementIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
