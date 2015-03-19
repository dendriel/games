FACING_NONE = -1;
FACING_DOWN = 0;
FACING_UP = 1;
FACING_LEFT = 2;
FACING_RIGHT = 3;

EntityClass = Class.extend(
{
    id : "not set",
    pos : {x : 0, y : 0},
    size : {w : 0, h : 0},
    last : {x : 0, y : 0},
    _killed : false,
    sprites : {
        up: new Array(),
        right: new Array(),
        down: new Array(),
        left: new Array()
    },
    facing : FACING_DOWN,
    curr_sprite : null,
    zIndex : 0,
    
    update : function() {},
    
    draw : function(drawctx)
    {
        if (this.curr_sprite === null)
        {
            return;
        }
        drawSprite(this.curr_sprite,
        this.pos.x - this.size.w/2,
        this.pos.y - this.size.h/2,
        drawctx);
    },
    
    onTouch : function(body, unused, impulse)
    {
        console.log("onTouch function is not implemented.");
    }
});
