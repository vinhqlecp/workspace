#pragma once

#include <string>

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <gps.pb.h>
#include <vehicle.pb.h>

using namespace std;

typedef std::function<void(const LocationPackage::GpsData&)> CallbackLocFunction;
typedef std::function<void(const VehiclePackage::Vehicle&)> CallbackVehFunction;

class VehicleDataProvider {
public:
    VehicleDataProvider();
    virtual ~VehicleDataProvider();

    void Start();
    void RegisterLocCallback(CallbackLocFunction cb);
    void RegisterVehCallback(CallbackVehFunction cb);

private:
    void RecvLocMsg(const char*, const LocationPackage::GpsData&);
    void RecvVehMsg(const char*, const VehiclePackage::Vehicle&);

private:
    eCAL::protobuf::CSubscriber<LocationPackage::GpsData> *mLocSub;
    eCAL::protobuf::CSubscriber<VehiclePackage::Vehicle> *mVehSub;

    CallbackLocFunction m_LocCallback;
    CallbackVehFunction m_VehCallback;
};
