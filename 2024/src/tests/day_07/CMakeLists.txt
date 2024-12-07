find_package(Catch2 REQUIRED)
    
    add_executable(day_07_tests "day_07.cpp")
    
    # Test framework dependencies.
    target_link_libraries(day_07_tests         PRIVATE Catch2::Catch2WithMain)
    
    # Functionality to test.
    target_link_libraries(day_07_tests         PRIVATE day_07)
    
    add_test(NAME day_07_tests_name COMMAND day_07_tests )
    
    # copy input files for each test
    add_custom_command(TARGET day_07_tests  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_07/src/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_07/src/test-input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
    )