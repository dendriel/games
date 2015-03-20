//##############################################################################
// Assets handling.
//
var core_assets = ["js/core.js"];
var code_assets = ["js/Spritesheet.js"];
var media_assets = ["json/leaping_frog_atlas.json", "images/leaping_frog_atlas.png", "images/forest_lake_800x600.png"];

function load_core_assets()
{
    loadAssets(core_assets,
    function(assetsList)
    {
        console.log("Core assets were loaded. Start loading code assets.");
        load_code_assets();
    });
}

function load_code_assets()
{
    loadAssets(code_assets,
    function(assetsList)
    {
        console.log("Code assets were loaded. Start loading media assets.");
        load_media_assets();
    });
}

function load_media_assets()
{
    loadAssets(media_assets,
    function(assetsList)
    {
        console.log("Code assets were loaded. Call main.");
        
        // Load our only atlas.        
        var sheet = new SpriteSheetClass();
        var sheet_asset = gCachedAssets["json/leaping_frog_atlas.json"];
        var img_path = "images/" + sheet_asset.meta.image;
        var img_data = gCachedAssets[img_path];
        sheet.parseAtlasDefinition(sheet_asset);
        sheet.load(img_path, img_data);
        
        // Call main line.
        main();
    });
}

//##############################################################################
// DOM handling.
//
var gBody = null;
var gBody_div_name = "body";
var gCanvas_w = 800;
var gCanvas_h = 600;

var gCanvas_obj = null;
var gDraw_ctx = null;

// Make gDrawCtx available.
function create_canvas()
{
    gBody = document.getElementById(gBody_div_name);
    gCanvas_obj = document.createElement("canvas");
    
    gCanvas_obj.setAttribute("width", gCanvas_w);
    gCanvas_obj.setAttribute("height", gCanvas_h);
    
    gBody.appendChild(gCanvas_obj);
    
    gDraw_ctx = gCanvas_obj.getContext("2d");
}

function show_main_menu()
{
    gDraw_ctx.drawImage(gCachedAssets["images/forest_lake_800x600.png"], 0, 0);
    
    var sprite = get_sprite("button_play.png");
    var px = align_middle(0, gCanvas_w, sprite.w);
    var py = gCanvas_h / 2;
    
    drawSprite(sprite.id, px, py, gDraw_ctx);
    
    add_element_callback("button_play.png",
                        px, py,
                        sprite.w, sprite.h,
                        handle_button_play_pressed,
                        null);
}

function hide_main_menu()
{
    gCanvas_obj.clearRect(0, 0, gCanvas_obj.width, gCanvas_obj.height);
    remove_element_callback("button_play.png");
}

function handle_button_play_pressed()
{
    hide_main_menu();
    show_game_play();
}

function show_game_play()
{
    console.log("GamePlay");
}

//##############################################################################
// Main handling.
//
gElements_callbacks = [];

function main()
{
    console.log("All code and media were loaded.");
    
    create_canvas();
    
    // User Interaction.
    gCanvas_obj.onclick = handle_mouse_click;
    
    // Display main menu.
    show_main_menu();
}

// Bootstrap.
load_core_assets();


function handle_mouse_click(e)
{
    var rect = gCanvas_obj.getBoundingClientRect();
    var px = e.clientX - rect.left;
    var py = e.clientY - rect.top;
    
    // Check if clicked on something.
    for (var i = 0; i < gElements_callbacks.length; i++)
    {
        var element = gElements_callbacks[i];
        
        if (checkInsideBounds(px, py, element.x, element.y, element.w, element.h) === true)
        {
            element.cb(element.data);
        }
    }
}

function add_element_callback(id, x, y, w, h, cb, data)
{
    var element = {
        id : id,
        x : x,
        y : y,
        w : w,
        h : h,
        cb : cb,
        data : data // context data.
       };
       
       gElements_callbacks.push(element);
}

function remove_element_callback(id)
{
    if (gElements_callbacks.indexOf(id) !== -1)
    {
        gElements_callbacks.splice(gElements_callbacks.indexOf(id), 1);
    }
}

//##############################################################################
// Utils.
//
function align_middle(obj1_px, obj1_w, obj2_w)
{
    var ref_middle = obj1_px + ( (obj1_w / 2) + (obj1_w % 2) );
    return (ref_middle - ( (obj2_w / 2) + (obj2_w % 2) ));
}

function checkInsideBounds (px, py, ax, ay, aw, ah)
{
    if ( (px < ax) || (px >= (ax + aw) ) )
    {
            return false;
    }
    else if ( (py < ay) || (py >= (ay + ah) ) )
    {
            return false;
    }

    return true;
}