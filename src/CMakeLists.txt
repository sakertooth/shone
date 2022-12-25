add_library(shone_core STATIC core/AudioFile.cpp core/AudioBuffer.cpp)
target_include_directories(shone_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(shone_core PUBLIC SndFile::sndfile)
add_library(shone::core ALIAS shone_core)

add_executable(shone Main.cpp)
target_link_libraries(shone PRIVATE shone_core)