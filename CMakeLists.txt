cmake_minimum_required(VERSION 3.2)
project(shone VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_AUTOMOC ON)

find_package(SndFile REQUIRED)
find_package(Aubio REQUIRED)
find_package(Rubberband REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Create core library
add_library(shone_core STATIC 
    src/core/AudioBuffer.cpp
    src/core/AudioFile.cpp
    src/core/Downmix.cpp
    src/core/MidiNote.cpp
    src/core/SndFileHelper.cpp
)

target_include_directories(shone_core 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(shone_core 
    PUBLIC 
    SndFile::sndfile
)

add_library(shone::core ALIAS shone_core)

# Create GUI executable
add_executable(shone
    src/Main.cpp

    ${CMAKE_SOURCE_DIR}/src/gui/MainGui.cpp
    ${CMAKE_SOURCE_DIR}/include/shone/gui/MainGui.hpp

    ${CMAKE_SOURCE_DIR}/src/gui/MainWindow.cpp
    ${CMAKE_SOURCE_DIR}/include/shone/gui/MainWindow.hpp

    ${CMAKE_SOURCE_DIR}/src/gui/PianoRoll.cpp
    ${CMAKE_SOURCE_DIR}/include/shone/gui/PianoRoll.hpp
)

target_link_libraries(shone PRIVATE shone::core Qt5::Widgets)

# Add tests
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
