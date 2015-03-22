//##############################################################################
// Assets handling.
//
var core_assets = ["js/core.js", "js/Box2dWeb-2.1.a.3.min.js", "js/howler.min.js"];
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
    "images/forest_lake_800x600.png",
    // Audio.
    "sounds/frog.mp3", //"sounds/Tiny_Frog-SoundBible.com-1771194786.mp3"
    "sounds/frogs_enter.mp3", // frogs-croaking-suburb-area_fJ17rrNu
    "sounds/winning.mp3"    // Ta Da-SoundBible.com-1884170640_mod.mp3
];

function loadCoreAssets()
{
    loadAssets(core_assets,
    function(assetsList)
    {
        console.log("Core assets were loaded. Start loading code assets.");
        loadCodeAssets();
    });
}

function loadCodeAssets()
{
    loadAssets(code_assets,
    function(assetsList)
    {
        console.log("Code assets were loaded. Start loading media assets.");
        loadMediaAssets();
    });
}

function loadMediaAssets()
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
var gGame_lost = "Time's up!";
var gTime_limit = 60;
var gCenter_frogs_offset = 5; // Center the frogs better in the lily pad.
var gVictory_flag = false;

var gGreen_frog_prefix = "green_frog_";
var gBlue_frog_prefix = "blue_frog_";

var gFrog_x_start = Math.round(gCanvas_w / 7);
var gFrog_x_offset = Math.round(gFrog_x_start / 4);
var gFrog_y_start = 400;

var gCanvas_obj = null;
var gDraw_ctx = null;

var gFrogs_list = null;

var gAnimation_delay = 1000/60;
var gStarting_pos = {x:0, y:0};

var gTimer = {
    x : 10,
    y : 50,
    value : 0,
    id : 0
};

var gExpected_frogs_array = [gBlue_frog_prefix, gBlue_frog_prefix, gBlue_frog_prefix, "empty", gGreen_frog_prefix, gGreen_frog_prefix, gGreen_frog_prefix];

// Make gDrawCtx available.
function createCanvas()
{
    gBody = document.getElementById(gBody_div_name);
    gCanvas_obj = document.createElement("canvas");
    
    gCanvas_obj.setAttribute("width", gCanvas_w);
    gCanvas_obj.setAttribute("height", gCanvas_h);
    
    gBody.appendChild(gCanvas_obj);
    
    gDraw_ctx = gCanvas_obj.getContext("2d");
}

function showMainMenu()
{
    gDraw_ctx.drawImage(gCachedAssets["images/forest_lake_800x600.png"], 0, 0);
    
    var sprite = get_sprite("button_play.png");
    var px = alignMiddle(0, gCanvas_w, sprite.w);
    var py = gCanvas_h / 2;
    
    drawSprite(sprite.id, px, py, gDraw_ctx);
    
    gDraw_ctx.font="60px Verdana";
    var gradient = gDraw_ctx.createLinearGradient(0,0, gCanvas_obj.width,0);
    gradient.addColorStop("0.2", "blue");
    gradient.addColorStop("1", "white");
    gDraw_ctx.fillStyle = gradient;
    gDraw_ctx.fillText(gGame_title, px - 50, 100);
    
    addElementCallback("button_play.png",
                        px, py,
                        sprite.w, sprite.h,
                        handleButtonPlayPressed);
}

function hideMainMenu()
{
    //gDraw_ctx.clearRect(0, 0, gCanvas_obj.width, gCanvas_obj.height);
    removeElementCallback("button_play.png");
}

function handleButtonPlayPressed()
{
    gCachedAssets["sounds/frogs_enter.mp3"].play();
    hideMainMenu();
    showGamePlay();
}

function showGamePlay()
{
    console.log("GamePlay");
    
    gFrogs_list = buildFrogArray();
    
    // Register replay button.
    var sprite = get_sprite("replay_button.png");
    // The bounds that we will check for click is with the original image size.
    // We don't need to bother with this now. *maybe resize the raw image.
    addElementCallback("restart_button.png",
                        (gCanvas_w - sprite.w), 0,
                        sprite.w, sprite.h,
                        handleButtonReplayPressed);

    clearInterval(gTimer.id);
    gTimer.id = setInterval(updateTimer, 1000);
    
    updateGamePlay();
}

function updateTimer()
{
    gTimer.value++;
    
    if (gTimer.value === gTime_limit)
    {
            console.log("Time's up!");
            clearInterval(gTimer.id);
            gVictory_flag = true;
            removeAllElementCallback();
            
            var sprite = get_sprite("replay_button.png");
            addElementCallback("restart_button.png",
                        (gCanvas_w - sprite.w), 0,
                        sprite.w, sprite.h,
                        handleButtonReplayPressed);
                        
            updateGamePlay();
            showLost();
            return;
    }
    
    updateGamePlay();
}

function updateGamePlay()
{
    var i;
    
    if (gFrogs_list === null)
    {
        console.log("Can't update the game play. The frog's list is empty.");
    }
    
    // Draw background.
    gDraw_ctx.drawImage(gCachedAssets["images/forest_lake_800x600.png"], 0, 0);
    
    // Draw timer.
    gDraw_ctx.font="40px sans-serif";
    gDraw_ctx.fillStyle ="#ffffff";
    gDraw_ctx.fillText(gTimer.value, gTimer.x, gTimer.y);
    
    // Draw replay button.
    var sprite = get_sprite("replay_button.png");
    drawSprite(sprite.id, (gCanvas_w - sprite.w), 0, gDraw_ctx, 0.5);
    
    // Draw lily pads. (before the frogs, otherwise, we could draw a lily pad
    // over a frog that is changing its position. In other words, the frog is
    // drawn before the lily pad.
    for ( i = 0; i < gFrogs_list.length; i++)
    {
        drawSprite("lily_pad.png", ((gFrog_x_start * i) + gFrog_x_offset), gFrog_y_start, gDraw_ctx);
    }
    
    for ( i = 0; i < gFrogs_list.length; i++)
    {
        var element = gFrogs_list[i];
        
        if (element.id === "empty")
        {
            continue;
        }
        var sprite_name = (element.leaping)? element.sprites.leaping[element.curr_sprite] : element.sprites.standing[element.curr_sprite];
        drawSprite(sprite_name, element.pos.x+gCenter_frogs_offset, element.pos.y+gCenter_frogs_offset, gDraw_ctx);
    }
}

// Check and handle victory condition.
function checkVictory()
{    
    for (var i = 0; i < gFrogs_list.length; i++)
    {
        var element = gFrogs_list[i];
        var expected = gExpected_frogs_array[i];
        
        console.log(element.id + " === " + expected + " ?");
        
        // Check if the expected frog type is in position.
        if (element.id.indexOf(expected) === -1)
        {
            return false;
        }
    }
    
    // All elements are in position.
    return true;
}

function showVictory()
{
    gCachedAssets["sounds/winning.mp3"].play();
    gDraw_ctx.font="60px Georgia";
    gDraw_ctx.fillStyle ="#3333ff";
    gDraw_ctx.fillText(gGame_win, (gCanvas_w / 2) - 100 , 150);
}

function showLost()
{
    gCachedAssets["sounds/frogs_enter.mp3"].play();
    gDraw_ctx.font="60px Georgia";
    gDraw_ctx.fillStyle ="#3333ff";
    gDraw_ctx.fillText(gGame_lost, (gCanvas_w / 2) - 100 , 150);
}

function handleButtonReplayPressed()
{
    gCachedAssets["sounds/frog.mp3"].play();
    removeAllElementCallback();
    
    if (gVictory_flag === true)
    {
        gTimer.value = 0;
        gVictory_flag = false;
    }
    showGamePlay();
}

function handleFrogClick(id)
{
    var empty_pos = getPosById("empty");
    var frog_pos = getPosById(id);
    
    console.log("Empty pos id: " + empty_pos + "; Frog pos id: " + frog_pos);
    
    if (checkMovementAllowed(id, frog_pos, empty_pos) !== true)
    {
        console.log("Movement not allowed.");
        return;
    }
    
    gCachedAssets["sounds/frog.mp3"].play();
    animateMovement(frog_pos, empty_pos);
}

function buildFrogArray()
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
        addElementCallback(frog.id,
                            frog.pos.x, frog.pos.y,
                            sprite.w, sprite.h,
                            handleFrogClick);
        
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
        addElementCallback(frog.id,
                            frog.pos.x, frog.pos.y,
                            sprite.w, sprite.h,
                            handleFrogClick);
        
        frogs_list.push(frog);
    }
    
    return frogs_list;
}

function getPosById(id)
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

function checkMovementAllowed(id, from, to)
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

function animateMovement(from, to, frame)
{
    var element = gFrogs_list[from];
    var destn = gFrogs_list[to];
    
    // Starting animation.
    if ( (frame == undefined) || (frame === 0) )
    {
        frame = 0;
        element.curr_sprite = 0;
        element.leaping = true;
        disableMouseClick();
        gStarting_pos.x = element.pos.x;
        gStarting_pos.y = element.pos.y;
        
        console.log("[1]Origin: " + gStarting_pos.x + "," + gStarting_pos.y + " " + element.id);
        console.log("[1]Destination: " + destn.pos.x + "," +  destn.pos.y + " " + destn.id);
    }
    
    var B = {x : gStarting_pos.x, y : gStarting_pos.y};
    var A = {x : destn.pos.x, y : destn.pos.y};
    
    var r = Math.round((B.x - A.x) / 2);
    
    var cx = A.x + r;
    var cy = A.y;
    var px = Math.round(cx + r * Math.cos(frame * Math.PI/180) );
    var py;
    
    if (element.id.indexOf(gGreen_frog_prefix) !== -1)
    {
        py = Math.round(cy + r * Math.sin(frame * Math.PI/180) );
    }
    else
    {
        py = Math.round(cy - r * Math.sin(frame * Math.PI/180) );
    }
    
    // Update frog.
    if (frame < 180)
    {
        element.pos.x = px;
        element.pos.y = py;
    }
    else
    {
        // If the angle step is to broad, the frog may land few pixels out of
        // the expected destination.
        element.pos.x = destn.pos.x;
        element.pos.y = destn.pos.y;
        
        element.curr_sprite = 0;
        element.leaping = false;
    
        var temp = gFrogs_list[to];
        gFrogs_list[to] = gFrogs_list[from];
        gFrogs_list[from] = temp;
        // WHAT OUT WHILE ASSIGNING OBJECTS!!
        // The code bellow will copy by reference (and mess everything).
        // gFrogs_list[from].pos = gStarting_pos
        gFrogs_list[from].pos.x = gStarting_pos.x;
        gFrogs_list[from].pos.y = gStarting_pos.y;
    
        updateElementCallback(gFrogs_list[from].id, gFrogs_list[from].pos.x, gFrogs_list[from].pos.y);
        updateElementCallback(gFrogs_list[to].id, gFrogs_list[to].pos.x, gFrogs_list[to].pos.y);
        
        updateGamePlay();
        enableMouseClick();
    
        if (checkVictory() === true)
        {
            console.log("Victory!");
            clearInterval(gTimer.id);
            showVictory();
            gVictory_flag = true;
        }
        
        return;
    }
    
    updateGamePlay();
    
    // Stop changing sprites.
    if (element.curr_sprite < (element.sprites.leaping.length -1))
    {
        element.curr_sprite++;
    }
    
    frame += 16;
    setTimeout(function() {
                animateMovement(from, to, frame);
                },
            gAnimation_delay);
}

//##############################################################################
// Main handling.
//
gElements_callbacks = {};
gMouse_click_enable = true;

function main()
{
    console.log("All code and media were loaded.");
    
    createCanvas();
    
    // User Interaction.
    gCanvas_obj.onclick = handleMouseClick;
    
    // Display main menu.
    showMainMenu();
}

// Bootstrap.
loadCoreAssets();

function enableMouseClick()
{
    gMouse_click_enable = true;
}

function disableMouseClick()
{
    gMouse_click_enable = false;
}

function handleMouseClick(e)
{
    if (gMouse_click_enable === false)
    {
        return;
    }
    
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

function addElementCallback(id, x, y, w, h, cb, data)
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

function removeAllElementCallback()
{
    gElements_callbacks = {};
}

function removeElementCallback(id)
{
    if (id in gElements_callbacks)
    {
        delete gElements_callbacks[id];
    }
}

function updateElementCallback(id, x, y)
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
function alignMiddle(obj1_px, obj1_w, obj2_w)
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