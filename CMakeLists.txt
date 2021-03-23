project(AgarioServer)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/engine)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER_NETWORK ${PROJECT_SOURCE_DIR}/network/*.hpp)
file(GLOB SOURCE_NETWORK ${PROJECT_SOURCE_DIR}/network/*.cpp)

file(GLOB HEADER_RENDERER ${PROJECT_SOURCE_DIR}/renderers/*.hpp)
file(GLOB SOURCE_RENDERER ${PROJECT_SOURCE_DIR}/renderers/*.cpp)

file(GLOB SOURCE_MAIN main.cpp)

set(HEADERS
    ${HEADER_NETWORK} ${HEADER_RENDERER}
)

set(SOURCE
    ${SOURCE_MAIN} ${SOURCE_NETWORK} ${SOURCE_RENDERER}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(AgarioServer PUBLIC AgarioEngine_lib -pthread -lsfml-graphics -lsfml-window -lsfml-system)
# target_link_libraries(AgarioServer )