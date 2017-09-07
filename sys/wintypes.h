#pragma once

#include<sys/types.h>


#include <stdint.h>
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

typedef int8_t   __s8;
typedef uint8_t  __u8;
typedef int16_t  __s16;
typedef uint16_t __u16;
typedef int32_t  __s32;
typedef uint32_t __u32;
typedef int64_t  __s64;
typedef uint64_t __u64;


typedef u_int16_t n_short;              
typedef u_int32_t n_long;             
typedef u_int32_t n_time;

typedef uint16_t __be16;
typedef uint16_t __sum16;
typedef uint32_t __be32;


typedef unsigned char	u_char; 
typedef unsigned short	u_short; 
typedef unsigned int	u_int;  
typedef unsigned long	u_long; 
typedef struct _quad { int val[2]; } quad_t;