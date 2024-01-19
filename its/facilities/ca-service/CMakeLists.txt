set(CA_SERVICE_SRCS
    CaService.cpp
    CaApplicationIF.cpp
    CaManagementIF.cpp
    CaNetworkTransportIF.cpp
    CaSecurityIF.cpp
    CaFacilityIF.cpp
    CamEncodeDecode.cpp
    CamReceptionMgmt.cpp
    CamTransmissionMgmt.cpp
)

add_library(ca-service STATIC ${CA_SERVICE_SRCS})
target_link_libraries(ca-service pthread asn proto)