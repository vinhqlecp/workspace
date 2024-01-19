#pragma once

#include <Interface.h>

class ManagementIF : public Interface {
public:
    ManagementIF();
    virtual ~ManagementIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};