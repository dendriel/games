package src.utils
{
	import flash.display.Loader;
	import flash.events.Event;
	import flash.display.MovieClip;
	import flash.events.IOErrorEvent;
	import flash.events.ProgressEvent;
	import flash.net.URLRequest;


	public class Image extends MovieClip 
	{
		protected var loader:Loader;
		protected var loader_width:uint;
		protected var loader_height:uint;
		

		public function Image (path:String, width:uint, height:uint) 
		{
			loader_width = width;
			loader_height = height;
			
			loader = new Loader();
			loader.contentLoaderInfo.addEventListener(ProgressEvent.PROGRESS, progressListener, false, 0, true);
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, completeListener, false, 0, true);
			loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, ioErrorListener, false, 0, true);
			loader.load(new URLRequest(path));
		}


		protected function progressListener(event:ProgressEvent) : void
		{ 
		}
		
		private function ioErrorListener(e:IOErrorEvent) : void
		{
			trace("LOAD ERROR: " + e.text);
		}
		
		protected function completeListener(event:Event) : void 
		{
			loader.width = loader_width;
			loader.height = loader_height;
			addChild(loader);
		}
	}
}
