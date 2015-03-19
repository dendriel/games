LandmineClass = EntityClass.extend(
{
    entity_def: new entityDef("dynamic", 0, 0, 30, 28, false),
    body_phy : null,

    init: function()
    {
        this.id = "Landmine";
        
        var explosion_list = gen_sprite_names("landmine_explosion_large_000", 0, 9, ".png");
        explosion_list = explosion_list.concat(gen_sprite_names("landmine_explosion_large_00", 10, 29, ".png"));
        
        this.sprites.up = explosion_list;
        
        this.curr_sprite = "landmine.png";
        this.facing = FACING_NONE;
    },

    kill: function()
    {
        _killed = true;
    },
    
    onTouch: function()
    {
        this.facing = FACING_UP;
    },
    
    draw: function(drawctx)
    {
        if (this.facing === FACING_UP)
        {
            var sprite_index = this.sprites.up.indexOf(this.curr_sprite);
            if (sprite_index === -1)
            {
                console.log("here");
                this.curr_sprite = this.sprites.up[0];
            }
            else
            {
                sprite_index++;
                if (sprite_index >= this.sprites.up.length)
                {
                    this.kill();
                    return;
                }
                this.curr_sprite = this.sprites.up[sprite_index];
            }
        }
        
        this.parent(drawctx);
    }
});

gGameEngine.factory['Landmine'] = LandmineClass;
