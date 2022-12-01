cmake_minimum_required(VERSION 3.19)

# Disable default MSVC warning level so we can set it ourselves.
if(POLICY CMP0092)
    cmake_policy(SET CMP0092 NEW)
endif()

# Set a module path so we can find our own custom modules.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(FeatureSummary)

# Default to release for single target generators if nothing specified.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)
endif()

# We don't support in tree builds, so help people make the right choice.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

project(business VERSION 1.0.0 LANGUAGES C CXX)

# Set up a format target to do automated clang format checking.
find_package(ClangFormat)
include(ClangFormat)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    set(WINDOWS TRUE)
endif()

# Set where the build results will end up
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(WINDOWS AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    option(BUILD_STANDALONE "Build the standalone binary." ON)
    option(BUILD_DLL "Build the injection dll." ON)

    add_feature_info(DllBuild BUILD_DLL "Injectable dlls")
else()
    set(STANDALONE TRUE)
endif()

add_feature_info(Standalone BUILD_STANDALONE "Standalone binary generation")

add_subdirectory(deps/compat)
add_subdirectory(deps/wing)

# Build the game exe.
add_subdirectory(src)

feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features:")
