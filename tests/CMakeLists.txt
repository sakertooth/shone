add_executable(ReadAudioFile ReadAudioFile.cpp)
target_link_libraries(ReadAudioFile PRIVATE shone::core)
add_test(ReadAudioFile ReadAudioFile)

file(COPY ${CMAKE_SOURCE_DIR}/tests/files/Sine_wave_440.wav DESTINATION ${CMAKE_BINARY_DIR}/tests)