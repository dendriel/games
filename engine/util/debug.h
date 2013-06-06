#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <stdio.h>

/**
 *	\b Define debug macro output.
 */
#if defined(DEBUG)
#define DEBUG_HEADER_MSG "[debug]"
#define debug(fmt,args...) (void)(printf("%s %15s:%3d -\t "fmt"\n",DEBUG_HEADER_MSG,__FILE__,__LINE__,##args))
#else
#define debug(...)
#endif

/**
 *	\b Define debug error macro output.
 */
#if defined(DEBUG_ERROR)
#define DEBUG_ERROR_HEADER_MSG "[error]"
#define error(fmt,args...) (void)(printf("%s %15s:%s():%3d - "fmt"\n",DEBUG_ERROR_HEADER_MSG,__FILE__,__func__,__LINE__,##args))
#else
#define error(...)
#endif

/**
 *	\b Define critical macro output.
 */
#if defined(DEBUG_CRITICAL)
#define DEBUG_CRITICAL_HEADER_MSG "[critical]"
#define critical(fmt,args...) (void)(printf("%s %15s:%s():%3d - "fmt"\n",DEBUG_CRITICAL_HEADER_MSG,__FILE__,__func__,__LINE__,##args))
#else
#define critical(...)
#endif

/**
 *	\b Define screen debug (WARNING: this is a verbose debug).
 */
#if defined(DEBUG_SCREEN)
#define DEBUG_SCREEN_HEADER_MSG "[gVideo_screen]"
#define debug_screen(fmt,args...) (void)(printf("%s %15s:%3d - "fmt"\n",DEBUG_SCREEN_HEADER_MSG,__FILE__,__LINE__,##args))
#else
#define debug_screen(...)
#endif


#endif /* DEBUG_HEADER */
