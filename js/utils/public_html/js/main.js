// Define core scripts that must be loaded first.
var core_scripts = [
    "js/core/core.js"
];

var basic_assets = [
    // Scripts.
    "js/basic/Spritesheet.js",
    // Images map.
    "json/grits_effects.json",
    // Images.
    "images/grits_effects.png"
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
            console.log("Basic assets were loaded. Call main.");
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

function main()
{
    var body = document.getElementById("body");
    var canvas = document.createElement("canvas");
    
    canvas.setAttribute('width', 500);
    canvas.setAttribute('height', 500);
    
    var drawctx = canvas.getContext("2d");
    drawctx.fillStyle = "#ff00ff";
    drawctx.fillRect(0,0,500,700);
    //canvas.style.opacity = '0.2';
    
    body.appendChild(canvas);
    
    drawSprite("rocket_launcher_muzzle_0005.png", 100, 100, drawctx);
}

// Start js logic.
enter_point();