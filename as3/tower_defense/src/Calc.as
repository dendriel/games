package src 
{
	import flash.geom.Matrix;
	import flash.display.Sprite;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Calc 
	{
		
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
		
		public static function
		hitRadialCheck(p1x:Number, p1y:Number, p1r:Number, p2x:Number, p2y:Number, p2r:Number)
		: Boolean
		{
			var newX:Number = p1x - p2x;
			var newY:Number = p1y - p2y;
					 
			var distance:Number = Math.sqrt(newX * newX + newY * newY);
			
			return (distance < (p1r + p2r) );
		}
		
		// Distributed chance. Doesn't work!!
		public static function randomChance(chance:Number, frameRate:Number) : Boolean
		{
			var chanceDec:Number = chance / 100;
			//trace("chanceDec: " + chanceDec);
			var test:Number = Math.pow(chanceDec, frameRate-1);
			//trace ("test: " + test);
			return (Math.random() < Math.pow(chanceDec, (frameRate-1)));
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
	}

}