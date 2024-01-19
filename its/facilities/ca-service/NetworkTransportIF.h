#pragma once

#include <Interface.h>

class NetworkTransportIF : public Interface {
public:
    NetworkTransportIF();
    virtual ~NetworkTransportIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};