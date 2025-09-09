
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(test_source ${TEST_SOURCES})

    get_filename_component(test_name ${test_source} NAME_WE)
    message(STATUS "Configuring test: ${test_name}")
    
    add_executable(${test_name}_test ${test_source})
    
    target_link_libraries(${test_name}_test PRIVATE VantagePointLib)

    target_include_directories(${test_name}_test PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )
    
    add_test(NAME ${test_name} COMMAND ${test_name}_test)
    
    set_target_properties(${test_name}_test PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()