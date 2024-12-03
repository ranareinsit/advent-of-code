find_package(Catch2 REQUIRED)
    
    add_executable(day_03_tests "day_03.cpp")
    
    # Test framework dependencies.
    target_link_libraries(day_03_tests         PRIVATE Catch2::Catch2WithMain)
    
    # Functionality to test.
    target_link_libraries(day_03_tests         PRIVATE day_03)
    
    add_test(NAME day_03_tests_name COMMAND day_03_tests )
    
    # copy input files for each test
    add_custom_command(TARGET day_03_tests  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_03/src/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/src/lib/day_03/src/test-input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
    )