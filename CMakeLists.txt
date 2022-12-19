cmake_minimum_required(VERSION 3.0.0)
project(shone VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(shone src/Main.cpp 
    src/core/AudioBuffer.cpp
    src/core/Mix.cpp
    src/core/PitchAnalyzer.cpp
    src/core/MusicalNote.cpp
    src/core/RubberbandHelper.cpp
    src/core/SndFileHelper.cpp)
    
find_package(SndFile REQUIRED)
find_package(Aubio REQUIRED)
find_package(Rubberband REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(shone PUBLIC SndFile::sndfile Qt5::Widgets ${Rubberband_LIBRARY} ${Aubio_LIBRARY})
target_include_directories(shone PUBLIC ${CMAKE_SOURCE_DIR}/include ${Rubberband_INCLUDE_DIRS} ${Aubio_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
