package src.ui
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import src.ui.GameTextFormat;
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameTileDisplay extends MovieClip
	{
		// Constants.
		private const nameTxtOffsetY:int = 4;
		private const firstColumnIconsX:int = 8;
		private const firstColumnIconsY:int = 30;
		private const iconsOffset:int = 16;
		
		// Text.
		private var nameTxt:TextField;
		private var fortifyText:TextField;
		private var moveBonusText:TextField;
		private var moveText:TextField;
		
		// Dynamic icons.
		private var moveOk:MoveIcon;
		private var moveBlocked:MoveBlockIcon;
		
		public function GameTileDisplay(px:int = 0, py:int = 0)
		{
			x = px;
			y = py;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			// Text.
			nameTxt = GameTextFormat.newDisplayTextTitle(firstColumnIconsX, nameTxtOffsetY);
			addChild(nameTxt);
			
			var fortify = new FortifyIcon();
			fortify.x = firstColumnIconsX;
			fortify.y = firstColumnIconsY;
			fortifyText = GameTextFormat.newDisplayTextField( (fortify.x + iconsOffset), fortify.y);
			
			var moveBonus = new PathArrowIcon();
			moveBonus.x = firstColumnIconsX;
			moveBonus.y = fortify.y + iconsOffset;
			moveBonusText = GameTextFormat.newDisplayTextField( (moveBonus.x + iconsOffset), moveBonus.y);
			
			moveOk = new MoveIcon();
			moveOk.x = firstColumnIconsX;
			moveOk.y = moveBonus.y + iconsOffset;
			moveBlocked = new MoveBlockIcon();
			moveBlocked.x = moveOk.x;
			moveBlocked.y = moveOk.y;
			// moveOk and moveBlocked are added dinamically.
			moveText = GameTextFormat.newDisplayTextField( (moveOk.x + iconsOffset), moveOk.y);
			
			addChild(fortify);
			addChild(fortifyText);
			addChild(moveBonus);
			addChild(moveBonusText);
		}
		
		public function set elemName(value:String) : void
		{
			nameTxt.text = value;
			nameTxt.width = nameTxt.textWidth + 4;
			nameTxt.height = nameTxt.textHeight + 2;
		}
		
		public function set fortifyBonus(value:int) : void { fortifyText.text = String(value); }
		public function set moveBonus(value:int) : void { moveBonusText.text = String(value); }
		
		public function set moveable(value:Boolean) : void
		{
			// Clearing.
			if ( contains(moveOk) )
			{
				removeChild(moveOk);
			}
			if ( contains(moveBlocked) )
			{
				removeChild(moveBlocked);
			}
			if ( contains(moveText) )
			{
				removeChild(moveText);
			}
			
			if (value == true)
			{
				addChild(moveOk);
				moveText.text = GameLanguage.lang.moveable_str;
			}
			else
			{
				addChild(moveBlocked);
				moveText.text = GameLanguage.lang.blocked_str;
			}
			
			addChild(moveText);
		}
	}
	
}