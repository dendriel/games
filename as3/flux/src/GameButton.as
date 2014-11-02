package  
{
	import flash.display.MovieClip;
	import flash.display.SimpleButton;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameButton extends MovieClip
	{
		private var textValue:String;
		private var button:SimpleButton;
		private var textField:TextField;
		
		public function GameButton(textValue:String, px:Number = 0, py:Number = 0)
		{
			this.textValue = textValue;
			x = px;
			y = py;
			
			button = new SimpleButton;
			textField = new TextField;
			
			drawSelf();
		}
		
		public function setPos(px:Number, py:Number) : void
		{
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
			format.align = TextFormatAlign.CENTER;
			
			textField.defaultTextFormat = format;
			textField.textColor = 0xffffff;
			textField.y = 3;
			textField.text = textValue;
			textField.width = buttonSprite.width;
			textField.selectable = false;
			textField.mouseEnabled = false;
			
			button.overState = button.downState = button.upState = button.hitTestState = buttonSprite;
			
			this.addChild(button);
			this.addChild(textField);
		}		
	}

}