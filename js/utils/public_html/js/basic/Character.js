CharacterClass = EntityClass.extend(
{
    nick: "",
    move_dir: new Vec2(0,0),
    speed: 10,
    entity_def: new entityDef("dynamic", 0, 0, 32, 32, false),
    body_phy : null,
    
    init: function()
    {
        this.id = "Player";
        
        var walk_down_list = gen_sprite_names("walk_down_000", 0, 9, ".png");
        walk_down_list = walk_down_list.concat(gen_sprite_names("walk_down_00", 10, 29, ".png"));
        this.sprites.down = walk_down_list;
        
        var walk_up_list = gen_sprite_names("walk_up_000", 0, 9, ".png");
        walk_up_list = walk_up_list.concat(gen_sprite_names("walk_up_00", 10, 29, ".png"));
        this.sprites.up = walk_up_list;
        
        var walk_left_list = gen_sprite_names("walk_left_000", 0, 9, ".png");
        walk_left_list = walk_left_list.concat(gen_sprite_names("walk_left_00", 10, 29, ".png"));
        this.sprites.left = walk_left_list;
        
        var walk_right_list = gen_sprite_names("walk_right_000", 0, 9, ".png");
        walk_right_list = walk_right_list.concat(gen_sprite_names("walk_right_00", 10, 29, ".png"));
        this.sprites.right = walk_right_list;
        
        this.curr_sprite = this.sprites.down[0];
        
//        this.curr_sprite_name = "legs.png";
//        this.curr_sprite_name = "machinegun.png";
//        this.curr_sprite_name = "turret.png";
//        this.curr_sprite_name = "turret_player_color.png";
    },
    
    draw: function(drawctx)
    {
        var next_sprite_name = this.curr_sprite;
        
        switch(this.facing)
        {
            case FACING_UP:
                var curr_index = this.sprites.up.indexOf(this.curr_sprite);
                if (curr_index !== -1)
                {
                    next_sprite_name = this.sprites.up[(curr_index + 1) % this.sprites.up.length];
                }
                else
                {
                    next_sprite_name = this.sprites.up[0];
                }
                break;
            
            case FACING_LEFT:
                var curr_index = this.sprites.left.indexOf(this.curr_sprite);
                if (curr_index !== -1)
                {
                    next_sprite_name = this.sprites.left[(curr_index + 1) % this.sprites.left.length];
                }
                else
                {
                    next_sprite_name = this.sprites.left[0];
                }
                break;
                
            case FACING_RIGHT:
                var curr_index = this.sprites.right.indexOf(this.curr_sprite);
                if (curr_index !== -1)
                {
                    next_sprite_name = this.sprites.right[(curr_index + 1) % this.sprites.right.length];
                }
                else
                {
                    next_sprite_name = this.sprites.right[0];
                }
                break;
            
            case FACING_DOWN:
                var curr_index = this.sprites.down.indexOf(this.curr_sprite);
                if (curr_index !== -1)
                {
                    next_sprite_name = this.sprites.down[(curr_index + 1) % this.sprites.down.length];
                }
                else
                {
                    next_sprite_name = this.sprites.down[0];
                }
                break;
                
            case FACING_NONE:
            default:
                break;
        }
        this.curr_sprite = next_sprite_name;
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