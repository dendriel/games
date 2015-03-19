LandmineClass = EntityClass.extend(
{
    ticks: 0.05,
    lifetime: 2,
    entity_def: new entityDef("dynamic", 0, 0, 32, 32, false),
    body_phy : null,

    init: function()
    {
        this.id = "Landmine";
        this.curr_sprite_name = "landmine.png";
        this.pos.x = 10;
        this.pos.y = 10;
        console.log("Landmine created!");
    },

    kill: function()
    {
        _killed = true;
    },

    update: function()
    {
        this.lifetime -= this.ticks;
        if (this.lifetime <= 0)
        {
            this.kill();
        }
        
        this.parent();
    }
});

gGameEngine.factory['Landmine'] = LandmineClass;
