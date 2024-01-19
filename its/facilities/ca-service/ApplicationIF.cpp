#include <ApplicationIF.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "ApplicationIF"

ApplicationIF::ApplicationIF() {
    printf("[%s] constructor\n", MODULE_NAME);
}

ApplicationIF::~ApplicationIF() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void ApplicationIF::Initialize(CaService* parent) {
    printf("[%s] initialize\n", MODULE_NAME);

    mParent = parent;
}

void ApplicationIF::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void ApplicationIF::Send() {
    printf("[%s] send data\n", MODULE_NAME);
}

void ApplicationIF::Recv() {
    printf("[%s] receive data\n", MODULE_NAME);
}
