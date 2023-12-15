# Get simplekv version from include/simplekv/version.h and put it in SIMPLEKV_VERSION
function(simplekv_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/simplekv/version.h" file_contents)
    string(REGEX MATCH "SIMPLEKV_VER_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from simplekv/version.h")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "SIMPLEKV_VER_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from simplekv/version.h")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "SIMPLEKV_VER_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from simplekv/version.h")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    # With PARENT_SCOPE option you change value of variable in the parent scope, but a variable in the current scope is unchanged.
    set(SIMPLEKV_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(SIMPLEKV_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(SIMPLEKV_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(SIMPLEKV_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()

# Turn on warnings on the given target
function(simplekv_enable_warnings target_name)
    if(SIMPLEKV_BUILD_WARNINGS)
        target_compile_options(
            ${target_name}
            PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
                    -Wall
                    -Wextra
                    -Wconversion
                    -pedantic
                    -Werror
                    -Wfatal-errors>)
    endif()
endfunction()

# Enable address sanitizer (gcc/clang only)
function(simplekv_enable_sanitizer target_name)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "Sanitizer supported only for gcc/clang")
    endif()
    message(STATUS "Address sanitizer enabled")
    target_compile_options(${target_name} PRIVATE -fsanitize=address,undefined)
    target_compile_options(${target_name} PRIVATE -fno-sanitize=signed-integer-overflow)
    target_compile_options(${target_name} PRIVATE -fno-sanitize-recover=all)
    target_compile_options(${target_name} PRIVATE -fno-omit-frame-pointer)
    target_link_libraries(${target_name} PRIVATE -fsanitize=address,undefined -fuse-ld=lld)
endfunction()