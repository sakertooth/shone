cmake_minimum_required(VERSION 3.0.0)
project(shone VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(shone src/Main.cpp 
    src/core/AudioFile.cpp
    src/core/AudioFrame.cpp
    src/core/PitchAnalyzer.cpp
    src/core/PitchSegment.cpp
    src/core/MusicalNote.cpp
    src/core/SndFileHelper.cpp)
    
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/portaudio)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(SndFile REQUIRED)
find_package(Aubio REQUIRED)
find_package(SoundTouch REQUIRED)

target_link_libraries(shone PUBLIC Qt5::Widgets SndFile::sndfile SoundTouch PortAudio ${Aubio_LIBRARY})
target_include_directories(shone PUBLIC ${CMAKE_SOURCE_DIR}/include ${Aubio_INCLUDE_DIRS})