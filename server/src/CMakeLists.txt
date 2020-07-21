find_package(Boost 1.40.0 REQUIRED system)
include_directories( ${Boost_INCLUDE_DIR} )

add_subdirectory(general)

add_executable(server main.cpp)

target_link_libraries(server l_general pthread ${Boost_LIBRARIES})