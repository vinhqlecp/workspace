#pragma once

#include <Interface.h>

class ApplicationIF : public Interface {
public:
    ApplicationIF();
    virtual ~ApplicationIF();

    void Initialize(CaService*) override;
    void Start() override;
    void Send() override;
    void Recv() override;

private:
};