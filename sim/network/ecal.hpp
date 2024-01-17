#pragma once

#include <string>

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <vehicle.pb.h>
#include <object.pb.h>

#include <networkif.hpp>

class ecal : public networkif {
public:
    ecal();
    virtual ~ecal();

    void start() override;
    
    void recvMsg(const char*, const StackPackage::Object&);
    void publishLocationData(const LocationPackage::GpsData data) override;
    void publishVehicleData(const VehiclePackage::Vehicle data);

private:
    eCAL::protobuf::CPublisher<LocationPackage::GpsData> *mLocPub;
    eCAL::protobuf::CPublisher<VehiclePackage::Vehicle> *mVehPub;
    eCAL::protobuf::CSubscriber<StackPackage::Object> *mObjSub;
};
