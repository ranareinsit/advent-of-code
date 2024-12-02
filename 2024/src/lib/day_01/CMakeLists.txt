#
add_library(day_01 STATIC src/common.cpp)

#
add_executable(day_01_part_01 src/part_01.cpp)
target_link_libraries(day_01_part_01 PRIVATE day_01)

#
add_executable(day_01_part_02 src/part_02.cpp)
target_link_libraries(day_01_part_02 PRIVATE day_01)

#
add_custom_command(TARGET day_01 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
)

#
target_include_directories(day_01
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_01
        EXPORT day_01Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_01Config DESTINATION share/day_01/cmake)
export(TARGETS day_01 FILE day_01Config.cmake)
