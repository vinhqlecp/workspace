#pragma once

#include <Interface.h>

class CaApplicationIF : public Interface {
public:
    CaApplicationIF();
    virtual ~CaApplicationIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};