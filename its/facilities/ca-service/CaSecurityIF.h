#pragma once

#include <Interface.h>

class CaSecurityIF : public Interface {
public:
    CaSecurityIF();
    virtual ~CaSecurityIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};