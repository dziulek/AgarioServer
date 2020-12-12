project(Agario)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glm)


include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER_SHAPES ${PROJECT_SOURCE_DIR}/shapes/*.hpp)
file(GLOB SOURCE_SHAPES ${PROJECT_SOURCE_DIR}/shapes/*.cpp)

file(GLOB HEADER_MAPS ${PROJECT_SOURCE_DIR}/maps/*.hpp)
file(GLOB SOURCE_MAPS ${PROJECT_SOURCE_DIR}/maps/*.cpp)

file(GLOB HEADER_MAIN *.hpp)
file(GLOB SOURCE_MAIN *.cpp)

set(HEADERS
    ${HEADER_SHAPES} ${HEADER_MAPS} ${HEADERS_MAIN}
)

set(SOURCE
    ${SOURCE_SHAPES} ${SOURCE_MAPS} ${SOURCE_MAIN}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(Agario glm)
target_link_libraries(Agario -lsfml-graphics -lsfml-window -lsfml-system)