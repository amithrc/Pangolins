#ifndef PANGOLINS_EM_DEFS_H
#define PANGOLINS_EM_DEFS_H
#include<stdbool.h>

/* Unsigned  data types  */
#define UINT8  unsinged char
#define UINT16 unsigned short
#define UINT32 unsigned int
#define UINT64 unsigned long

/* Signed data types    */
#define SINT8  singed char
#define SINT16 sgined short
#define SINT32  signed int
#define SINT64 signed long

#define TRUE  true
#define FALSE false

#define PREDICT_TRUE(x)   __builtin_expect (!!(x), 1)
#define PREDICT_FALSE(x)  __builtin_expect (!!(x), 0)

/* Defining lock type to use */
typedef enum E_LOCK_TYPE
{
    E_NO_LOCK   = 0x0,
    E_MUTX_LOCK = 0x1,
    E_SPIN_LOCK = 0x2,
    E_LOCK_MAX
}T_LOCK_TYPE;

#define IS_MUTX_LOCK(lock_type) ( lock_type == E_MUTX_LOCK )
#define IS_SPIN_LOCK(lock_type) ( lock_type == E_SPIN_LOCK )

#endif //PANGOLINS_EM_DEFS_H
