package src
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameTimerSemesterEvent extends Event
	{
		public static const EVT_TIMER_SEMESTER:String = "timer semester";
		
		public function GameTimerSemesterEvent(bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(GameTimerSemesterEvent.EVT_TIMER_SEMESTER, bubbles, cancelable);
		}
		
		public override function clone() : Event
		{
			return new GameTimerSemesterEvent(bubbles, cancelable);
		}
	}
	
}