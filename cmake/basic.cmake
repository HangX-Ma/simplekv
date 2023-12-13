# Basic CMakeLists.txt

# collect all files in the following directories and put them into 'SOURCES' variable
set(SIMPLEKV_SRC ${SIMPLEKV_ROOT_DIR}/simplekv.cpp)
set(SIMPLEKV_INC ${SIMPLEKV_ROOT_DIR}/simplekv.h)

add_library(${PROJECT_NAME} ${SIMPLEKV_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${SIMPLEKV_INC})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

add_subdirectory(${SIMPLEKV_ROOT_DIR}/test)


