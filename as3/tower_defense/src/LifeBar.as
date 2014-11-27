package src
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * I made a code 'hack' to very low total life values be doubled so the life bar looks bigger.
	 * 
	 */
	public class LifeBar extends MovieClip 
	{
		private const lifeColor:Number = 0x32CD32; // LimeGreen.
		private const noLifeColor:Number = 0xFF0000; // Red.
		private const barHeight:Number = 5;
		private var totalLife:Number;
		private var _life:Number;
		private var greenLife:Shape;
		
		public function LifeBar(life:Number, px:Number, py:Number)
		{
			totalLife = life;
			_life = (totalLife >= 40 ? life : life*2); // double the life so the bar will be larger.
			
			this.x = px;
			this.y = py;
			
			drawSelf();
		}
		
		
		
		private function drawSelf() : void
		{
			// Create red life (no life).
			var rect:Shape = new Shape;
			rect.graphics.beginFill(noLifeColor);
			rect.graphics.drawRect(0, 0, _life, barHeight);
			rect.graphics.endFill();
			this.addChild(rect);
			
			greenLife = new Shape;
			greenLife.graphics.beginFill(lifeColor);
			greenLife.graphics.drawRect(0, 0, _life, barHeight);
			greenLife.graphics.endFill();
			this.addChild(greenLife);
		}
		
		private function updateSelf() : void
		{
			greenLife.graphics.clear();
			greenLife.graphics.beginFill(lifeColor);
			greenLife.graphics.drawRect(0, 0, _life, barHeight);
			greenLife.graphics.endFill();
		}
		
		public function decreaseLife(value:Number):void 
		{
			_life -= (totalLife >= 40 ? value : value * 2);
			updateSelf();
		}
		
	}
	
}