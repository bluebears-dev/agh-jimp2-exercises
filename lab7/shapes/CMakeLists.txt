project(shapes)

set(HEDEAR_FILES Shapes.h)
set(SOURCE_FILES Shapes.cpp)

add_library(libshapes STATIC ${SOURCE_FILES})
target_include_directories(libshapes PUBLIC .)
target_link_libraries(libshapes libpoint)

add_executable(shapes ${SOURCE_FILES} main.cpp)

target_link_libraries(shapes libshapes)
