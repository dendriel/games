package src 
{
	import flash.display.MovieClip;
	import flash.geom.Matrix;
	import flash.display.Sprite;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Calc 
	{
		// Define possibles collision orientation.
		static public const ORI_NONE:Number = 0;
		static public const ORI_N:Number = 1;
		static public const ORI_W:Number = 2;
		static public const ORI_S:Number = 3;
		static public const ORI_E:Number = 4;
		static public const ORI_NE:Number = 5;
		static public const ORI_NO:Number = 6;
		static public const ORI_SE:Number = 7;
		static public const ORI_SO:Number = 8;
		static public const ORI_C:Number = 9;
		
		/**
		 * @usage Create a random value between min and max.
		 * @param	min
		 * @param	max
		 * @return  (min >= value <= max)
		 */
		public static function randomRange(min:Number, max:Number) : Number
		{
			// Value will be something between 0 and max.
			var value:Number = Math.random() * max;
			// Value is already inside max limit. If value is less than min, return min.
			return (value >= min)? value : min;
		}
		
		//public function setRegistrationPoint(s:Sprite, regx:Number, regy:Number, showRegistration:Boolean )
		public static function setRegistrationPoint(s:Sprite, regx:Number, regy:Number) : void
		{
			//translate movieclip 
			s.transform.matrix = new Matrix(1, 0, 0, 1, -regx, -regy);
			//registration point.
			/*
			if (showRegistration)
			{
				var mark:Sprite = new Sprite();
				mark.graphics.lineStyle(1, 0x000000);
				mark.graphics.moveTo(-5, -5);
				mark.graphics.lineTo(5, 5);
				mark.graphics.moveTo(-5, 5);
				mark.graphics.lineTo(5, -5);
				s.parent.addChild(mark);
			}*/
		}
		
		/**
		 * @usage Check if two circles are in a collision.
		 * @param	p1x Circle 1 horizontal center position.
		 * @param	p1y Circle 1 vertical center position.
		 * @param	p1r Circle 1 radius.
		 * @param	p2x Circle 2 horizontal center position.
		 * @param	p2y Circle 2 vertical center position.
		 * @param	p2r Circle 2 radius.
		 * @return	true if the circles are colliding; false if not.
		 */
		public static function
		hitRadialCheck(p1x:Number, p1y:Number, p1r:Number, p2x:Number, p2y:Number, p2r:Number)
		: Boolean
		{
			var newX:Number = p1x - p2x;
			var newY:Number = p1y - p2y;
					 
			var distance:Number = Math.sqrt(newX * newX + newY * newY);
			
			return (distance < (p1r + p2r) );
		}
		
		/**
		 * @usage Transform a pixel coordinate into its corresponding tile coordinate. For example,
		 * a map sized 640x640 pixels, with tile size of 32x32, have 20 tiles rows and 20 columns.
		 * (20x20 tiles of 32x32 pixels each). The point of 630x630 is inside the tile in the
		 * position 19x19 (starting from 0 to 19 [20 tiles]).
		 * @param px	Horizontal position of the point.
		 * @param py	Vertical position of the point.
		 * @param tw	Tile width.
		 * @param th	Tile weigth.
		 * 
		 * @return The tile position (inside a Point object).
		 */
		public static function coorToTile(px:Number, py:Number, tw:Number, th:Number) : Point
		{
			var tile_h:int = px / tw;
			var tile_v:int = py / th;
			
			return ( new Point(tile_h, tile_v) );
		}
		
		/**
		 * @usage Center-align object 2 with object 1. Useful for menus.
		 *     x1     mid
		 *		+------+-----+
		 *		|    obj1    |
		 *		+------------+
		 *       x2    mid
		 * 		  +----+---+
		 * 		  |  obj2  |
		 *        +--------+
		 * 
		 * Equation:
		 * 
		 * middle_obj1 = x1 + (w1/2 + w1%2)
		 * x_obj2 = middle_obj1 - (w2/2 + w2%2)
		 * 
		 * 
		 * @param	obj1Px	Object 1 x.
		 * @param	obj1W	Object 1 width.
		 * @param	obj2W	Object 2 witdh.
		 * @return			The object 2 x to be center-aligned with object 1.
		 */
		public static function alignMiddle(obj1Px:Number, obj1W:Number, obj2W:Number) : Number
		{
			var refMiddle:Number = obj1Px + ( int(obj1W / 2) + (obj1W % 2) );
			return ( refMiddle - ( int(obj2W / 2) + (obj2W % 2) ) );
		}
		
		/**
		 * @usage Clip if greater than maximun.
		 * @param value	The value to clip.
		 * @param max	The limit to be tested.
		 * @return		If the value is greater than max, then max is returned. Or else,
		 * value is returned.
		 */ 
		public static function clipGT(value:Number, max:Number) : Number
		{
			return ((value > max)? max : value);
		}
		
		/**
		 * @usage Clip if less than minimum.
		 * @param value	The value to clip.
		 * @param min	The limit to be tested.
		 * @return		If the value is less than the min, then min is returned. Or else,
		 * value is returned.
		 */ 
		public static function clipLT(value:Number, min:Number) : Number
		{
			return ((value < min)? min : value);
		}
		
				
		
		/**
		 * @usage Checks if px and py are outside the given bounds. x,y = origin; w,h = size.
		 * @param px	x position of the point to check.
		 * @param py	y position of the point to check.
		 * @param ax	x position of the boundary.
		 * @param ay	y position of the boundary.
		 * @param aw	width of the boundary.
		 * @param ah	heigth of the boundary.
		 * @return		true if the point is outside the bounds; false otherwise.
		 * 
		 * For example (put values in x', y', w and h):
		 * 
		 * x axis
		 * ^
		 * |
		 * +---------------------> y axis
		 * |
		 * |		x',y'
		 * |		 +--------------+
		 * |		 |		  o	    |
		 * |		 |		px,py   |
		 * |		 |			    |
		 * |		 |			    |
		 * |		 +--------------+
		 * |				 (x'+w),(y'+ph)
		 */
		public static function checkOutsideBounds (px:Number, py:Number, ax:Number, ay:Number, aw:Number, ah:Number) : Boolean
		{
			/*
			 * px cant be less than x point.
			 * px cant be greater than or equal x2 point.
			 */
			if ( (px < ax) || (px >= (ax + aw) ) )
			{
				return true;
			}
			/*
			 * py cant be less than y point.
			 * py cant be greater than or equal y2 point.
			 */
			else if ( (py < ay) || (py >= (ay + ah) ) )
			{
				return true;
			}
			
			return false;
		}
		
		/**
		 * @usage Check if a point is inside the given "box". (the same as checkOutsideBounds, but inverse its return value).
		 * Check the function "checkOutsideBounds" for more information.
		 * @param px	x position of the point to check.
		 * @param py	y position of the point to check.
		 * @param ax	x position of the boundary.
		 * @param ay	y position of the boundary.
		 * @param aw	width of the boundary.
		 * @param ah	heigth of the boundary.
		 * @return		true if the point is inside the bounds; false otherwise.
		 */
		public static function checkInsideBounds (px:Number, py:Number, ax:Number, ay:Number, aw:Number, ah:Number) : Boolean
		{
			return !(checkOutsideBounds(px, py, ax, ay, aw, ah));
		}
    
		/**
		 * @usage  De	termines if the lines AB and CD intersect.
		 * Adapted from: http://ideone.com/PnPJgb
		 * another awesome reference: http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
		 * @param	Point A
		 * @param	Point B
		 * @param	Point C
		 * @param	Point D
		 * @return
		 */
		static function checkLinesIntersection(A:Point, B:Point, C:Point, D:Point) : Boolean
		{
			var CmP = new Point(C.x - A.x, C.y - A.y);
			var r   = new Point(B.x - A.x, B.y - A.y);
			var s   = new Point(D.x - C.x, D.y - C.y);

			var CmPxr = ( (CmP.x * r.y) - (CmP.y * r.x) );
			var CmPxs = ( (CmP.x * s.y) - (CmP.y * s.x) );
			var rxs   = ( (r.x * s.y) - (r.y * s.x) );

			if (CmPxr == 0)
			{
				// Lines are collinear, and so intersect if they have any overlap

				return ((C.x - A.x < 0) != (C.x - B.x < 0))
					|| ((C.y - A.y < 0) != (C.y - B.y < 0));
			}

			if (rxs == 0)
			{
				return false; // Lines are parallel.
			}

			var rxsr = 1 / rxs;
			var t = CmPxs * rxsr;
			var u = CmPxr * rxsr;

			return (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1);
		}
		
		/**
		 * @usage Check what face of a movieClip a line is in intersection.
		 * @param	Point A
		 * @param	Point B
		 * @param	MovieClip m
		 * @return A collision orientation (look for ORI_*).
		 */
		public static function checkLineIntersectOrientation(A:Point, B:Point, m:MovieClip) : Number
		{
			var mPointA = new Point(m.x, m.y);
			var mPointB = new Point(m.x + m.width, m.y);
			var mPointC = new Point(m.x, m.y + m.height);
			var mPointD = new Point(m.x + m.width, m.y + m.height);
			
			// Check Top.
			if (checkLinesIntersection(A, B, mPointA, mPointB))
			{
				return ORI_N;
			}
			
			// Check Right.
			if (checkLinesIntersection(A, B, mPointB, mPointD))
			{
				return ORI_W;
			}
			
			// Check bottom.
			if (checkLinesIntersection(A, B, mPointC, mPointD))
			{
				return ORI_S;
			}
			
			// Check left.
			if (checkLinesIntersection(A, B, mPointA, mPointC))
			{
				return ORI_E;
			}
			
			// No intersection.
			return ORI_NONE;
		}
		
		/**
		 * @usage Checks what is the position of the point in relation of a rectangle.
		 * 
		 * @param p The point to be checked.
		 * @param m The movie clip to be checked (its rectangle).
		 * 
		 * +--------------+---+----------------+
		 * |              |   |                |
		 * |      NO      | N |       NE       |
		 * |              |   |                |
		 * +--------------+---+----------------+
		 * |       O      | C |        E       |
		 * +--------------+---+----------------+
		 * |              |   |                |
		 * |      SO      | S |       SE       |
		 * |              |   |                |
		 * +--------------+---+----------------+
		 * 
		 * 
		 * 
		 *   +--------------+---+----------------+
		 *   |              |   |                |
		 *   |      NO      | N |       NE       |
		 *   |            Pa|   |Pb              |
		 *   +--------------+---+----------------+
		 *   |       O      | C |        E       |
		 *   +--------------+---+----------------+
		 *   |            Pc|   |Pd              |
		 *   |      SO      | S |       SE       |
		 *   |              |   |                |
		 *   +--------------+---+----------------+
		 *
		 * 
		 * @return The orientation value from point in relation to the movie clip. If the point is
		 * inside the movie clip, return ORI_C. Warning: if the point is inside of the border of a
		 * quadrant, it will be considered to be in that quadrant. The checking will be made in the
		 * order: N -> S -> E -> O; then, NO -> NE -> SE -> SO;
		 * If the point is not found anywere out of the rectangle, then the point is in the center
		 * and ORI_C is returned.
		 * 
		 */
		public static function pointOrientationRect(p:Point, m:MovieClip) : Number
		{
			var Pa = new Point(m.x, m.y);
			var Pb = new Point(m.x + m.width, m.y);
			var Pc = new Point(m.x, m.y + m.height);
			var Pd = new Point(m.x + m.width, m.y + m.height);
			
			// North or South.
			if ( (p.x >= Pa.x) && (p.x <= Pb.x) ) {
				// North.
				if (p.y <= Pa.y) {
					return ORI_N;
				}
				// South.
				else if (p.y >= Pc.y) {
					return ORI_S;
				}
			}
			// East and West.
			if ( (p.y >= Pb.y) && (p.y <= Pd.y) ) {
				// East.
				if (p.x >= Pb.x) {
					return ORI_E;
				}
				// West.
				else if (p.x <= Pc.x) {
					return ORI_W;
				}
			}
			
			// Northeast or Southeast.
			if (p.x >= Pb.x) {
				// Northeast.
				if (p.x <= Pb.y) {
					return ORI_NE;
				}
				// Southeast.
				else if (p.x >= Pd.y) {
					return ORI_SE;
				}
			}
			
			// Northwest or Southwest.
			if (p.x <= Pa.x) {
				// Northwest.
				if (p.x <= Pa.y) {
					return ORI_NO;
				}
				// Southwest.
				else if (p.x >= Pc.y) {
					return ORI_SO;
				}
			}
			
			return ORI_C;
		}
	}

}