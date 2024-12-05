#
add_library(day_05 STATIC "src/common.cpp")

#
add_executable(day_05_part_01_exec "src/part_01.cpp")
target_link_libraries(day_05_part_01_exec PRIVATE day_05)

#
add_executable(day_05_part_02_exec "src/part_02.cpp")
target_link_libraries(day_05_part_02_exec PRIVATE day_05)

#
add_custom_command(TARGET day_05 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_05/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_05/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
)

#
target_include_directories(day_05
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_05
        EXPORT day_05Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_05Config DESTINATION share/day_05/cmake)
export(TARGETS day_05 FILE day_05Config.cmake)