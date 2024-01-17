set(NETWORK_SRCS
   ecal.cpp
   network_mgr.cpp
)

add_library(its-network STATIC ${NETWORK_SRCS})
target_link_libraries(its-network PRIVATE pthread its-proto eCAL::core)