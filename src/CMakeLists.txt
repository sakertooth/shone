find_package(SndFile REQUIRED)
find_package(Aubio REQUIRED)
find_package(Rubberband REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Create core library
add_library(shone_core STATIC
    core/AudioFile.cpp
    core/AudioBuffer.cpp
    core/SndFileHelper.cpp
    core/Downmix.cpp
)

target_include_directories(shone_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(shone_core PUBLIC
    SndFile::sndfile
)

add_library(shone::core ALIAS shone_core)

# Create shone executable
add_executable(shone Main.cpp)
target_link_libraries(shone PRIVATE
    shone::core
    cxxopts::cxxopts
)