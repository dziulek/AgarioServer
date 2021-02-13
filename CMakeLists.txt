project(AgarioServer)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/engine)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER_NETWORK ${PROJECT_SOURCE_DIR}/network/*.hpp)
file(GLOB SOURCE_NETWORK ${PROJECT_SOURCE_DIR}/network/*.cpp)

# file(GLOB_RECURSE HEADER_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.hpp)
# file(GLOB_RECURSE SOURCE_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.cpp)

file(GLOB SOURCE_MAIN main.cpp)

set(HEADERS
    ${HEADER_NETWORK}
)

set(SOURCE
    ${SOURCE_MAIN} ${SOURCE_NETWORK}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(AgarioServer PUBLIC AgarioEngine_lib -pthread)
# target_include_directories(AgarioServer "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/engine")