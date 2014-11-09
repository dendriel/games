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
		
		public function MonsterWave(monsters:Number, startPoint:Point, checkpoints:Vector.<Point>, offset:Point)
		{
			this.monsters = monsters;
			this.startPoint = startPoint;
			this.checkpoints = checkpoints;
			this.offset = offset;
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
	}
	
}