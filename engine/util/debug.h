#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED

#include <stdio.h>


#if defined(DEBUG_ON)
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif /* DEBUG_INCLUDED */
