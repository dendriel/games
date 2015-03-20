// Define core scripts that must be loaded first.
var core_scripts = [
    "js/core/Box2dWeb-2.1.a.3.min.js",
    "js/core/core.js"
];

var basic_assets = [
    // Scripts.
    "js/basic/Spritesheet.js",
    "js/basic/PhysicsEngine.js",
    "js/basic/InputEngine.js",
    "js/basic/GameEngine.js",
    "js/basic/Entity.js",
    "js/basic/TiledMap.js",
    
    // Images map.
    "json/grits_effects.json",
    // Images.
    "images/grits_effects.png"
];

var maps = [
    "json/map.json"
];

var entities = [
    "js/basic/Character.js",
    "js/entities/LandmineClass.js"
];


// Initial script loading.
function enter_point()
{
    load_core_assets();
}

function load_core_assets()
{
    loadAssets(core_scripts,
        function(assetsList)
        {
            console.log("Core assets were loaded. Initialize basic assets.");
            load_basic_assets();
        });
}

function load_basic_assets()
{
    loadAssets(basic_assets,
        function(assetsList)
        {
            console.log("Basic assets were loaded. Call load maps.");
            load_maps();
        });
}

function load_maps()
{
    loadAssets(maps,
        function(assetsList)
        {
            console.log("Maps were loaded. Call load entities.");
            load_entities();
        });
}

function load_entities()
{
    loadAssets(entities,
        function(assetsList)
        {
            console.log("Entities were loaded. Call load spritesheets.");
            load_spritesheets();
        });
}

function load_spritesheets()
{
    // Get only json files.
    var json_data = basic_assets.filter(function(element, index, array)
        {
            return (element.indexOf(".json") !== -1);
        });
    
    for (var i = 0; i < json_data.length; i++)
    {
        var asset = json_data[i];
        
        var sheet = new SpriteSheetClass();
        var sheet_asset = gCachedAssets[asset];
        sheet.parseAtlasDefinition(sheet_asset);
        
        var img_path = "images/" + sheet_asset.meta.image;
        var img_data = gCachedAssets[img_path];
        
        sheet.load(img_path, img_data);
    }
    
    main();
}

var FRAMERATE = 1000/60;

function main()
{
    
    
    var body = document.getElementById("body");
    var canvas = document.createElement("canvas");
    
    canvas.setAttribute('width', 1000);
    canvas.setAttribute('height', 1000);
    canvas.setAttribute('tabindex','0');
    canvas.focus();
    
    var drawctx = canvas.getContext("2d");
    drawctx.fillStyle = "#33ffff";
    drawctx.fillRect(0,0,500,700);
    //canvas.style.opacity = '0.2';
    
    body.appendChild(canvas);
    
    gInputEngine.setup(canvas);
    
    gGameEngine.setup(FRAMERATE, drawctx);
    gGameEngine.spawnEntity("Landmine", 200, 350);
    
    var player = gGameEngine.spawnEntity("Character", 150, 150);
    player.nick = "Dendriel";
    gGameEngine.loadPlayer(player);
}

// Start js logic.
enter_point();