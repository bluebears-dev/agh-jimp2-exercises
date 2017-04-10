project(student_repository)

set(HEDEAR_FILES StudentRepository.h)
set(SOURCE_FILES StudentRepository.cpp)

add_library(libstudentrepository STATIC ${SOURCE_FILES})
target_include_directories(libstudentrepository PUBLIC .)

add_executable(student_repository ${SOURCE_FILES} main.cpp)

target_link_libraries(student_repository libstudentrepository)
