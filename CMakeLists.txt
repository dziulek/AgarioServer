project(Agario)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/engine)

include_directories(${PROJECT_SOURCE_DIR})



#file(GLOB HEADER_NETWORK ${PROJECT_SOURCE_DIR}/network/*.hpp)
#file(GLOB SOURCE_NETWORK ${PROJECT_SOURCE_DIR}/network/*.cpp)

file(GLOB HEADER_MAIN *.hpp)
file(GLOB SOURCE_MAIN *.cpp)

set(HEADERS
    ${HEADERS_MAIN} ${HEADER_NETWORK}
)

set(SOURCE
    ${SOURCE_MAIN} ${SOURCE_NETWORK}
)

message("${HEADERS}")

add_executable("${PROJECT_NAME}" ${SOURCE} ${HEADERS})

target_link_libraries(Agario AgarioEngine_lib)
target_link_libraries(Agario -lsfml-graphics -lsfml-window -lsfml-system -pthread)