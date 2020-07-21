add_subdirectory(general)

add_executable(server main.cpp)

target_link_libraries(server l_general)