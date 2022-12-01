/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Intrinsic for instructions used as a break point for debuggers.
 *
 * @copyright JustBusiness is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef COMPAT_DEBUGBREAK_H
#define COMPAT_DEBUGBREAK_H

#if defined __GNUC__ || defined __clang__
#define trap_inline extern __attribute__((gnu_inline, always_inline)) inline
#else
#define trap_inline inline
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_debugtrap)
#define debugbreak() __builtin_debugtrap()
#elif defined _WIN32 && !defined __WATCOMC__
#include <intrin.h>
#define debugbreak() __debugbreak()
/* If we have GCC or compiler that tries to be compatible, use GCC inline assembly. */
#elif defined __GNUC__ || defined __clang__
#if defined(__i386__) || defined(__x86_64__)
trap_inline void debugbreak(void)
{
    __asm__ volatile("int $0x03");
}
#elif defined(__arm__)
trap_inline void debugbreak(void)
{
    __asm__ volatile("bkpt #3");
}
#elif defined(__aarch64__)
trap_inline void debugbreak(void)
{
    /* same values as used by msvc __debugbreak on arm64 */
    __asm__ volatile("brk #0xF000");
}
#elif defined(__powerpc__)
trap_inline void debugbreak(void)
{
    __asm__ volatile(".4byte 0x7d821008");
}
#else
#error debugbreak not currently supported on this processor platform, see debugbreak.h
#endif /* CPU architectures on GCC like compilers */
#elif defined __WATCOMC__
void debugbreak(void);
#pragma aux debugbreak = "int 3"
#endif

#undef trap_inline

#endif /* COMPAT_DEBUGBREAK_H */
