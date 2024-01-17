set(VDP_SRCS
    VehicleDataProvider.cpp
)

add_library(vdp STATIC ${VDP_SRCS})
target_link_libraries(vdp proto eCAL::core)