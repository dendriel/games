#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <stdio.h>


#if defined(DEBUG)
#define debug(fmt,args...) (void)(printf("[debug] %s:%3d - "fmt"\n",__FILE__,__LINE__,##args))
#else
#define debug(...)
#endif

#endif /* DEBUG_HEADER */
