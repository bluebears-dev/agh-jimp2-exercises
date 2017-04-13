project(wordcounter)

set(HEDEAR_FILES WordCounter.h)
set(SOURCE_FILES WordCounter.cpp)

add_library(libwordcounter STATIC ${SOURCE_FILES})
target_include_directories(libwordcounter PUBLIC .)

add_executable(word_counter ${SOURCE_FILES} main.cpp)

target_link_libraries(word_counter libwordcounter)
