package 
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.ui.Keyboard;
	import senocular.utils.KeyObject;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Ship extends MovieClip 
	{
		public const drawRadius:Number = 35;
		private const drawInnerRadius:Number = 25;
		private const moveSpeed:Number = 6;
		private const initialPower:Number = 100;
		private var currPower:Number;
		private var stageRef:Stage;
		private var key:KeyObject;
		private var powerText:TextField;
		
		public function Ship(stageRef:Stage)
		{
			this.stageRef = stageRef;
			key = new KeyObject(stageRef);
			powerText = new TextField;
			currPower = initialPower;
			drawSelf();
			
			x = stageRef.stageWidth / 2;
			y = stageRef.stageHeight - 100;
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
		}
		
		private function drawSelf() : void
		{
			graphics.beginFill(0x7ebff1);
            graphics.drawCircle(0, 0, drawInnerRadius);
            graphics.drawCircle(0, 0, drawRadius);
			graphics.endFill();
			
			var format:TextFormat = new TextFormat;
			format.size = 18;
			
			powerText.defaultTextFormat = format;
			powerText.x = -16;
			powerText.y = -13;
			powerText.textColor = 0xffffff;
			updatePower();
			this.addChild(powerText);
		}
		
		public function addEnergy(value:Number) : void
		{
			currPower += value;
			updatePower();
		}
		
		private function updatePower() : void
		{
			powerText.text = String(currPower);
		}
		
		private function loop(e:Event) : void
		{
			if (key.isDown(Keyboard.LEFT))
			{
				x -= moveSpeed;
				if (x < drawRadius) {
					x = drawRadius;
				}
				
			}
			else if (key.isDown(Keyboard.RIGHT))
			{
				x += moveSpeed;
				if (x > stageRef.stageWidth - drawRadius)
				{
					x = stageRef.stageWidth-drawRadius;
				}
			}
			
			// action key.
			if (key.isDown(Keyboard.SPACE))
			{
				dispatchEvent(new Event("action"));
			}
		}
	}
	
}