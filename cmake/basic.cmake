# Basic CMakeLists.txt

# collect all files in the following directories and put them into 'SOURCES' variable
set(SIMPLEKV_SRC ${SIMPLEKV_ROOT_DIR}/simplekv.cpp)
set(SIMPLEKV_INC ${SIMPLEKV_ROOT_DIR}/simplekv.h)

add_library(${PROJECT_NAME} ${SIMPLEKV_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${SIMPLEKV_INC})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

if (NOT GTest_FOUND)
    message(STATUS "GTest not found, download it from Github.")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
    add_library(GTest::GTest INTERFACE IMPORTED)
    target_link_libraries(GTest::GTest INTERFACE gtest_main)
endif()

enable_testing()
include_directories(${GTEST_INCLUDE_DIR})
add_subdirectory(${SIMPLEKV_ROOT_DIR}/test)


