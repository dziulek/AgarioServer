project(Test)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_subdirectory(${PROJECT_SOURCE_DIR}/../engine/glm)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER_NETWORK ${PROJECT_SOURCE_DIR}/network/*.hpp)
file(GLOB SOURCE_NETWORK ${PROJECT_SOURCE_DIR}/network/*.cpp)

file(GLOB_RECURSE HEADER_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.hpp)
file(GLOB_RECURSE SOURCE_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.cpp)

file(GLOB_RECURSE HEADER_RENDERER ${PROJECT_SOURCE_DIR}/renderers/*.hpp)
file(GLOB_RECURSE SOURCE_RENDERER ${PROJECT_SOURCE_DIR}/renderers/*.cpp)

file(GLOB SOURCE_MAIN test.cpp)

set(HEADERS
    ${HEADER_RENDERER} ${HEADER_ENGINE}
)

set(SOURCE
    ${SOURCE_MAIN} ${SOURCE_RENDERER} ${SOURCE_ENGINE}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(Test glm)