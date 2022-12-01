include(CheckIncludeFile)

# Check if we are missing any posix headers we consider required.
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(libgen.h HAVE_LIBGEN_H)
check_include_file(dirent.h HAVE_DIRENT_H)
check_include_file(fnmatch.h HAVE_FNMATCH_H)
check_include_file(getopt.h HAVE_GETOPT_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(dlfcn.h HAVE_DLFCN_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(alloca.h HAVE_ALLOCA_H)

include(CheckSymbolExists)

# Check if we are missing any functions known to exist in platform specific runtimes.
check_symbol_exists(strtrim "string.h" HAVE_STRTRIM)
check_symbol_exists(strlwr "string.h" HAVE_STRLWR)
check_symbol_exists(strupr "string.h" HAVE_STRUPR)
check_symbol_exists(strlcat "string.h" HAVE_STRLCAT)
check_symbol_exists(strlcpy "string.h" HAVE_STRLCPY)
configure_file(string.h.in string.h @ONLY)

add_library(compat STATIC)

if(WIN32)
    target_compile_definitions(compat PUBLIC _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN)
endif()

target_sources(compat PRIVATE
    compat/aliasing.h
    compat/bitfield.h
    compat/callconv.h
    compat/cpuid.h
    compat/debugbreak.h
    compat/endianness.h
    compat/messagebox.h
    compat/rotate.h
    string.c
    ${CMAKE_CURRENT_BINARY_DIR}/string.h
)

target_include_directories(compat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compat ${CMAKE_CURRENT_BINARY_DIR})

# Link needed platform libraries.
if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    target_sources(compat PRIVATE messagebox_win32.c)
    target_link_libraries(compat comdlg32)
elseif("${CMAKE_SYSTEM}" MATCHES "Darwin")
    target_sources(compat PRIVATE messagebox_macos.m)    
    target_link_libraries(compat AppKit)
else()
    find_package(GTK3 COMPONENTS gtk)
    if(GTK3_FOUND)
        target_sources(compat PRIVATE messagebox_gtk.c)
        target_link_libraries(compat ${GTK3_LIBRARIES})
        target_include_directories(compat PRIVATE ${GTK3_INCLUDE_DIRS})
    else()
        target_sources(compat PRIVATE messagebox_null.c)
    endif()
endif()

if(NOT HAVE_STRINGS_H)
    target_sources(compat PRIVATE strings/strings.c strings/strings.h)
    target_include_directories(compat PUBLIC strings)
endif()

if(NOT HAVE_LIBGEN_H)
    target_sources(compat PRIVATE libgen/libgen.c libgen/libgen.h)
    target_include_directories(compat PUBLIC libgen)
endif()

if(NOT HAVE_DIRENT_H)
    target_sources(compat PRIVATE dirent/dirent.c dirent/dirent.h)
    target_include_directories(compat PUBLIC dirent)
endif()

if(NOT HAVE_FNMATCH_H)
    target_sources(compat PRIVATE fnmatch/fnmatch.c fnmatch/fnmatch.h)
    target_include_directories(compat PUBLIC fnmatch)
endif()

if(NOT HAVE_GETOPT_H)
    target_sources(compat PRIVATE getopt/getopt.c getopt/getopt.h)
    target_include_directories(compat PUBLIC getopt)
endif()

if(NOT HAVE_UNISTD_H)
    target_sources(compat PRIVATE unistd/unistd.c unistd/unistd.h)
    target_include_directories(compat PUBLIC unistd)
endif()

if(NOT HAVE_DLFCN_H)
    target_sources(compat PRIVATE dlfcn/dlfcn.c dlfcn/dlfcn.h)
    target_include_directories(compat PUBLIC dlfcn)
endif()

if(NOT HAVE_SYS_TIME_H)
    target_sources(compat PRIVATE systime/time.c systime/sys/time.h)
    target_include_directories(compat PUBLIC systime)
endif()

if(NOT HAVE_ALLOCA_H)
    target_sources(compat PRIVATE alloca/alloca.h)
    target_include_directories(compat PUBLIC alloca)
endif()
