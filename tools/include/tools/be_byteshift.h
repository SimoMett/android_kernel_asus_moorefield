#ifndef _TOOLS_BE_BYTESHIFT_H
#define _TOOLS_BE_BYTESHIFT_H

#include <stdint.h>
typedef int8_t   __s8;
typedef uint8_t  __u8;
typedef int16_t  __s16;
typedef uint16_t __u16;
typedef int32_t  __s32;
typedef uint32_t __u32;
typedef int64_t  __s64;
typedef uint64_t __u64;

static inline __u16 __get_unaligned_be16(const __u8 *p)
{
	return p[0] << 8 | p[1];
}

static inline __u32 __get_unaligned_be32(const __u8 *p)
{
	return p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
}

static inline __u64 __get_unaligned_be64(const __u8 *p)
{
	return (__u64)__get_unaligned_be32(p) << 32 |
	       __get_unaligned_be32(p + 4);
}

static inline void __put_unaligned_be16(__u16 val, __u8 *p)
{
	*p++ = val >> 8;
	*p++ = val;
}

static inline void __put_unaligned_be32(__u32 val, __u8 *p)
{
	__put_unaligned_be16(val >> 16, p);
	__put_unaligned_be16(val, p + 2);
}

static inline void __put_unaligned_be64(__u64 val, __u8 *p)
{
	__put_unaligned_be32(val >> 32, p);
	__put_unaligned_be32(val, p + 4);
}

static inline __u16 get_unaligned_be16(const void *p)
{
	return __get_unaligned_be16((const __u8 *)p);
}

static inline __u32 get_unaligned_be32(const void *p)
{
	return __get_unaligned_be32((const __u8 *)p);
}

static inline __u64 get_unaligned_be64(const void *p)
{
	return __get_unaligned_be64((const __u8 *)p);
}

static inline void put_unaligned_be16(__u16 val, void *p)
{
	__put_unaligned_be16(val, p);
}

static inline void put_unaligned_be32(__u32 val, void *p)
{
	__put_unaligned_be32(val, p);
}

static inline void put_unaligned_be64(__u64 val, void *p)
{
	__put_unaligned_be64(val, p);
}

#endif /* _TOOLS_BE_BYTESHIFT_H */
