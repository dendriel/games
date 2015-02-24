package src
{
	import flash.display.MovieClip;
	import flash.events.TimerEvent;
	import flash.text.TextField;
    import flash.utils.Timer;
	import src.ui.GameTextFormat;
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameTimer extends MovieClip
	{
		// Static values.
		public static const JANUARY  = 0;
		public static const FEBRUARY = 1;
		public static const MARCH    = 2;
		public static const APRIL    = 3;
		public static const MAY      = 4;
		public static const JUN      = 5;
		public static const JULY     = 6;
		public static const AUGUST   = 7;
		public static const SEPTEMBER = 8;
		public static const OCTOBER  = 9;
		public static const NOVEMBER = 10;
		public static const DECEMBER = 11;
		
		private const yearInDays:int = 365;
		
		private var year_counter:int;
		private var month_counter:int;
		private var days_counter:int;
		private var timerCounter:Timer;
		private var displayTxt:TextField;
		
		public function GameTimer()
		{
			timerCounter = new Timer(Const.DAY_TIME_MS, yearInDays);
			year_counter = 1;
			month_counter = GameTimer.JANUARY;
			days_counter = 0;
			
			timerCounter.addEventListener(TimerEvent.TIMER, handleTimer, false, 0, true);
			timerCounter.addEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete, false, 0, true);
			
			displayTxt = new TextField();
			displayTxt.defaultTextFormat = GameTextFormat.displayTimerFormat;
			displayTxt.textColor = GameTextFormat.displayFieldsColor;
			displayTxt.selectable = false;
			displayTxt.mouseEnabled = false;
			displayTxt.x = 0;
			displayTxt.y = 0;
			
			addChild(displayTxt);
			
			updateTimerTxt();
		}
		
		public function start() : void
		{
			timerCounter.start();
		}

		// Handle day/month
        private function handleTimer(e:TimerEvent) : void
		{
			days_counter++;
			trace("days: " + days_counter + "; currentCount: " + timerCounter.currentCount);
			
			if (days_counter <= 31)
			{
				month_counter = GameTimer.JANUARY;
			}
			else if ( (days_counter >= 32) && (days_counter <= 59) )
			{
				month_counter = GameTimer.FEBRUARY;
			}
			else if ( (days_counter >= 60) && (days_counter <= 90) )
			{
				month_counter = GameTimer.MARCH;
			}
			else if ( (days_counter >= 91) && (days_counter <= 120) )
			{
				month_counter = GameTimer.APRIL;
			}
			else if ( (days_counter >= 121) && (days_counter <= 151) )
			{
				month_counter = GameTimer.MAY;
			}
			else if ( (days_counter >= 152) && (days_counter <= 181) )
			{
				month_counter = GameTimer.JUN;
			}
			else if ( (days_counter >= 182) && (days_counter <= 212) )
			{
				month_counter = GameTimer.JULY;
			}
			else if ( (days_counter >= 213) && (days_counter <= 243) )
			{
				month_counter = GameTimer.AUGUST;
			}
			else if ( (days_counter >= 244) && (days_counter <= 273) )
			{
				month_counter = GameTimer.SEPTEMBER;
			}
			else if ( (days_counter >= 274) && (days_counter <= 304) )
			{
				month_counter = GameTimer.OCTOBER;
			}
			else if ( (days_counter >= 305) && (days_counter <= 334) )
			{
				month_counter = GameTimer.NOVEMBER;
			}
			else /*if ( (days_counter >= 335) && (days_counter <= 365) ) */
			{
				month_counter = GameTimer.DECEMBER;
			}
			
			updateTimerTxt();
        }

		// Handle Year.
        private function handleTimerComplete(e:TimerEvent) : void
		{
			year_counter++;
			days_counter = 0;
			month_counter = GameTimer.JANUARY;
			updateTimerTxt();
			
			timerCounter.reset();
			timerCounter.start();
			trace(timerCounter.currentCount);
        }
		
		private function updateTimerTxt() : void
		{
			var month:String;
			
			switch (month_counter)
			{
				case GameTimer.JANUARY:
					month = GameLanguage.lang.january_str;
					break;
				case GameTimer.FEBRUARY:
					month = GameLanguage.lang.february_str;
					break;
				case GameTimer.MARCH:
					month = GameLanguage.lang.march_str;
					break;
				case GameTimer.APRIL:
					month = GameLanguage.lang.april_str;
					break;
				case GameTimer.MAY:
					month = GameLanguage.lang.may_str;
					break;
				case GameTimer.JUN:
					month = GameLanguage.lang.jun_str;
					break;
				case GameTimer.JULY:
					month = GameLanguage.lang.july_str;
				break;
				case GameTimer.AUGUST:
					month = GameLanguage.lang.august_str;
					break;
				case GameTimer.SEPTEMBER:
					month = GameLanguage.lang.september_str;
					break;
				case GameTimer.OCTOBER:
					month = GameLanguage.lang.october_str;
					break;
				case GameTimer.NOVEMBER:
					month = GameLanguage.lang.november_str;
					break;
				case GameTimer.DECEMBER:
					month = GameLanguage.lang.december_str;
					break;
				default:
					trace("Invalid month id received: " + month_counter);
					month = GameLanguage.lang.january_str;
					break;
			}
			
			displayTxt.text = month + " " + GameLanguage.lang.of_the_year_str + " " + String(year_counter);
			displayTxt.width = displayTxt.textWidth + 4;
			displayTxt.height = displayTxt.textHeight + 4;
		}
	}
	
}