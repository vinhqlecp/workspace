set(SIMULATOR_SRCS
   location_unit.cpp
   vehicle_data_unit.cpp
   simulator.cpp
)

add_library(its-sim STATIC ${SIMULATOR_SRCS})
target_link_libraries(its-sim PRIVATE pthread its-proto)