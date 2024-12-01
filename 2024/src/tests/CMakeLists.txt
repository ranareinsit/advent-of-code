find_package(Catch2 REQUIRED)

#
add_executable(unit-tests_combined unit/lib/foo.cpp     "unit/lib/foo.cpp")
add_executable(example-tests       unit/lib/example.cpp "unit/lib/example.cpp")
add_executable(day_01_tests        unit/lib/day_01.cpp  "unit/lib/day_01.cpp")


# Test framework dependencies.
target_link_libraries(unit-tests_combined PRIVATE Catch2::Catch2WithMain)
target_link_libraries(example-tests       PRIVATE Catch2::Catch2WithMain)
target_link_libraries(day_01_tests        PRIVATE Catch2::Catch2WithMain)


# Functionality to test.
target_link_libraries(unit-tests_combined PRIVATE foo)
target_link_libraries(example-tests       PRIVATE example)
target_link_libraries(day_01_tests        PRIVATE day_01)

#
add_test(NAME unit-tests        COMMAND unit-tests_combined)
add_test(NAME example-tests     COMMAND example-tests)
add_test(NAME day_01_tests_name COMMAND day_01_tests)

#
file(COPY ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/test-input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET day_01_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/input.txt
        ${CMAKE_BINARY_DIR}/src/lib/day_01/src/input.txt
)

add_custom_command(TARGET day_01_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/test-input.txt
        ${CMAKE_BINARY_DIR}/src/lib/day_01/src/test-input.txt
)
