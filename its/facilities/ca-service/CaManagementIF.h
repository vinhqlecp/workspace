#pragma once

#include <Interface.h>

class CaManagementIF : public Interface {
public:
    CaManagementIF();
    virtual ~CaManagementIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};