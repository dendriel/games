#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

/**************************************************************************************************
 * Debug utilities.
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


#endif /* DEBUG_H_ */
