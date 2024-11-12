add_library(example STATIC src/example.cpp)

target_include_directories(example
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS example
        EXPORT exampleConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT exampleConfig DESTINATION share/example/cmake)
export(TARGETS example FILE exampleConfig.cmake)
