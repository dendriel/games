/*
 * utils.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef UTILS_H_
#define UTILS_H_

/**************************************************************************************************
 * Time definitions.
 */
#define MILI 1000

/**************************************************************************************************
 * Macro utilities.
 */
//!< Checks and print error if the operation fails.
#define CHK_NULL(_f)\
{\
	if ((_f) == NULL) {\
		cout << "Error occurred at " << #_f << endl;\
		return -1;\
	}\
}

//!< Checks and print error if the operation fails.
#define CHK(_f, _r)\
{\
	if ((_f) == (_r)) {\
		cout << "Error occurred at " << #_f << "; Returned: " << _r << endl;\
		return -1;\
	}\
}

#endif /* UTILS_H_ */
