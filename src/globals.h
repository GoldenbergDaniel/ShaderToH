#pragma once

#define BUFFER_SIZE 32

#define TRUE 1
#define FALSE 0

typedef unsigned char bool;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef float f32;
typedef double f64;

#define arr_len(arr) (sizeof (arr) / sizeof (arr[0]))
#define arr_ptr_len(arr) (sizeof (*arr) / sizeof (arr[0]))

#define log(msg) (printf("%s\n", msg))
#define log_char(caption, data) (printf("%s%c\n", caption, data))
#define log_int(caption, data) (printf("%s%i\n", caption, data))
#define log_uint(caption, data) (printf("%s%u\n", caption, data))
#define log_float(caption, data) (printf("%s%f\n", caption, data))

// Assert index safety: throws error when i >= len
#define assert_range(i, len) (assert((i) < (len)))
