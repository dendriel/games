package src
{
	import src.as3.math.Calc;
	import src.units.GameUnit;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameBattleProcessor 
	{
		public static function processBattle(attacker:GameUnit, defender:GameUnit) : void
		{
			var defender_soldiers:int = defender.soldiers;
			var attacker_soldiers:int = attacker.soldiers;
			
			trace("Processing battle. " + defender_soldiers + " vs " + attacker_soldiers);
			
			SoundLoader.playSwordHit01();
			for (var i:int = 0; (i < attacker_soldiers) && (defender_soldiers > 0); i++)
			{				
				var attacker_power = attacker.attack + Calc.roll_d6();
				var defender_power = defender.attack + Calc.roll_d6();
				var attacker_defense = attacker.defense + Calc.roll_d6();
				var defender_defense = defender.defense + Calc.roll_d6();
				
				trace("\nTurn " + i + " attacker_power: " + attacker_power + " defender power: " + defender_power);
				trace("\attacker_defense: " + attacker_defense + " defender defender_defense: " + defender_defense);
				
				// Attacker go first.
				if (attacker_power > defender_defense)
				{
					trace("defender is down. defense: " + defender_defense);
					defender_soldiers--;
				}
				// If attacker could not kill the defender, then it's the defender turn.
				else if (defender_power > attacker_defense)
				{
					trace("attacker is down. defense: " + attacker_defense);
					attacker_soldiers--;
				}
			}
			
			attacker.takeDamage(attacker.soldiers - attacker_soldiers);
			defender.takeDamage(defender.soldiers - defender_soldiers);
		}
	}
	
}