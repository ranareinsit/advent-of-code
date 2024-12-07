#
add_library(day_07 STATIC "src/common.cpp")

#
add_executable(day_07_part_01_exec "src/part_01.cpp")
target_link_libraries(day_07_part_01_exec PRIVATE day_07)

#
add_executable(day_07_part_02_exec "src/part_02.cpp")
target_link_libraries(day_07_part_02_exec PRIVATE day_07)

#
add_custom_command(TARGET day_07 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_07/src/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_07/src/test-input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test-input.txt
)

#
target_include_directories(day_07
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_07
        EXPORT day_07Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_07Config DESTINATION share/day_07/cmake)
export(TARGETS day_07 FILE day_07Config.cmake)