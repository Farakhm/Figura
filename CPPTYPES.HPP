// CPPTYPES:
// Pre-defined constants & types

#define FALSE 0
#define TRUE  1

#ifndef NULL
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define NULL    0
#  else
#    define NULL    0L
#  endif
#endif

typedef unsigned char boolean;
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long int dword;
typedef double real;
