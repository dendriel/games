#ifndef MACROS_HEADER
#define MACROS_HEADER

#include "game_defines.h"
#include "debug.h"

/**************************************************************************************************/
/**
 *	\b Return GAME_RET_UNITIALIZED if validation is false.
 */
#define CHECK_INITIALIZED(flag) if (!flag) {error("Sub-module not initialized."); return GAME_RET_UNINITIALIZED;}

/**************************************************************************************************/
/**
 *	\b Check success or return the exception value.
 */
#define CHECK_EXCEPT(f, except)\
	{\
		en_game_return_code ret;\
		if ((ret = (f)) == except) {\
			return except;\
		}\
		else if (ret != GAME_RET_SUCCESS) {\
			return GAME_RET_ERROR;\
		}\
	}

/**************************************************************************************************/
/**
 *	\b Check success or print error msg and return the exception value.
 */
#define CHECK_ERROR_EXCEPT(f, except, fmt, args...)\
	{\
		en_game_return_code ret;\
		if ((ret = (f)) == except) {\
			return except;\
		}\
		else if (ret != GAME_RET_SUCCESS) {\
			error(fmt, ##args);\
			return GAME_RET_ERROR;\
		}\
	}

/**************************************************************************************************/
/**
 *	\b Fill the v_elem structure automatic loading the image.
 */
#define BRAIN_FILLNLOAD_V_ELEM(elem, t, x, y, img, k)\
	{\
		elem.type = t;\
		elem.h = x;\
		elem.v = y;\
		elem.key = k;\
		if (img != NULL) {\
			elem.image = load_bitmap(img, NULL);\
			if (elem.image == NULL) {\
				error("Failed to load bitmap.");\
				return GAME_RET_ERROR;\
			}\
		}\
	}

/**************************************************************************************************/
/**
 *	\b Copy the visal data pointed by "from" to "dest".
 */
#define BRAIN_FILL_V_ELEM(dest, from)\
	{\
		dest.type = from.type;\
		dest.h = from.h;\
		dest.v = from.v;\
		dest.image = from.image;\
	}

/**************************************************************************************************/
/**
 *	\b Simplify the use of strerror_r.
 */
#define strerror_buf_len 256
#define STRERROR_R(error)\
	{\
		char *buf[strerror_buf_len];\
		strerror_r(error, buf, strerror_buf_len);\
	}


#endif /* MACROS_HEADER */
