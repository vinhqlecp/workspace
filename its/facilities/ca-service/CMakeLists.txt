set(CA_SERVICE_SRCS
    CaService.cpp
)

add_library(ca-service STATIC ${CA_SERVICE_SRCS})
target_link_libraries(ca-service pthread asn)