set(BINARY AgarioServer)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})