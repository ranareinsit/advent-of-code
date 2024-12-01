add_library(day_01 STATIC "src/common.cpp")

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

#
add_executable(day_01_exec src/main.cpp)
target_link_libraries(day_01_exec PRIVATE day_01)

#
add_executable(day_01_part_02 src/part-02.cpp)
target_link_libraries(day_01_part_02 PRIVATE day_01)


file(COPY src/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/test-input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET day_01 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/input.txt
        ${CMAKE_BINARY_DIR}/src/lib/day_01/src/input.txt
)

add_custom_command(TARGET day_01 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/lib/day_01/src/test-input.txt
        ${CMAKE_BINARY_DIR}/src/lib/day_01/src/test-input.txt
)
