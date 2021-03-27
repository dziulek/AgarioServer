project(AgarioServer)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src/network)
add_subdirectory(tests)
add_subdirectory(lib/AgarioEngine)

target_link_libraries(AgarioServer PUBLIC AgarioEngine_lib -pthread)