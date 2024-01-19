#pragma once

#include <Interface.h>

class CaNetworkTransportIF : public Interface {
public:
    CaNetworkTransportIF();
    virtual ~CaNetworkTransportIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};