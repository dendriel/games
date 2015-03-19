EntityClass = Class.extend(
{
    id : "not set",
    pos : {x : 0, y : 0},
    size : {w : 0, h : 0},
    last : {x : 0, y : 0},
    _killed : false,
    curr_sprite_name : null,
    zIndex : 0,
    
    update : function() {},
    
    draw : function(drawctx)
    {
        if (this.curr_sprite_name === null)
        {
            return;
        }
        drawSprite(this.curr_sprite_name,
        this.pos.x - this.size.w/2,
        this.pos.y - this.size.h/2,
        drawctx);
    },
    
    onTouch : function(body, unused, impulse)
    {
        console.log("onTouch function is not implemented.");
    }
});
