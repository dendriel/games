package  
{
	import flash.geom.Matrix;
	import flash.display.Sprite;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Calculation 
	{
		
		public static function randomRange(min:Number, max:Number) : Number
		{
			// Value will be something between 0 and max.
			var value:Number = Math.random() * max;
			// Value is already inside max limit. If value is less than min, return min.
			return (value >= min)? value : min;
		}
		
		//public function setRegistrationPoint(s:Sprite, regx:Number, regy:Number, showRegistration:Boolean )
		public static function setRegistrationPoint(s:Sprite, regx:Number, regy:Number)
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
		
		public static function hitRadialCheck(p1x:Number, p1y:Number, p1r:Number, p2x:Number, p2y:Number, p2r:Number) : Boolean
		{
			var newX:Number = p1x - p2x;
			var newY:Number = p1y - p2y;
					 
			var distance:Number = Math.sqrt(newX * newX + newY * newY);
			
			return (distance < p1r + p2r);
		}
		
		public static function randomChance(chance:Number, frameRate:Number) : Boolean
		{
			var chanceDec:Number = chance / 100;
			//trace("chanceDec: " + chanceDec);
			var test:Number = Math.pow(chanceDec, frameRate-1);
			//trace ("test: " + test);
			return (Math.random() < Math.pow(chanceDec, (frameRate-1)));
		}
	}

}