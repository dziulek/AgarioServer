project(AgarioServer)

# set(${BINARY} AgarioServer)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(src)

add_subdirectory(lib/AgarioEngine/src)
add_subdirectory(src/network)

add_executable(AgarioServer_run main.cpp)

set(C_LIB ${CMAKE_BINARY_DIR}/libcombi.a)

add_custom_target(combinedGen
    COMMAND ar -x $<TARGET_FILE:AgarioServer_lib>
    COMMAND ar -x $<TARGET_FILE:AgarioEngine_lib>
    COMMAND ar -qcs ${C_LIB} *.o
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS AgarioServer_lib AgarioEngine_lib
)

add_library(combined STATIC IMPORTED GLOBAL)
add_dependencies(combined combinedGen)

set_target_properties(combined PROPERTIES IMPORTED_LOCATION ${C_LIB})

target_link_libraries(AgarioServer_run combined)
target_link_libraries(AgarioServer_run -pthread)





# add_subdirectory(tests)

add_subdirectory(lib/json)