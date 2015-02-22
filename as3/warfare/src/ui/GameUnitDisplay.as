package src.ui
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnitDisplay extends MovieClip 
	{
		// Constants.
		private const nameTxtOffsetX:int = 8;
		private const nameTxtOffsetY:int = 4;
		
		private const firstColumnIconsX:int = 8;
		private const firstColumnIconsY:int = 30;
		private const secondColumnIconsX:int = 64;
		private const secondColumnIconsY:int = 30;
		private const iconsOffset:int = 16;
		
		// Text.
		private var nameFormat:TextFormat;
		private var nameTxt:TextField;
		
		private var fieldsFormat:TextFormat;
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
			nameFormat = new TextFormat;
			nameFormat.size = 14;
			nameFormat.bold = true;
			
			fieldsFormat = new TextFormat;
			fieldsFormat.size = 12;
			
			nameTxt = new TextField();
			nameTxt.defaultTextFormat = nameFormat;
			nameTxt.textColor = 0xffffff;
			nameTxt.selectable = false;
			nameTxt.mouseEnabled = false;
			nameTxt.x = nameTxtOffsetX;
			nameTxt.y = nameTxtOffsetY;
			
			soldiersAmountTxt = new TextField();
			soldiersAmountTxt.defaultTextFormat = fieldsFormat;
			soldiersAmountTxt.textColor = 0xffffff;
			soldiersAmountTxt.selectable = false;
			soldiersAmountTxt.mouseEnabled = false;
			attackValueTxt = new TextField();
			attackValueTxt.defaultTextFormat = fieldsFormat;
			attackValueTxt.textColor = 0xffffff;
			attackValueTxt.selectable = false;
			attackValueTxt.mouseEnabled = false;
			defenseValueTxt = new TextField();
			defenseValueTxt.defaultTextFormat = fieldsFormat;
			defenseValueTxt.textColor = 0xffffff;
			defenseValueTxt.selectable = false;
			defenseValueTxt.mouseEnabled = false;
			distanceValueTxt = new TextField();
			distanceValueTxt.defaultTextFormat = fieldsFormat;
			distanceValueTxt.textColor = 0xffffff;
			distanceValueTxt.selectable = false;
			distanceValueTxt.mouseEnabled = false;
			moveValueTxt = new TextField();
			moveValueTxt.defaultTextFormat = fieldsFormat;
			moveValueTxt.textColor = 0xffffff;
			moveValueTxt.selectable = false;
			moveValueTxt.mouseEnabled = false;
			costValueTxt = new TextField();
			costValueTxt.defaultTextFormat = fieldsFormat;
			costValueTxt.textColor = 0xffffff;
			costValueTxt.selectable = false;
			costValueTxt.mouseEnabled = false;
			
			addChild(nameTxt);
			
			var soldiers = new SoldiersIcon();
			soldiers.x = firstColumnIconsX;
			soldiers.y = firstColumnIconsY;
			soldiersAmountTxt.x = soldiers.x + iconsOffset;
			soldiersAmountTxt.y = soldiers.y;
			
			var attack = new AttackIcon();
			attack.x = firstColumnIconsX;
			attack.y = soldiers.y + iconsOffset;
			attackValueTxt.x = attack.x + iconsOffset;
			attackValueTxt.y = attack.y;
			
			var defense = new DefenseIcon();
			defense.x = firstColumnIconsX;
			defense.y = attack.y + iconsOffset;
			defenseValueTxt.x = defense.x + iconsOffset;
			defenseValueTxt.y = defense.y;
			
			var distance = new DistanceIcon();
			distance.x = secondColumnIconsX;
			distance.y = secondColumnIconsY;
			distanceValueTxt.x = distance.x + iconsOffset;
			distanceValueTxt.y = distance.y;
			
			var move = new MoveIcon();
			move.x = secondColumnIconsX;
			move.y = distance.y + iconsOffset;
			moveValueTxt.x = move.x + iconsOffset;
			moveValueTxt.y = move.y;
			
			var cost = new CostIcon();
			cost.x = secondColumnIconsX;
			cost.y = move.y + iconsOffset;
			costValueTxt.x = cost.x + iconsOffset;
			costValueTxt.y = cost.y;
			
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
			nameTxt.width = nameTxt.textWidth + 2;
			nameTxt.height = nameTxt.textHeight + 2;
		}
		
		public function set_soldiers(soldiers:int, injuried:int) : void
		{
			soldiersAmountTxt.text = ( String(soldiers - injuried) + "/" + String(soldiers) );
		}
		
		public function set attack(value:int) : void { attackValueTxt.text = String(value); }
		public function set defense(value:int) : void { defenseValueTxt.text = String(value); }
		public function set distance(value:int) : void { distanceValueTxt.text = String(value); }
		public function set move(value:int) : void { moveValueTxt.text = String(value); }
		public function set cost(value:int) : void { costValueTxt.text = String(value); }
		
	}
}