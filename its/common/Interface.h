#pragma once

class CaService;

class Interface {
public:
    virtual void Initialize(CaService*) = 0;
    virtual void Start() = 0;
    virtual void Send() = 0;
    virtual void Recv() = 0;

protected:
    CaService* mParent;
};