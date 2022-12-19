cmake_minimum_required(VERSION 3.0.0)
project(shone VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(SndFile REQUIRED)
find_package(Aubio REQUIRED)
find_package(Rubberband REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(shone_core STATIC 
    src/core/AudioBuffer.cpp
    src/core/Mix.cpp
    src/core/PitchAnalyzer.cpp
    src/core/PitchSegment.cpp
    src/core/MusicalNote.cpp
    src/core/RubberbandHelper.cpp)

target_include_directories(shone_core PUBLIC ${CMAKE_SOURCE_DIR}/include ${Rubberband_INCLUDE_DIRS} ${Aubio_INCLUDE_DIRS})
target_link_libraries(shone_core PUBLIC SndFile::sndfile Qt5::Widgets ${Rubberband_LIBRARY} ${Aubio_LIBRARY})

add_executable(shone src/Main.cpp)
target_link_libraries(shone PUBLIC shone_core)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
