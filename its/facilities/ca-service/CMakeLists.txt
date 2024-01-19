set(CA_SERVICE_SRCS
    CaService.cpp
    ApplicationIF.cpp
    ManagementIF.cpp
    NetworkTransportIF.cpp
    SecurityIF.cpp
    FacilityIF.cpp
    CamEncodeDecode.cpp
    CamReceptionMgmt.cpp
    CamTransmissionMgmt.cpp
)

add_library(ca-service STATIC ${CA_SERVICE_SRCS})
target_link_libraries(ca-service pthread asn)