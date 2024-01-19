#pragma once

#include <Interface.h>

class SecurityIF : public Interface {
public:
    SecurityIF();
    virtual ~SecurityIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};