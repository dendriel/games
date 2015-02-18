package src.ui
{
	import flash.display.MovieClip;
	import src.utils.Image;
	import src.MediaSource;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MainMenu extends MovieClip 
	{
		private const px:Number = 0;
		private const py:Number = 0;
		
		private var bg:Image;
		
		
		public function MainMenu() : void
		{
			bg = new Image(MediaSource.MAIN_MENU_BG_LOC,
							MediaSource.MAIN_MENU_W,
							MediaSource.MAIN_MENU_H);
			this.addChild(bg);
			this.x = px;
			this.y = py;
		}
	}
	
}