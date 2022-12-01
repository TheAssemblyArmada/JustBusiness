#ifndef COMPAT_BITFIELD_H
#define COMPAT_BITFIELD_H

/*
 * Use this macro to mark a structure to be packed in an MSVC compatible way.
 */
#if defined __clang__ || defined __GNUC__
#define BITFIELD_STRUCT __attribute__((ms_struct))
#else
#define BITFIELD_STRUCT
#endif

#endif /* COMPAT_BITFIELD_H*/
