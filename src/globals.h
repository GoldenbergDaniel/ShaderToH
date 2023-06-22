#pragma once

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

#define print_str(title, data) (printf("%s%s\n", title, data))
#define print_char(title, data) (printf("%s%c\n", title, data))
#define print_int(title, data) (printf("%s%i\n", title, data))
#define print_uint(title, data) (printf("%s%u\n", title, data))
#define print_float(title, data) (printf("%s%f\n", title, data))
#define print_ln() (printf("\n"))
