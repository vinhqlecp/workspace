set(MOCKING_SRCS
   location.cpp
   vehicle_data.cpp
)

add_library(its-mocking STATIC ${MOCKING_SRCS})
target_link_libraries(its-mocking PRIVATE pthread)