//##############################################################################
// Assets handling.
//
var core_assets = ["js/core.js"];
var code_assets = ["js/Spritesheet.js", "js/Frog.js"];

// Media and codes that depend from base classes.
var media_assets = [
    // Code.
    "js/FrogGreen.js",
    "js/FrogBlue.js",
    // JSON.
    "json/leaping_frog_atlas.json", 
    // Images.
    "images/leaping_frog_atlas.png",
    "images/forest_lake_800x600.png"];

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
var gGame_title = "Leaping Frog";
var gGame_win = "Winner!";

var gGreen_frog_prefix = "green_frog_";
var gBlue_frog_prefix = "blue_frog_";

var gFrog_x_start = Math.round(gCanvas_w / 7);
var gFrog_x_offset = Math.round(gFrog_x_start / 4);
var gFrog_y_start = 400;

var gCanvas_obj = null;
var gDraw_ctx = null;

var gFrogs_list = null;

var gExpected_frogs_array = [gBlue_frog_prefix, gBlue_frog_prefix, gBlue_frog_prefix, "empty", gGreen_frog_prefix, gGreen_frog_prefix, gGreen_frog_prefix];

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
    
    gDraw_ctx.font="60px Verdana";
    var gradient = gDraw_ctx.createLinearGradient(0,0, gCanvas_obj.width,0);
    gradient.addColorStop("0.2", "blue");
    gradient.addColorStop("1", "white");
    gDraw_ctx.fillStyle = gradient;
    gDraw_ctx.fillText(gGame_title, px - 50, 100);
    
    add_element_callback("button_play.png",
                        px, py,
                        sprite.w, sprite.h,
                        handle_button_play_pressed);
}

function hide_main_menu()
{
    //gDraw_ctx.clearRect(0, 0, gCanvas_obj.width, gCanvas_obj.height);
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
    
    gFrogs_list = build_frog_array();
    update_game_play();
}

function update_game_play()
{
    if (gFrogs_list === null)
    {
        console.log("Can't update the game play. The frog's list is empty.");
    }
    
    gDraw_ctx.drawImage(gCachedAssets["images/forest_lake_800x600.png"], 0, 0);
    
    for ( var i = 0; i < gFrogs_list.length; i++)
    {
        var element = gFrogs_list[i];
        //console.log(i + " " + element.id + " " + element.pos.x + "," + element.pos.y);
        
        // Add a lily pad in the position.
        drawSprite("lily_pad.png", element.pos.x, element.pos.y, gDraw_ctx);
        
        if (element.id === "empty")
        {
            continue;
        }
        
        drawSprite(element.sprites.standing[0], element.pos.x, element.pos.y, gDraw_ctx);
    }
}

function get_pos_by_id(id)
{
    for ( var i = 0; i < gFrogs_list.length; i++)
    {
        var element = gFrogs_list[i];
        
        if (element.id === id)
        {
            return i;
        }
    }
    
    return -1;
}

function check_movement_allowed(id, from, to)
{
    // Green frogs can go only to right;
    // Blue frogs can go only to left;
    // They can jump only +1 or +2 from its position.
    
    // Handle green frog.
    if (id.indexOf(gGreen_frog_prefix) !== -1)
    {
        // If want to jump to the next position (that is the free pos).
        if ( (from + 1) === to)
        {
            return true;
        }
        // If want to jump over a frog.
        else if ((from + 2) === to)
        {
            // The frog in the middle can't be of the same color.
            if (gFrogs_list[from+1].id.indexOf(gBlue_frog_prefix) !== -1)
            {
                // Blue frog in the middle.
                return true;
            }
            else
            {
                // Green frog in the middle.
                return false;
            }
        }
        // Invalid jump.
        else
        {
            return false;
        }
    }
    // Handle blue frog.
    else
    {
        // If want to jump to the next position (that is the free pos).
        if ( (from - 1) === to)
        {
            return true;
        }
        // If want to jump over a frog.
        else if ((from - 2) === to)
        {
            // The frog in the middle can't be of the same color.
            if (gFrogs_list[from-1].id.indexOf(gGreen_frog_prefix) !== -1)
            {
                // Green frog in the middle.
                return true;
            }
            else
            {
                // Blue frog in the middle.
                return false;
            }
        }
        // Invalid jump.
        else
        {
            return false;
        }
    }
    
    return true;
}

function move_frog(from, to)
{
    var temp_to_ref = gFrogs_list[to];
    var temp_from_x = gFrogs_list[from].pos.x;
    var temp_from_y = gFrogs_list[from].pos.y;
    var temp_to_x = gFrogs_list[to].pos.x;
    var temp_to_y = gFrogs_list[to].pos.y;
    
    gFrogs_list[to] = gFrogs_list[from];
    gFrogs_list[to].pos.x = temp_to_x;
    gFrogs_list[to].pos.y = temp_to_y;
    
    gFrogs_list[from] = temp_to_ref;
    gFrogs_list[from].pos.x = temp_from_x;
    gFrogs_list[from].pos.y = temp_from_y;
    
    update_game_play();
    
    update_element_callback(gFrogs_list[from].id, gFrogs_list[from].pos.x, gFrogs_list[from].pos.y);
    update_element_callback(gFrogs_list[to].id, gFrogs_list[to].pos.x, gFrogs_list[to].pos.y);
}

// Check and handle victory condition.
function check_victory()
{
    for (var i = 0; i < gFrogs_list.length; i++)
    {
        var element = gFrogs_list[i];
        var expected = gExpected_frogs_array[i];
        
        // Check if the expected frog type is in position.
        if (element.id.indexOf(expected) === -1)
        {
            return false;
        }
    }
    
    // All elements are in position.
    return true;
}

function show_victory()
{
    gDraw_ctx.font="60px Georgia";
    gDraw_ctx.fillStyle ="#3333ff";
    gDraw_ctx.fillText(gGame_win, (gCanvas_w / 2) - 100 , 150);
    
    var sprite = get_sprite("replay_button.png");
    var px = align_middle(0, gCanvas_w, sprite.w);
    var py = gCanvas_h / 2 - 100;
    
    drawSprite(sprite.id, px, py, gDraw_ctx);
    
    add_element_callback("restart_button.png",
                        px, py,
                        sprite.w, sprite.h,
                        handle_button_restart_pressed)
}

function handle_button_restart_pressed()
{
    remove_all_element_callback();
    show_game_play();
}

function handle_frog_click(id)
{
    var empty_pos = get_pos_by_id("empty");
    var frog_pos = get_pos_by_id(id);
    
    if (check_movement_allowed(id, frog_pos, empty_pos) !== true)
    {
        console.log("Movement not allowed.");
        return;
    }
    
    move_frog(frog_pos, empty_pos);
    
    if (check_victory() === true)
    {
        console.log("Victory!");
        show_victory();
    }
}

function build_frog_array()
{
    var frogs_list = [];
    var i;
    
    // Create 3 green frogs.
    for (i = 0; i < 3; i++)
    {
        var frog = new FrogGreenClass();
        frog.id = gGreen_frog_prefix + i;
        frog.pos.x = gFrog_x_start * i + gFrog_x_offset;
        frog.pos.y = gFrog_y_start;
        
        var sprite = get_sprite(frog.sprites.standing[0]);
        
        // Add callback for on click.
        add_element_callback(frog.id,
                            frog.pos.x, frog.pos.y,
                            sprite.w, sprite.h,
                            handle_frog_click);
        
        frogs_list.push(frog);
    }
    
    // Create an empty space in the middle.
    var empty = new FrogClass();
    empty.id = "empty";
    empty.pos.x = gFrog_x_start * 3 + gFrog_x_offset;
    empty.pos.y = gFrog_y_start;
    frogs_list.push(empty);
    
    // Create 3 red frogs.
    for (i = 4; i < 7; i++)
    {
        var frog = new FrogBlueClass();
        frog.id = gBlue_frog_prefix + (i - 4);
        frog.pos.x = gFrog_x_start * i + gFrog_x_offset;
        frog.pos.y = gFrog_y_start;
        
        var sprite = get_sprite(frog.sprites.standing[0]);
        
        // Add callback for on click.
        add_element_callback(frog.id,
                            frog.pos.x, frog.pos.y,
                            sprite.w, sprite.h,
                            handle_frog_click);
        
        frogs_list.push(frog);
    }
    
    return frogs_list;
}

//##############################################################################
// Main handling.
//
gElements_callbacks = {};

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
    for (var id in gElements_callbacks)
    {
        var element = gElements_callbacks[id];        
        if (checkInsideBounds(px, py, element.x, element.y, element.w, element.h) === true)
        {
            element.cb(id, element.data);
            break;
        }
    }
}

function add_element_callback(id, x, y, w, h, cb, data)
{
    var element = {
        x : x,
        y : y,
        w : w,
        h : h,
        cb : cb,
        data : data // context data.
       };

    gElements_callbacks[id] = element;
}

function remove_all_element_callback()
{
    gElements_callbacks = {};
}

function remove_element_callback(id)
{
    if (id in gElements_callbacks)
    {
        delete gElements_callbacks[id];
    }
}

function update_element_callback(id, x, y)
{
    if (id in gElements_callbacks)
    {
        gElements_callbacks[id].x = x;
        gElements_callbacks[id].y = y;
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