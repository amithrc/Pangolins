#ifndef PANGOLINS_COMMON_DEFS_H
#define PANGOLINS_COMMON_DEFS_H

#include<stdbool.h>

/* Unsigned  data types  */
#define UINT8  unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned int
#define UINT64 unsigned long

/* Signed data types */
#define SINT8  singed char
#define SINT16 sgined short
#define SINT32  signed int
#define SINT64 signed long

#define CHAR char

#define TRUE  true
#define FALSE false

#define PREDICT_TRUE(x)   __builtin_expect (!!(x), 1)
#define PREDICT_FALSE(x)  __builtin_expect (!!(x), 0)

typedef enum{
    E_NO_LOCK   = 0x0,
    E_MUTX_LOCK = 0x1,
    E_SPIN_LOCK = 0x2
}LOCK_TYPE;

#define IS_MUTX_LOCK(lock_type) ( lock_type == E_MUTX_LOCK )
#define IS_SPIN_LOCK(lock_type) ( lock_type == E_SPIN_LOCK )
#define IS_NO_LOCK(lock_type) ( !IS_MUTX_LOCK(lock_type) && \
                                !IS_SPIN_LOCK(lock_type) )

#define CHECK_FOR_TIME_OUT( start_time, num_secs ) ( time(0) >= ( start_time + num_secs ) )
#define DefineOptions(option_name , bit)  B_##option_name = bit , M_##option_name = ( 1 << B_##option_name)

#endif //PANGOLINS_COMMON_DEFS_H
