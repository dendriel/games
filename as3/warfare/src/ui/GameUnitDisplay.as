package src.ui
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import src.ui.GameTextFormat;
	
	/**
	 * ...TODO:
		 * 
		 * - Display help information when passing mouse over icons or name (show desc for this).
		 * 
		 * 
	 * @author Vitor Rozsa
	 */
	public class GameUnitDisplay extends MovieClip 
	{
		// Constants.
		private const nameTxtOffsetY:int = 4;
		
		private const firstColumnIconsX:int = 8;
		private const firstColumnIconsY:int = 30;
		private const secondColumnIconsX:int = 64;
		private const secondColumnIconsY:int = 30;
		private const iconsOffset:int = 16;
		
		// Text.
		private var nameTxt:TextField;
		private var soldiersAmountTxt:TextField;
		private var attackValueTxt:TextField;
		private var defenseValueTxt:TextField;
		private var distanceValueTxt:TextField;
		private var moveValueTxt:TextField;
		private var costValueTxt:TextField;
		
		public function GameUnitDisplay(px:int = 0, py:int = 0)
		{
			x = px;
			y = py;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			// Text.
			nameTxt = GameTextFormat.newDisplayTextTitle(firstColumnIconsX, nameTxtOffsetY);
			
			var soldiers = new SoldiersIcon();
			soldiers.x = firstColumnIconsX;
			soldiers.y = firstColumnIconsY;
			soldiersAmountTxt = GameTextFormat.newDisplayTextField( (soldiers.x + iconsOffset), soldiers.y);
			
			var attack = new AttackIcon();
			attack.x = firstColumnIconsX;
			attack.y = soldiers.y + iconsOffset;
			attackValueTxt = GameTextFormat.newDisplayTextField( (attack.x + iconsOffset), attack.y);
			
			var defense = new DefenseIcon();
			defense.x = firstColumnIconsX;
			defense.y = attack.y + iconsOffset;
			defenseValueTxt = GameTextFormat.newDisplayTextField( (defense.x + iconsOffset), defense.y);
			
			var distance = new DistanceIcon();
			distance.x = secondColumnIconsX;
			distance.y = secondColumnIconsY;
			distanceValueTxt = GameTextFormat.newDisplayTextField( (distance.x + iconsOffset), distance.y);
			
			var move = new MoveIcon();
			move.x = secondColumnIconsX;
			move.y = distance.y + iconsOffset;
			moveValueTxt = GameTextFormat.newDisplayTextField( (move.x + iconsOffset), move.y);
			
			var cost = new CostIcon();
			cost.x = secondColumnIconsX;
			cost.y = move.y + iconsOffset;
			costValueTxt = GameTextFormat.newDisplayTextField( (cost.x + iconsOffset), cost.y);
			
			addChild(nameTxt);
			addChild(soldiers);
			addChild(soldiersAmountTxt);
			addChild(attack);
			addChild(attackValueTxt);
			addChild(defense);
			addChild(defenseValueTxt);
			addChild(distance);
			addChild(distanceValueTxt);
			addChild(move)
			addChild(moveValueTxt);
			addChild(cost);
			addChild(costValueTxt);
		}
		
		public function set elemName(value:String) : void
		{
			nameTxt.text = value;
			nameTxt.width = nameTxt.textWidth + 4;
			nameTxt.height = nameTxt.textHeight + 2;
		}
		
		public function set_soldiers(soldiers:int, injuried:int) : void
		{
			soldiersAmountTxt.text = ( String(soldiers - injuried) + "/" + String(soldiers) );
		}
		
		public function set attack(value:int) : void { attackValueTxt.text = String(value); }
		public function set defense(value:int) : void { defenseValueTxt.text = String(value); }
		public function set distance(value:int) : void { distanceValueTxt.text = String(value); }
		public function set move(value:Number) : void { moveValueTxt.text = String(value); }
		public function set cost(value:int) : void { costValueTxt.text = String(value); }
		
	}
}