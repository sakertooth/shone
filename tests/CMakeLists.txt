add_executable(ReadAudioFile ReadAudioFile.cpp)
target_link_libraries(ReadAudioFile PRIVATE shone::core)
add_test(ReadAudioFile COMMAND ReadAudioFile)