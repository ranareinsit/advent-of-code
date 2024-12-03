#
add_library(day_03 STATIC "src/common.cpp")

#
add_executable(day_03_part_01_exec "src/part_01.cpp")
target_link_libraries(day_03_part_01_exec PRIVATE day_03)

#
add_executable(day_03_part_02_exec "src/part_02.cpp")
target_link_libraries(day_03_part_02_exec PRIVATE day_03)

#
add_custom_command(TARGET day_03 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_03/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_03/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_03/src/test-input2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input2.txt
)

#
target_include_directories(day_03
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_03
        EXPORT day_03Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_03Config DESTINATION share/day_03/cmake)
export(TARGETS day_03 FILE day_03Config.cmake)