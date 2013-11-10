/*
 * Gpos.h
 *
 *  Created on: 09/11/2013
 *      Author: vitor
 */

#ifndef GPOS_H_
#define GPOS_H_

#include "util.h"

// TODO: this could be a class.
typedef struct point {
	float x, y;
	point(float x, float y):
		x(x),
		y(y) {}
} point;

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
	 * \return 0 = first area; 1 = second area; 2 = third area; 3 = fourth area; -1 if the point
	 * is inside of any area.
	 *
	 * \note *There is no need to be an equilateral rectangle.
	 *
	 * Example:
	 *
	 *     px1          px2          px3
	 * 	py1	+-------------------------+
	 * 		| .       area #0       . |
	 * 		|    .               .    |
	 * 		|       .         .       |
	 *		|          .   .          |
	 *	py2	+  area #3   +   area #1  +
	 *		|          .   .          |
	 *		|       .         .       |
	 *		|    .               .    |
	 *		| .       area #2       . |
	 *	py3	+-------------------------+
	 *
	 */
	static unsigned short point_area_in_rect(
			const int x,
			const int y,
			const int rect_size_w,
			const int rect_size_h,
			const int rect_origin_x = 0,
			const int rect_origin_y = 0)
	{
		int px1, px2, px3;
		int py1, py2, py3;

		px1 = rect_origin_x;
		px2 = rect_origin_x + (rect_size_w/2);
		px3 = rect_origin_x + (rect_size_w - 1);

		py1 = rect_origin_y;
		py2 = rect_origin_y + (rect_size_h/2);
		py3 = rect_origin_y + (rect_size_h - 1);

		debug("%d %d %d; %d %d %d", px1, px2, px3, py1, py2, py3);

		// Area 0
		if (point_in_triangle(x,y, px1,py1, px2,py2, px3,py1)) {
			return 0;
		}
		// Area 1
		else if (point_in_triangle(x,y, px3,py1, px2,py2, px3,py3)) {
			return 1;
		}
		// Area 2
		else if (point_in_triangle(x,y, px1,py3, px2,py2, px3,py3)) {
			return 2;
		}
		// Area 3
		else if (point_in_triangle(x,y, px1,py1, px2,py2, px1,py3)) {
			return 3;
		}

		return -1;
	}

private:
	/**
	 * \note Find out if a point is inside a rectangle.
	 * Retrieved from:
	 *  http://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
	 */
	static bool point_in_triangle(
			const int& x,
			const int& y,
			const int& x1,
			const int& y1,
			const int& x2,
			const int& y2,
			const int& x3,
			const int& y3)
	{
		point p(x, y);
		point p1(x1, y1);
		point p2(x2, y2);
		point p3(x3, y3);

		float alpha = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y)) /
						((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
		float beta = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y)) /
						((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
		float gamma = 1.0f - alpha - beta;

		return ((alpha > 0) && (beta >0) && (gamma > 0));
	}

};


#endif /* GPOS_H_ */
