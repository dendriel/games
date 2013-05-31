#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <stdio.h>

/**
 *	\b Define debug macro output.
 */
#if defined(DEBUG)
#define DEBUG_HEADER_MSG "[debug]"
#define debug(fmt,args...) (void)(printf("%s %s:%3d - "fmt"\n",DEBUG_HEADER_MSG,__FILE__,__LINE__,##args))
#else
#define debug(...)
#endif

/**
 *	\b Define critical macro output.
 */
#if defined(DEBUG_CRITICAL)
#define DEBUG_CRITICAL_HEADER_MSG "[critical]"
#define critical(fmt,args...) (void)(printf("%s %s:%3d - "fmt"\n",DEBUG_CRITICAL_HEADER_MSG,__FILE__,__LINE__,##args))
#else
#define critical(...)
#endif

#endif /* DEBUG_HEADER */
