find_package(Catch2 REQUIRED)
    
    add_executable(day_06_tests "day_06.cpp")
    
    # Test framework dependencies.
    target_link_libraries(day_06_tests         PRIVATE Catch2::Catch2WithMain)
    
    # Functionality to test.
    target_link_libraries(day_06_tests         PRIVATE day_06)
    
    add_test(NAME day_06_tests_name COMMAND day_06_tests )
    
    # copy input files for each test
    add_custom_command(TARGET day_06_tests  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_06/src/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_06/src/test-input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
    )