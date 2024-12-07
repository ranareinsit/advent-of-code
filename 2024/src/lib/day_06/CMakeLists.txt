#
add_library(day_06 STATIC "src/common.cpp")

#
add_executable(day_06_part_01_exec "src/part_01.cpp")
target_link_libraries(day_06_part_01_exec PRIVATE day_06)

#
add_executable(day_06_part_02_exec "src/part_02.cpp")
target_link_libraries(day_06_part_02_exec PRIVATE day_06)

#
add_custom_command(TARGET day_06 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_06/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_06/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
)

#
target_include_directories(day_06
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_06
        EXPORT day_06Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_06Config DESTINATION share/day_06/cmake)
export(TARGETS day_06 FILE day_06Config.cmake)