/*
 * Gpos.h
 *
 *  Created on: 09/11/2013
 *      Author: vitor
 */

#ifndef GPOS_H_
#define GPOS_H_

#include "util.h"

/**
 * \brief Define Game Positioning auxiliary functions. Should be used to make calculations
 * for a matrix positioning system from a 2D based game.
 */
class Gpos {

public:
	/**
	 * \brief Find out what area of a rectangle a point is in.
	 * \parameter x The point horizontal coordinates;
	 * \parameter y The point vertical coordinates;
	 * \parameter rect_size_w The weight of the rectangle;
	 * \parameter rect_size_h The height of the rectangle;
	 * \parameter rect_origin_x The x origin of the rectangle (given a cartesian plan);
	 * \parameter rect_origin_y The h origin of the rectangle (given a cartesian plan);
	 * \return 0 = first area; 1 = second area; 2 = third area; 3 = fourth area.
	 *
	 * \note *There is no need to be an equilateral rectangle.
	 *
	 * Example (user view):
	 *
	 * 		+-------------------------+
	 * 		| .       area #0       . |
	 * 		|    .               .    |
	 * 		|       .         .       |
	 *		|          .   .          |
	 *		+  area #3   +   area #1  +
	 *		|          .   .          |
	 *		|       .         .       |
	 *		|    .               .    |
	 *		| .       area #2       . |
	 *		+-------------------------+
	 *
	 *
	 * Developer view:
	 *
	 *  The areas (0, 1, 2 and 3) will be subdivided in 2 triangles to be viable to determine
	 * the point are in the map. Something like this:
	 *
	 *
	 *                     area #0
	 * 			+-------------------------+
	 * 			| .     0.1  |  0.2     . |
	 * 			|    .       |       .    |
	 * 			|       .    |    .       |
	 *			|  3.1     . | .    1.1   |
	 * area #3	+------------+------------+ area #1
	 *			|  3.2     . | .    1.2   |
	 *			|       .    |    .       |
	 *			|    .       |       .    |
	 *			| .     2.1  | 2.2      . |
	 *			+-------------------------+
	 *                    area #2
	 *
	 *
	 *         px1        px2|px3        px4
	 * 		py1	+-------------------------+
	 * 			| .     0.1  |  0.2     . |
	 * 			|    .       |       .    |
	 * 			|       .    |    .       |
	 *		py2	|  3.1     . | .    1.1   |
	 *		py3	+------------+------------+
	 *			|  3.2     . | .    1.2   |
	 *			|       .    |    .       |
	 *			|    .       |       .    |
	 *			| .     2.1  | 2.2      . |
	 *		py4	+-------------------------+
	 *
	 */
	static unsigned short get_point_area(
			const int x,
			const int y,
			const int rect_size_w,
			const int rect_size_h,
			const int rect_origin_x = 0,
			const int rect_origin_y = 0)
	{
		int px1, px2, px3, px4;
		int py1, py2, py3, py4;

		px1 = rect_origin_x;
		px2 = rect_origin_x + (rect_size_w/2) - 1;
		px3 = rect_origin_x + (rect_size_w/2);
		px4 = rect_origin_x + (rect_size_w - 1);

		py1 = rect_origin_y;
		py2 = rect_origin_y + (rect_size_h/2) - 1;
		py3 = rect_origin_y + (rect_size_h/2);
		py4 = rect_origin_y + (rect_size_h - 1);

		debug("%d %d %d %d; %d %d %d %d", px1, px2, px3, px4, py1, py2, py3, py4);

		// Area 0
		// sub-area 1
		if (point_in_triangle(x, y, px1,py1, px2,py1, px1,py2) ||
		// sub-area 2
			point_in_triangle(x, y, px3,py1, px4,py1, px3,py2)) {
			return 0;
		}


		return 3;
	}

private:
	/**
	 * \note Find out if a point is inside a rectangle.
	 * Retrieved from:
	 *  http://stackoverflow.com/questions/2752725/finding-whether-a-point-lies-inside-a-rectangle-or-not
	 */
	static bool point_in_triangle(
			const int& x,
			const int& y,
			const int& ax,
			const int& ay,
			const int& bx,
			const int& by,
			const int& dx,
			const int& dy)
	{
		const int bax = bx - ax;
		const int bay = by - ay;
		const int dax = dx - ax;
		const int day = dy - ay;

		if (((x-ax)*bax + (y-ay)*bay) < 0) {
			return false;
		}
		else if (((x-bx)*bax + (y-by)*bay) > 0) {
			return false;
		}
		else if (((x-ax)*dax + (y-ay)*day) < 0) {
			return false;
		}
		else if (((x-dx)*dax + (y-dy)*day) > 0) {
			return false;
		}

		return true;
	}

};


#endif /* GPOS_H_ */
