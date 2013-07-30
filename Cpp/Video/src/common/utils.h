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

/**************************************************************************************************
 * Math utilities.
 */
/**
 * \brief Find x from a matrix with the array index.
 * \param index The position of the element in array representation.
 * \param x_max The width of the matrix.
 * \return The x coordinate in matrix representation.
 */
inline unsigned int find_x(const unsigned int index, const unsigned int x_max)
{
	return ((index % x_max) );
}
/**
 * \brief Find y from a matrix with the array index.
 * \param index The position of the element in array representation.
 * \param x_max The width of the matrix.
 * \param x The x coordinate that must be previous calculated.
 * \return The y coordinate in matrix representation.
 */
inline unsigned int find_y(const unsigned int index, const unsigned int x_max, const unsigned int x)
{
	return (((index - x)/x_max) );
}

/**
 * \brief Find the width of a surface from the array tile set length.
 */
#define find_width(_array_size, _x_max)\
{\
	return (find_x(_array_size, _x_max) * x_max);\
}

/**
 * \brief Find the height of a surface from the array tile set length.
 */
#define find_height(_array_size, _x_max, _x)\
{\
	return (find_y(_array_size, _x_max, _x) * _x_max);\
}

#endif /* UTILS_H_ */
