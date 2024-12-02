#
add_library(day_02 STATIC src/common.cpp)

#
add_executable(day_02_part_01 src/part_01.cpp)
target_link_libraries(day_02_part_01 PRIVATE day_02)

#
add_executable(day_02_part_02 src/part_02.cpp)
target_link_libraries(day_02_part_02 PRIVATE day_02)

#
add_custom_command(TARGET day_02 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_02/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_02/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
)

#
target_include_directories(day_02
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_02
        EXPORT day_02Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_02Config DESTINATION share/day_02/cmake)
export(TARGETS day_02 FILE day_02Config.cmake)
