package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.text.TextField;
	import flash.text.TextFormat;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ScoreHud extends MovieClip
	{
		private var stageRef:Stage;
		private var scoreDisplayText:TextField;
		private var scoreValueText:TextField;
		private var scoreValue:Number;
		
		public function ScoreHud(stageRef:Stage) 
		{
			this.stageRef = stageRef;
			
			var format:TextFormat = new TextFormat;
			format.size = 24;
			
			scoreValue = 0;
			
			scoreDisplayText = new TextField();
			scoreDisplayText.defaultTextFormat = format;
			scoreDisplayText.text =  "Score: ";
			scoreDisplayText.textColor = 0xffffff;
			scoreDisplayText.selectable = false;
			scoreDisplayText.mouseEnabled = false;
			
			scoreValueText = new TextField();
			scoreValueText.defaultTextFormat = format;
			scoreValueText.text =  String(scoreValue);
			scoreValueText.textColor = 0xffffff;
			scoreDisplayText.selectable = false;
			scoreDisplayText.mouseEnabled = false;
			
			scoreValueText.x = scoreDisplayText.textWidth;
			
			show();
		}
		
		public function update(value:Number) : void
		{
			scoreValue += value;
			scoreValueText.text = String(scoreValue);
		}
		
		public function show() : void
		{
			this.addChild(scoreDisplayText);
			this.addChild(scoreValueText);
		}
		
		public function hide() : void
		{
			if (this.contains(scoreDisplayText))
			{
				this.removeChild(scoreDisplayText);
			}
			
			if (this.contains(scoreValueText))
			{
				this.removeChild(scoreValueText);
			}
		}
		
		public function getScore() : Number
		{
			return scoreValue;
		}
	}

}