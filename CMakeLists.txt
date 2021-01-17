project(Agario)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/engine/glm)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER_NETWORK ${PROJECT_SOURCE_DIR}/network/*.hpp)
file(GLOB SOURCE_NETWORK ${PROJECT_SOURCE_DIR}/network/*.cpp)

#file(GLOB HEADER_SA ${PROJECT_SOURCE_DIR}/engine/shapes/*.hpp)
#file(GLOB SOURCE_ENGINE ${PROJECT_SOURCE_DIR}/engine/shapes/*.cpp)

file(GLOB_RECURSE HEADER_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.hpp)
file(GLOB_RECURSE SOURCE_ENGINE ${PROJECT_SOURCE_DIR}/engine/*.cpp)

file(GLOB HEADER_MAIN *.hpp)
file(GLOB SOURCE_MAIN *.cpp)

set(HEADERS
    ${HEADERS_MAIN} ${HEADER_NETWORK} ${HEADER_ENGINE}
)

set(SOURCE
    ${SOURCE_MAIN} ${SOURCE_NETWORK} ${SOURCE_ENGINE}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(Agario glm)
target_link_libraries(Agario -lsfml-graphics -lsfml-window -lsfml-system -pthread)