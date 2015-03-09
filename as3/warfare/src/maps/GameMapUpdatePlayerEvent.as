package src.maps
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameMapUpdatePlayerEvent extends Event
	{
		public static const EVT_MAP_UPDATE_PLAYER:String = "update player";
		
		public function GameMapUpdatePlayerEvent(bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(GameMapUpdatePlayerEvent.EVT_MAP_UPDATE_PLAYER, bubbles, cancelable);
		}
		
		public override function clone() : Event
		{
			return new GameMapUpdatePlayerEvent(bubbles, cancelable);
		}
	}
	
}