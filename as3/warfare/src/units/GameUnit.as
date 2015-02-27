package src.units
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import src.IElementInfo;
	import src.ElementType;
	import src.Const;
	import src.as3.math.graph.*;
	import src.as3.math.Calc;
	import src.tiles.ConstTile;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnit extends MovieClip implements IElementInfo, IElementUnitInfo
	{
		// Constants.
		private const focusSignRadiusW:Number = ConstTile.TILE_W;
		private const focusSignRadiusH:Number = ConstTile.TILE_H / 2;
		private const focusSignRadiusPosX:Number = 0;
		private const focusSignRadiusPosY:Number = ConstTile.TILE_H / 2;
		
		private const busySignPosX:Number = ConstTile.TILE_W - 8;
		private const busySignPosY:Number = -12;
		
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
		private var _busy:Boolean;
		private var moveTimer:Timer;
		private var movePath:Vector.<SPFNode>;
		private var moveTo:SPFNode;
		private var moveFrom:int;
		
		// Images.
		protected var _topImg:MovieClip;
		private var _focusSign:Shape;
		private var _busySign:HourglassSign;
		
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
			drawSigns();
			busy = false;
			trace("Number of childs: " + this.numChildren);
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
		
		public function get topImg() : MovieClip { return _topImg; }
		
		public function set focusSign(value:Boolean) : void { _focusSign.visible = value; }
		
		/**
		 * Call after processing an unit action.
		 */
		public function unBusy() : void
		{
			if (movePath == null)
			{
				_busy = false;
				_busySign.visible = false;
			}
		}
		
		private function set busy(value:Boolean) : void
		{
			_busy = value;
			_busySign.visible = value;
		}
		
		/**
		 * Schedule unit movement.
		 */
		public function move(fromIdx:int, path:Vector.<SPFNode>) : void
		{
			if (_busy == true)
			{
				// Unit movement can be canceled.
				trace("Unit is busy right now. Restarting movement timer.");
				moveTimer.stop();
			}
			
			busy = true;
			movePath = path;
			moveFrom = fromIdx;
				
			// We know that the first node on the list is the own node, so we discard it.
			moveTo = movePath.pop();
			
			scheduleMovement();
		}

//##################################################################################################
// Private functions.
//##################################################################################################
		private function drawSigns() : void
		{
			_focusSign = new Shape();
			_focusSign.graphics.beginFill(0xffffcc);
			_focusSign.graphics.drawEllipse(focusSignRadiusPosX, focusSignRadiusPosY, focusSignRadiusW, focusSignRadiusH);
			_focusSign.graphics.drawEllipse(focusSignRadiusPosX, focusSignRadiusPosY, focusSignRadiusW - 2, focusSignRadiusH - 2);
			_focusSign.graphics.endFill();
			_focusSign.visible = false;
			addChildAt(_focusSign, 0);
			
			_busySign = new HourglassSign();
			_busySign.x = busySignPosX;
			_busySign.y = busySignPosY;
			_busySign.visible = false;
			addChildAt(_busySign, 0);
		}

		private function scheduleMovement() : void
		{
			trace("Next node is " + moveTo.uid);
			
			moveTo = movePath.pop();
			
			moveTimer.delay = _move_time * Const.DAY_TIME_MS;
			moveTimer.repeatCount = 1;
			
			if (movePath.length == 0)
			{
				movePath = null;
			}
			
			moveTimer.reset();
			moveTimer.start();
		}
		
		private function handleTimerComplete_move(e:TimerEvent) : void
		{
			trace("Unit on move!");
			dispatchEvent(new UnitMoveEvent(_uid, moveFrom, moveTo.uid));
			
			if (movePath == null)
			{
				moveFrom = -1;
				moveTo = null;
				// Unit finished moving.
				return;
			}
			
			moveFrom = moveTo.uid;
			scheduleMovement()
		}
	}
	
}