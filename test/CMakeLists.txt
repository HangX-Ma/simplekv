# compile all tests
aux_source_directory(. EXECUTABLE_FILES)
foreach(FILE_NAME ${EXECUTABLE_FILES})
    get_filename_component(EXECUTABLE_FILE_NAME ${FILE_NAME} NAME_WE)
    add_executable(${EXECUTABLE_FILE_NAME} ${FILE_NAME})
    target_link_libraries(${EXECUTABLE_FILE_NAME}
        PRIVATE
            ${PROJECT_NAME}
            ${CMAKE_THREAD_LIBS_INIT}
            GTest::GTest
            GTest::Main
    )
    target_include_directories(${EXECUTABLE_FILE_NAME} PRIVATE ${SIMPLEKV_ROOT_DIR})
    gtest_discover_tests(${EXECUTABLE_FILE_NAME})
endforeach()

enable_testing()

add_test(
    NAME basic_test
    COMMAND $<TARGET_FILE:basic_test>#
)