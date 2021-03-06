// We keep a global dictionary of loaded sprite-sheets, which are each an
// instance of our SpriteSheetClass below.
//
// This dictionary is indexed by the URL path that the atlas is located at. For
// example, calling:
//
// gSpriteSheets['grits_effects.png'] 
//
// would return the SpriteSheetClass object associated
// to that URL, assuming that it exists.
var gSpriteSheets = {};

//-----------------------------------------
SpriteSheetClass = Class.extend(
{
    img: null, // The Image object that we created for our atlas.
    url: "",   // The URL path that we grabbed our atlas from.
    sprites: new Array(), // An array of all the sprites in our atlas.

    //-----------------------------------------
    init: function () {},

    //-----------------------------------------
    // Load the atlas at the path 'imgName' into memory.
    load: function (img_path, img_data)
    {
        this.url = img_path;	// Store the URL of the spritesheet we want.
        this.img = img_data;

        // Store this SpriteSheetClass in our global dictionary.
        gSpriteSheets[this.url] = this;
        console.log("New spritesheet loaded: \"" + img_path + "\"");
    },

    //-----------------------------------------
    // Define a sprite for this atlas
    defSprite: function (name, x, y, w, h, cx, cy)
    {
        var spt = {
                "id": name,
                "x": x,
                "y": y,
                "w": w,
                "h": h,
                "cx": cx == null ? 0 : cx,
                "cy": cy == null ? 0 : cy
        };
        
        this.sprites.push(spt);
    },

    //-----------------------------------------
    // Parse the JSON file passed in as 'atlasJSON' that is associated to this
    // atlas.
    parseAtlasDefinition: function (atlasJSON)
    {
        //var data = JSON.parse(atlasJSON);
        var data = atlasJSON;
        
        for (var i = 0; i < data.frames.length; i++)
        {
            var sprite = data.frames[i];
            var sprite_name = i;

            var cx = -1 * Math.ceil(sprite.frame.w / 2);
            var cy = -1 * Math.ceil(sprite.frame.h / 2);
            
            //if (sprite.trimmed === true)
           // {
           //     cx  = sprite.spriteSourceSize.x - (sprite.sourceSize.w / 2);
           //     cy  = sprite.spriteSourceSize.y - (sprite.sourceSize.h / 2);
           // }

            this.defSprite(sprite_name,
                        sprite.frame.x,
                        sprite.frame.y,
                        sprite.frame.w,
                        sprite.frame.h,
                        cx,
                        cy);
        }
    },

    //-----------------------------------------
    // Walk through all the sprite definitions for this atlas, and find which
    // one matches the name.
    // Return the sprite indexed by 'name'; or null if the sprite was not found.
    getStats: function (name)
    {
        for(var i = 0; i < this.sprites.length; i++)
        {
            if(this.sprites[i].id === name)
            {
                return this.sprites[i];
            }
        }
        return null;
    }

});

//-----------------------------------------
// External-facing function for drawing sprites based on the sprite name.
function drawSprite(spritename, posX, posY, drawctx)
{
    // Find the spritesheet that contains the wanted sprite.
    for (var i in gSpriteSheets)
    {
        var sheet = gSpriteSheets[i];
        
        var sprite = sheet.getStats(spritename);
        if (sprite !== null)
        {
            __drawSpriteInternal(sprite, sheet, posX, posY, drawctx);
            break;
        }
    }

}

//-----------------------------------------
// External-facing function for drawing sprites based on the sprite object
// stored from the 'sprites' Array inside the 'SpriteSheetClass' object, and the
// position on canvas to draw to.
function __drawSpriteInternal(spt, sheet, posX, posY, drawctx)
{
    if ( (spt === null) || (sheet === null) || (drawctx === null) )
    {
        return;
    }
    drawctx.drawImage(sheet.img,
                spt.x, spt.y, // from
                spt.w, spt.h, // from
                posX + spt.cx, posY + spt.cy, // to
                spt.w, spt.h); // to
    //drawctx.drawImage(sheet.img, spt.x, spt.y, spt.w, spt.h, posX, posY, spt.w, spt.h);
}
    
function gen_sprite_names(prefix, start, end, suffix)
{
    var sprites_list = new Array();

    for (var i = start; i <= end; i++)
    {
        var sprite_name = prefix + i + suffix;
        sprites_list.push(sprite_name);
    }
    return sprites_list;
}

//var body = document.getElementById("body");
//var canvas = document.createElement("canvas");
//canvas.setAttribute('width', 500);
//canvas.setAttribute('height', 700);
//var drawctx = canvas.getContext("2d");
//
//drawctx.fillStyle = "#ff00ff";
//drawctx.fillRect(0,0,500,700);
////canvas.style.opacity = '0.2';
//
//body.appendChild(canvas);
//
//var obj = new SpriteSheetClass();
//var getCb = function(response)
//{
//    obj.parseAtlasDefinition(response);
//    obj.load("images", "grits_effects.png");
//};
//
//$.getJSON("js/grits_effects.json", getCb);
//
//setTimeout(function()
//{
//    drawSprite("chaingun_impact_0000.png", 10, 10);
//},
//1000);