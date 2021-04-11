project(AgarioServer)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(src)

add_subdirectory(src/network)
add_subdirectory(tests)
add_subdirectory(lib/AgarioEngine)
add_subdirectory(lib/json)

target_link_libraries(AgarioServer PUBLIC AgarioEngine_lib -pthread)