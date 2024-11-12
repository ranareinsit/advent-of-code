find_package(Catch2 3 REQUIRED)

add_executable(unit-tests_combined unit/lib/foo.cpp "unit/lib/foo.cpp")
add_executable(example-tests unit/lib/example.cpp "unit/lib/example.cpp")


# Test framework dependencies.
target_link_libraries(unit-tests_combined PRIVATE Catch2::Catch2WithMain)
target_link_libraries(example-tests PRIVATE Catch2::Catch2WithMain)

# Functionality to test.
target_link_libraries(unit-tests_combined PRIVATE foo)
target_link_libraries(example-tests PRIVATE example)


add_test(NAME unit-tests COMMAND unit-tests_combined)
add_test(NAME example-tests COMMAND example-tests)

