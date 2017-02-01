#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if !defined(__unix__) && (defined(__APPLE__) || defined(__linux__))
#define __unix__ 1
#endif

#ifndef NATIVE_LITTLE_ENDIAN
#define NATIVE_LITTLE_ENDIAN
#endif

#define COMPILER_ASSERT(X) (void)sizeof(char[(X) ? 1 : -1])

#define ROTL32(x, b) (uint32_t)(((x) << (b)) | ((x) >> (32 - (b))))
#define ROTL64(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))

#define LOAD64_LE(SRC) load64_le(SRC)
static inline uint64_t load64_le(const uint8_t src[8])
{
#ifdef NATIVE_LITTLE_ENDIAN
    uint64_t w;
    memcpy(&w, src, sizeof w);
    return w;
#else
    uint64_t w = (uint64_t)src[0];
    w |= (uint64_t)src[1] << 8;
    w |= (uint64_t)src[2] << 16;
    w |= (uint64_t)src[3] << 24;
    w |= (uint64_t)src[4] << 32;
    w |= (uint64_t)src[5] << 40;
    w |= (uint64_t)src[6] << 48;
    w |= (uint64_t)src[7] << 56;
    return w;
#endif
}

#define STORE64_LE(DST, W) store64_le((DST), (W))
static inline void store64_le(uint8_t dst[8], uint64_t w)
{
#ifdef NATIVE_LITTLE_ENDIAN
    memcpy(dst, &w, sizeof w);
#else
    dst[0] = (uint8_t)w;
    w >>= 8;
    dst[1] = (uint8_t)w;
    w >>= 8;
    dst[2] = (uint8_t)w;
    w >>= 8;
    dst[3] = (uint8_t)w;
    w >>= 8;
    dst[4] = (uint8_t)w;
    w >>= 8;
    dst[5] = (uint8_t)w;
    w >>= 8;
    dst[6] = (uint8_t)w;
    w >>= 8;
    dst[7]     = (uint8_t)w;
#endif
}

#define LOAD32_LE(SRC) load32_le(SRC)
static inline uint32_t load32_le(const uint8_t src[4])
{
#ifdef NATIVE_LITTLE_ENDIAN
    uint32_t w;
    memcpy(&w, src, sizeof w);
    return w;
#else
    uint32_t w = (uint32_t)src[0];
    w |= (uint32_t)src[1] << 8;
    w |= (uint32_t)src[2] << 16;
    w |= (uint32_t)src[3] << 24;
    return w;
#endif
}

#define STORE32_LE(DST, W) store32_le((DST), (W))
static inline void store32_le(uint8_t dst[4], uint32_t w)
{
#ifdef NATIVE_LITTLE_ENDIAN
    memcpy(dst, &w, sizeof w);
#else
    dst[0] = (uint8_t)w;
    w >>= 8;
    dst[1] = (uint8_t)w;
    w >>= 8;
    dst[2] = (uint8_t)w;
    w >>= 8;
    dst[3]     = (uint8_t)w;
#endif
}

/* ----- */

#define LOAD64_BE(SRC) load64_be(SRC)
static inline uint64_t load64_be(const uint8_t src[8])
{
#ifdef NATIVE_BIG_ENDIAN
    uint64_t w;
    memcpy(&w, src, sizeof w);
    return w;
#else
    uint64_t w = (uint64_t)src[7];
    w |= (uint64_t)src[6] << 8;
    w |= (uint64_t)src[5] << 16;
    w |= (uint64_t)src[4] << 24;
    w |= (uint64_t)src[3] << 32;
    w |= (uint64_t)src[2] << 40;
    w |= (uint64_t)src[1] << 48;
    w |= (uint64_t)src[0] << 56;
    return w;
#endif
}

#define LOAD32_BE(SRC) load32_be(SRC)
static inline uint32_t load32_be(const uint8_t src[4])
{
#ifdef NATIVE_BIG_ENDIAN
    uint32_t w;
    memcpy(&w, src, sizeof w);
    return w;
#else
    uint32_t w = (uint32_t)src[3];
    w |= (uint32_t)src[2] << 8;
    w |= (uint32_t)src[1] << 16;
    w |= (uint32_t)src[0] << 24;
    return w;
#endif
}

#define STORE64_BE(DST, W) store64_be((DST), (W))
static inline void store64_be(uint8_t dst[8], uint64_t w)
{
#ifdef NATIVE_BIG_ENDIAN
    memcpy(dst, &w, sizeof w);
#else
    dst[7] = (uint8_t)w;
    w >>= 8;
    dst[6] = (uint8_t)w;
    w >>= 8;
    dst[5] = (uint8_t)w;
    w >>= 8;
    dst[4] = (uint8_t)w;
    w >>= 8;
    dst[3] = (uint8_t)w;
    w >>= 8;
    dst[2] = (uint8_t)w;
    w >>= 8;
    dst[1] = (uint8_t)w;
    w >>= 8;
    dst[0] = (uint8_t)w;
#endif
}

#define STORE32_BE(DST, W) store32_be((DST), (W))
static inline void store32_be(uint8_t dst[4], uint32_t w)
{
#ifdef NATIVE_BIG_ENDIAN
    memcpy(dst, &w, sizeof w);
#else
    dst[3] = (uint8_t)w;
    w >>= 8;
    dst[2] = (uint8_t)w;
    w >>= 8;
    dst[1] = (uint8_t)w;
    w >>= 8;
    dst[0] = (uint8_t)w;
#endif
}

static const uint8_t zero[64] = { 0 };
