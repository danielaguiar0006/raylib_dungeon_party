#pragma once

#define TRUE 1
#define FALSE 0

#define INVALID_ENTITY 0

// Unsigned int types
typedef unsigned char u8;        // 1 byte
typedef unsigned short u16;      // 2 bytes
typedef unsigned int u32;        // 4 bytes
typedef unsigned long long u64;  // 8 bytes

// Signed int types
typedef char i8;                 // 1 byte
typedef short i16;               // 2 bytes
typedef int i32;                 // 4 bytes
typedef long long i64;           // 8 bytes

// Floating point types
typedef float f32;               // 4 bytes
typedef double f64;              // 8 bytes

// Boolean type
typedef char b8;                 // 1 byte
typedef char b32;                // 4 byte

// Game specific types
typedef u32 entity;              // 4 bytes
typedef enum {  // Component flags
    COMPONENT_NONE = 0,
    COMPONENT_ACTIVE = 1 << 0,
    COMPONENT_TAG = 1 << 1,
    COMPONENT_TRANSFORM = 1 << 2,
    COMPONENT_SPRITE = 1 << 3,
    COMPONENT_VELOCITY = 1 << 4,
} component_flags;

// NULL definition
#ifndef NULL
#ifdef __cplusplus
#ifndef _WIN64
#define NULL 0
#else
#define NULL 0LL
#endif  /* W64 */
#else
#define NULL ((void *)0)
#endif
#endif

// Properly define static asseritions
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size
/* STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");
 */
