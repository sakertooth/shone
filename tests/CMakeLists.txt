function(CreateTest TestName)
    add_executable(${TestName} ${TestName}.cpp)
    target_include_directories(${TestName} PUBLIC ${PROJECT_SOURCE_DIR}/src/core)
    target_link_libraries(${TestName} PUBLIC shone_core)
    add_test(${TestName} ${TestName})
endfunction()

CreateTest(StretchOneSemitone)
CreateTest(ReadAudioFile)

file(COPY ${PROJECT_SOURCE_DIR}/tests/files DESTINATION ${PROJECT_BINARY_DIR}/tests)