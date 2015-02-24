package src.units
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import src.IElementInfo;
	import src.ElementType;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnit extends MovieClip implements IElementInfo, IElementUnitInfo
	{
		// Unique identifier.
		private var _uid:int;
		// Type identifier for map building.
		protected var _id:int;
		
		// Element type identifier;
		private var _type:int = ElementType.UNIT;
		protected var _name:String;
		protected var _desc:String;
		
		// Unit type attributes.
		protected var _soldiers_max;      //! Maximum number of soldiers that can hold.
		protected var _soldiers;    //! Number of soldiers that can fight.
		protected var _soldiers_injuried; //! Number of soldiers that are hurt and can't fight;
		protected var _health_max;
		protected var _health;
		protected var _attack;
		protected var _defense;
		protected var _distance;
		protected var _move_time;			//! Time to move a square in days.
		protected var _recruit_cost;
		
		// Action definitions.
		private var busy:Boolean;
		private var moveTimer:Timer;
		private var moveFrom:int;
		private var moveTo:int;
		
		// Unit advantages and disadvantages.
		
//##################################################################################################
		// Unique building identifier.
		private static var uid_count:int;
		
		/**
		 * @return An unique identifier for the unit.
		 */
		public static function generateUID() : int
		{
			var new_uid = uid_count;
			uid_count++;
			return new_uid;
		}
//##################################################################################################

		public function GameUnit()
		{
			_uid = GameUnit.generateUID();
			moveTimer = new Timer(0);
			moveTimer.addEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_move, false, 0, true);
			busy = false;
		}
		
		public function get uid() : int {return _uid;}
		public function get id():int { return _id; }
		
		public function get elemType():int {return _type;}
		public function get elemName():String { return _name; }
		public function get elemDesc():String { return _desc; }
		
		public function get soldiers_max() : int { return _soldiers_max; }
		public function get soldiers() : int { return _soldiers; }
		public function get soldiers_injuried() : int { return _soldiers_injuried; }
		public function get health_max() : int { return _health_max; }
		public function get health() : int { return _health; }
		public function get attack() : int { return _attack; }
		public function get defense() : int { return _defense; }
		public function get distance() : int { return _distance; }
		public function get move_time() : int { return _move_time; }
		public function get recruit_cost() : int { return _recruit_cost; }
		
		/**
		 * Call after processing an unit action.
		 */
		public function unBusy() : void
		{
			busy = false;
		}
		
		/**
		 * @brief Schedule unit movement.
		 */
		public function move(from:int, to:int) : void
		{
			if (busy == true)
			{
				// Unit movement can be canceled.
				trace("Unit is busy right now. Restarting movement timer.");
				moveTimer.stop();
			}
			
			busy = true;
			
			moveFrom = from;
			moveTo = to;
			
			moveTimer.delay = _move_time * Const.DAY_TIME_MS;
			moveTimer.repeatCount = 1;
			
			moveTimer.reset();
			moveTimer.start();
			trace("start!!");
		}
		
		private function handleTimerComplete_move(e:TimerEvent) : void
		{
			trace("dispatch!!");
			dispatchEvent(new UnitMoveEvent(_uid, moveFrom, moveTo));
		}
	}
	
}