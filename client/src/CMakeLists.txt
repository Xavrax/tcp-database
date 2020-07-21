find_package(Boost 1.40.0 REQUIRED system)
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(client main.cpp)

target_link_libraries(client pthread ${Boost_LIBRARIES})