project(movie_subtitles)

set(HEDEAR_FILES MovieSubtitles.h)
set(SOURCE_FILES MovieSubtitles.cpp)

add_library(libmoviesubtitles STATIC ${SOURCE_FILES})
target_include_directories(libmoviesubtitles PUBLIC .)

add_executable(movie_subtitles ${SOURCE_FILES} main.cpp)

target_link_libraries(movie_subtitles libmoviesubtitles)
