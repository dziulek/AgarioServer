add_subdirectory(glm)

file(GLOB_RECURSE SOURCE_SHAPES ./shapes/*.cpp)

file(GLOB_RECURSE SOURCE_MAPS ./maps/*.cpp)

file(GLOB_RECURSE SOURCE_CORE ./*.cpp)

set(SOURCE_FILES ${SOURCE_SHAPES} ${SOURCE_SHAPES} ${SOURCE_CORE})

add_library(AgarioEngine_lib STATIC ${SOURCE_FILES})