#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED

#include <stdio.h>


#if defined(DEBUG_ON)
#define DEBUG(fmt,args...) (void)(printf("[debug] %s:%3d - "fmt"\n",__FILE__,__LINE__,##args))
#else
#define DEBUG(...)
#endif

#endif /* DEBUG_INCLUDED */
