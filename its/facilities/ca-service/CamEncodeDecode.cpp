#include <CamEncodeDecode.h>

#include <iostream>

#ifdef MODULE_NAME
#undef MODULE_NAME
#endif
#define MODULE_NAME "CamEncodeDecode"

CamEncodeDecode::CamEncodeDecode() {
    printf("[%s] constructor\n", MODULE_NAME);
}

CamEncodeDecode::~CamEncodeDecode() {
    printf("[%s] destructor\n", MODULE_NAME);
}

void CamEncodeDecode::Initialize(CaService* parent) {
    printf("[%s] initalize\n", MODULE_NAME);

    mParent = parent;
}

void CamEncodeDecode::Start() {
    printf("[%s] start\n", MODULE_NAME);
}

void CamEncodeDecode::EncodeCam() {
    printf("[%s] encode CAM\n", MODULE_NAME);
}

void CamEncodeDecode::DecodeCam() {
    printf("[%s] decode CAM\n", MODULE_NAME);
}