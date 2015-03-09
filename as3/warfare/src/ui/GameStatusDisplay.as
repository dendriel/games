package src.ui
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	/**
	 * Dynamic status menu. Maximum number of entries is 9.
	 * 
	 * Example:
		 * var display:GameStatusDisplay = new GameStatusDisplay(pos_x, pos_y,
		 * 										[["entry01", new MyEntryIconBitmapData],
		 *  										["entry02", new MyEntryIconBitmapData],
		 *  										["entry03", new MyEntryIconBitmapData],
		 *  										["entry04", new MyEntryIconBitmapData],
		 *  										["entry05", new MyEntryIconBitmapData],
		 *  										["entry06", new MyEntryIconBitmapData],
		 *  										["entry07", new MyEntryIconBitmapData],
		 *  										["entry08", new MyEntryIconBitmapData],
		 *  										["entry09", new MyEntryIconBitmapData]
		 * 										]);
		 * 
		 * display.setName("Small City");
		 * display.setField("entry05", "Field value to be displayed");
		 * addChield(display);
	 * 
	 * 
	 * @author Vitor Rozsa
	 */
	public class GameStatusDisplay extends MovieClip 
	{
		// Constants.
		private const nameTxtOffsetY:int = 4;
		
		private const firstColumnIconsX:int = 8;
		private const secondColumnIconsX:int = 64;
		private const thirdColumnIconsX:int = 120;
		private const columnIconsY:int = 30;
		private const iconsOffset:int = 16;
		
		// Variables.
		// An iten in the menu is composed by a [label, icon].
		private var elements_list:Vector.<Array>;
		
		// Element name.
		private var nameTxt:TextField;
		
		public function GameStatusDisplay(px:int, py:int, elements:Array)
		{
			x = px;
			y = py;
			
			elements_list = new Vector.<Array>;
			
			drawSelf(elements);
		}
		
		private function drawSelf(elements:Array) : void
		{
			// Element name is a 'static' item.
			nameTxt = GameTextFormat.newDisplayTextTitle(firstColumnIconsX, nameTxtOffsetY);
			
			addChild(nameTxt);
			
			for (var i in elements)
			{
				var label:String = elements[i][0];
				var icon:Bitmap = new Bitmap(elements[i][1]);
				var text:TextField;
				
				//icon.x = ( (i < 3)? firstColumnIconsX :	( (i > 2 && i < 6)? secondColumnIconsX : thirdColumnIconsX ) );
				
				if (i < 3)
				{
					icon.x = firstColumnIconsX;
					icon.y = columnIconsY + iconsOffset * i;
				}
				else if (i > 2 && i < 6)
				{
					icon.x = secondColumnIconsX;
					icon.y = columnIconsY + iconsOffset * (i - 3);
				}
				else
				{
					icon.x = thirdColumnIconsX;
					icon.y = columnIconsY + iconsOffset * (i - 6);
				}
				
				text = GameTextFormat.newDisplayTextField( (icon.x + iconsOffset), icon.y);
				
				addChild(icon);
				addChild(text);
				elements_list.push([label, text, icon]);
				
				// Limited in nine entries.
				if (i == 9)
				{
					break;
				}
			}
		}
		
		/**
		 * Update status field.
		 * @param	label Reference to the field.
		 * @param	value Text to be set.
		 * @param	color Add color depending if the number are positive or negative.
		 * @param	sign Add positive or negative sign depending if the number are positive or negative.
		 * @param	percent Add percentage signal at the end of the string value.
		 */
		public function setField(label:String, value:String, sign:Boolean=false, percent:Boolean=false, color:Boolean=false) : void
		{
			var colorValue:uint;
			var text:String = "";
			var num:Number;
			
			for each (var element in elements_list)
			{
				var elem_label:String = element[0];
				var elem_txt:TextField = element[1];
				
				if (elem_label != label)
				{
					continue;
				}
				
				if (color)
				{
					num = Number(value);
					colorValue = ( (num == 0)? GameTextFormat.displayFieldsColor :
									( (num > 0)? GameTextFormat.positiveColor : GameTextFormat.negativeColor ) );
					elem_txt.textColor = colorValue;
				}
				
				if (sign)
				{
					num = Number(value);
					text += (num > 0)? "+" : "";
				}
				
				text += value;
				
				if (percent)
				{
					text += "%";
				}
				
				elem_txt.text = text;
			}
		}
		
		/**
		 * Update the icon of a field.
		 * @param	label Field reference.
		 * @param	icon The new icon.
		 */
		public function changeIcon(label:String, icon_data:BitmapData) : void
		{
			var new_icon:Bitmap = new Bitmap(icon_data);
			for each (var element in elements_list)
			{
				var elem_label:String = element[0];
				var elem_txt:TextField = element[1];
				var elem_icon:Bitmap = element[2];
				
				if (elem_label != label)
				{
					continue;
				}
				
				if (contains(elem_icon))
				{
					removeChild(elem_icon);
				}
				
				new_icon.x = elem_icon.x;
				new_icon.y = elem_icon.y;
				
				addChild(new_icon);
				element[2] = new_icon;
			}
		}
		
		public function setName(value:String) : void
		{
			nameTxt.text = value;
			nameTxt.width = nameTxt.textWidth + 4;
			nameTxt.height = nameTxt.textHeight + 2;
		}
	}
	
}