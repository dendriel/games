package  
{
	import flash.display.MovieClip;
	import flash.display.Shader;
	import flash.display.Shape;
	import flash.display.Stage;
	import flash.geom.Matrix;
	import flash.geom.Rectangle;
	import flash.display.GradientType;
	import flash.display.InterpolationMethod;
	import flash.display.SpreadMethod;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Background extends MovieClip
	{
		private const starsAmount:Number = 80;
		private var stageRef:Stage;
		public var rect:Shape;
		
		public function Background(stageRef:Stage) 
		{
			this.stageRef = stageRef;
			x = 0;
			y = 0;
			
			drawSelf();
			setupStars();
		}
		
		private function drawSelf() : void
		{
			//graphics.
			//createGradientBox(width:Number, height:Number, rotation:Number, translx:Number, transly:Number);
			/*
			rect = new Shape();
			rect.graphics.beginFill(0xFF0000); // choosing the colour for the fill, here it is red
			rect.graphics.drawRect(0, 0, 100,100); // (x spacing, y spacing, width, height)
			rect.graphics.endFill(); // not always needed but I like to put it in to end the fill
			this.addChild(rect); // adds the rectangle to the stage
			*/
			
			rect = new Shape();
			
			var type:String = GradientType.RADIAL; 
			//var colors:Array = [0x00FF00, 0x000088];
			var colors:Array = [0x191970, 0x191990];
			var alphas:Array = [0.6, 1]; 
			// Pretty blue sky.
			//var colors:Array = [0xB0C4FE, 0xB0C4DE];
			//var alphas:Array = [0.5, 0.7]; 
			var ratios:Array = [0, 255]; 
			var spreadMethod:String = SpreadMethod.PAD; 
			var interp:String = InterpolationMethod.LINEAR_RGB; 
			var focalPtRatio:Number = 0; 
			 
			var matrix:Matrix = new Matrix(); 
			var boxWidth:Number = stageRef.stageWidth; 
			var boxHeight:Number = stageRef.stageHeight; 
			var boxRotation:Number = 0;//Math.PI/2; // 90° 
			var tx:Number = 0; 
			var ty:Number = stageRef.stageHeight/2; 
			matrix.createGradientBox(boxWidth, boxHeight, boxRotation, tx, ty); 
			 
			var square:Shape = new Shape; 
			rect.graphics.beginGradientFill(type,  
										colors, 
										alphas, 
										ratios,  
										matrix,  
										spreadMethod,  
										interp,  
										focalPtRatio);
			rect.graphics.drawRect(0, 0, stageRef.stageWidth, stageRef.stageHeight); 
			
			this.addChild(rect);
		}
		
		/*
		 * Create the scenario stars. 
		 */
		private function setupStars() : void
		{
			for (var i:Number = 0; i < starsAmount; i++)
			{
				var star:Star = new Star(this);
			}
			
		}
	}

}