#pragma once

class CaService;

class CamEncodeDecode {
public:
    CamEncodeDecode();
    virtual ~CamEncodeDecode();

    void Initialize(CaService*);
    void Start();
    void EncodeCam();
    void DecodeCam();

private:
    CaService* mParent;
};