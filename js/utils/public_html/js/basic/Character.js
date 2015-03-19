CharacterClass = EntityClass.extend(
{
    nick: "",
    move_dir: new Vec2(0,0),
    speed: 20,
    entity_def: new entityDef("dynamic", 0, 0, 32, 32, false),
    body_phy : null,
    
    init: function()
    {
        this.curr_sprite_name = "walk_down_0000.png";
    },
    
    draw: function(drawctx)
    {
        var pos = this.body_phy.GetPosition();
        this.pos.x = pos.x;
        this.pos.y = pos.y;
        this.parent(drawctx);
    },
    
    onTouch : function(body, unused, impulse)
    {
        console.log("Character touched a " + body.id);
    }
});

gGameEngine.factory['Character'] = CharacterClass;

function Character(name, image_path, sufix, length, canvasdraw)
{
    this.name = name;
    this.image_path = image_path;     // image path prefix.
    this.sufix = sufix;
    this.canvasdraw = canvasdraw;
    this.length = length;
    this.image_arr = [];    // internal use.
    this.loaded = 0;        // internal use.
    this.curr_frame = 0;    // internal use.
    
    // On load image callback.
    this.onImageLoadCb = function ()
    {
        this.loaded++;
    };
    
    // Load character images.
    this.load = function()
    {
        for (var i = 0; i < length; i++)
        {
            var image = new Image();
            image.onload = this.onImageLoadCb();
            image.src = this.image_path + (i+1) + this.sufix;
            this.image_arr[i] = image;
        }
    };
    
    // Animate character callback.
    this.animateCb = function()
    {
        // TODO: use dinamic values.
        this.canvasdraw.clearRect(0, 0, 500, 700);
        this.canvasdraw.drawImage(this.image_arr[this.curr_frame], 0, 0);
        this.curr_frame = (this.curr_frame+1) % length;
    };
    
    // Animate character.
    this.animate = function(delay)
    {
        if (this.loaded < this.length)
        {
            console.log("Not all images were loaded. " + this.loaded + "/" + this.length);
            return;
        }
        var self = this;
        setInterval(function() { self.animateCb(); }, delay);
    };
};