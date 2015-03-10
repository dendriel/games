package src.ui
{
	import flash.display.Bitmap;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import src.as3.math.Calc;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameActionsDisplay extends MovieClip 
	{
		// Constants.
		private const max_windows = 3;
		private const iconsHorizontalOffset = 10;
		private const iconsVerticalOffset = 8;
		private const iconsWidth = 32;
		private const iconsHeight = 32;
		private const iconsPerRow = 9
		
		
		// Variables
		// each member: [title, elements_list]
		private var windows_list:Array;
		
		public function GameActionsDisplay(px:int, py:int)
		{
			x = px;
			y = py;
			
			windows_list = new Array(max_windows);
		}
		
		public function addWindow(title:String, itens:Array) : void
		{
			var window:MovieClip = new MovieClip();
			
			// Remove window data if already added.
			for each (var window_data:Array in windows_list)
			{
				var window_title:String = window_data[0];
				var window_view:MovieClip = window_data[1];
				
				if (window_title == title)
				{
					if (contains(window_view))
					{
						removeChild(window_view);
					}
					windows_list.splice(windows_list.indexOf(window_data), 1);
				}
			}
			
			for (var i in itens)
			{
				var element:Array = itens[i];
				var icon:Sprite = new Sprite();
				icon.addChild(element[2]);
				var clickHandler:Function = element[3];
				
				var verticalOffset = int(i / iconsPerRow) * iconsVerticalOffset + int(i / iconsPerRow) * iconsHeight;
				var horizontalOffset = (i - int(i / iconsPerRow) * iconsPerRow) * (iconsWidth + iconsHorizontalOffset);
				
				icon.x = iconsHorizontalOffset + horizontalOffset;
				icon.y = iconsVerticalOffset + verticalOffset;
				
				icon.addEventListener(MouseEvent.CLICK, clickHandler, false, 0, true);
				
				//var nameTxt:TextField = GameTextFormat.newDisplayTextField();
				//nameTxt.text = element[0];
				//nameTxt.x = Calc.alignMiddle(icon.x, iconsWidth, nameTxt.textWidth);
				//nameTxt.y = icon.y + iconsHeight;
				//var desc:String = element[1];
				
				window.addChild(icon);
			}
			addChild(window);
			windows_list.push([title, window]);
		}
	}
	
}