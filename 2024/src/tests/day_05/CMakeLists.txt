find_package(Catch2 REQUIRED)
    
    add_executable(day_05_tests "day_05.cpp")
    
    # Test framework dependencies.
    target_link_libraries(day_05_tests         PRIVATE Catch2::Catch2WithMain)
    
    # Functionality to test.
    target_link_libraries(day_05_tests         PRIVATE day_05)
    
    add_test(NAME day_05_tests_name COMMAND day_05_tests )
    
    # copy input files for each test
    add_custom_command(TARGET day_05_tests  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_05/src/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_05/src/test-input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
    )