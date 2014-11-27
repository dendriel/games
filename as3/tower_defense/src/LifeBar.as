package src
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LifeBar extends MovieClip 
	{
		private const lifeColor:Number = 0x32CD32; // LimeGreen.
		private const barHeight:Number = 5;
		private var totalLife:Number;
		private var _life:Number;
		
		public function LifeBar(life:Number, px:Number, py:Number)
		{
			totalLife = life;
			_life = (life >= 40 ? life : life*2); // double the life so the bar will be larger.
			
			this.x = px;
			this.y = py;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			var rect:Shape = new Shape;
			rect.graphics.beginFill(lifeColor);
			rect.graphics.drawRect(0, 0, _life, barHeight); // (x spacing, y spacing, width, height)
			rect.graphics.endFill();
			this.addChild(rect); // adds the rectangle to the stage
		}
		
	}
	
}