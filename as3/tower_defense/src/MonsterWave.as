package src
{
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MonsterWave 
	{
		private var offset:Point; // were to offset so the monsters dont overlay each other.
		private var monsters:Number;
		private var startPoint:Point;
		private var checkpoints:Vector.<Point>;
		private var monsterType:String;
		
		public function MonsterWave(monstersR:Number, startPointR:Point, checkpointsR:Vector.<Point>, offsetR:Point, monsterTypeR:String = Const.SLIME_NAME)
		{
			monsters = monstersR;
			startPoint = startPointR;
			checkpoints = checkpointsR;
			offset = offsetR;
			monsterType = monsterTypeR;
		}
		
		/**
		 * @return The level checkpoints for monsters.
		 */
		public function getCheckpoints() : Vector.<Point>
		{
			return checkpoints;
		}
		
		/**
		 * @return The number of monsters to spawn.
		 */
		public function getMonstersNumber() : Number
		{
			return monsters;
		}
		
		/**
		 * @return The monsters starting point.
		 */
		public function getStartPoint() : Point
		{
			return startPoint;
		}
		
		/**
		 * @return The monsters offset to starting point.
		 */
		public function getStartPointOffset() : Point
		{
			return offset;
		}
		
		/**
		 * @return The type of monster to spawn.
		 */
		public function getMonsterType() : String
		{
			return monsterType;
		}
	}
	
}