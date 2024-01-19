#include <SecurityIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "SecurityIF"

SecurityIF::SecurityIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

SecurityIF::~SecurityIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void SecurityIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void SecurityIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void SecurityIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void SecurityIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
