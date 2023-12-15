# Basic CMakeLists.txt

set(SIMPLEKV_SRCS src/simplekv.cpp)

if(SIMPLEKV_BUILD_SHARED OR BUILD_SHARED_LIBS)
    add_library(simplekv SHARED ${SIMPLEKV_SRCS} ${SIMPLEKV_ALL_HEADERS})
else()
    add_library(simplekv STATIC ${SIMPLEKV_SRCS} ${SIMPLEKV_ALL_HEADERS})
endif()
add_library(simplekv::simplekv ALIAS simplekv)
target_include_directories(simplekv PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

simplekv_enable_warnings(simplekv)

set_target_properties(simplekv PROPERTIES VERSION ${SIMPLEKV_VERSION} SOVERSION
                                                                      ${SIMPLEKV_VERSION_MAJOR}.${SIMPLEKV_VERSION_MINOR})
set_target_properties(simplekv PROPERTIES DEBUG_POSTFIX d)

if(SIMPLEKV_BUILD_TESTS)
    message(STATUS "Generating tests")
    enable_testing()
    add_subdirectory(tests)
endif()
