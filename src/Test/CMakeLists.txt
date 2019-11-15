
aux_source_directory(. SOURCES)
add_executable(Test ${SOURCES})
message(STATUS "Test:" ${SOURCES})

target_link_libraries(Test
        boost_system
        boost_filesystem
        base)


