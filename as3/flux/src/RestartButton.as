package  
{
	import flash.display.MovieClip;
	import flash.display.SimpleButton;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;

	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class RestartButton extends MovieClip
	{
		private const buttonTextDefault:String = "Restart Game";
		private var button:SimpleButton;
		private var buttonText:TextField;
		
		public function RestartButton(px:Number, py:Number) 
		{
			button = new SimpleButton;
			buttonText = new TextField;
			drawSelf();
			
			x = px;
			y = py;
			
		}
		
		private function drawSelf() : void
		{
			var format:TextFormat = new TextFormat;
			var buttonSprite:Sprite;
			
			buttonSprite = new Sprite();
			buttonSprite.graphics.lineStyle(1, 0x555555);
			buttonSprite.graphics.beginFill(0xffffff, 0.1);
			buttonSprite.graphics.drawRect(0,0,120,30);
			buttonSprite.graphics.endFill();
			
			format.size = 18;
			
			buttonText.defaultTextFormat = format;
			buttonText.textColor = 0xffffff;
			buttonText.width = 120;
			buttonText.x = 8;
			buttonText.y = 3;
			buttonText.text = buttonTextDefault;
			buttonText.selectable = false;
			buttonText.mouseEnabled = false;
			//buttonText.
			
			button.overState = button.downState = button.upState = button.hitTestState = buttonSprite;
			
			button.addEventListener(MouseEvent.CLICK, dispatchClicked, false, 0, true);
			
			this.addChild(button);
			this.addChild(buttonText);
		}
		
		private function dispatchClicked(e:MouseEvent) : void
		{
			dispatchEvent(new Event("clicked"));
		}
	}

}