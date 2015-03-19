// Define core scripts that must be loaded first.
var core_scripts = [
    "js/core/core.js"
];

var basic_assets = [
    // Scripts.
    "js/basic/Spritesheet.js",
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
            main();
        });
}

function load_spritesheets()
{
    
}

function main()
{
}

// Start js logic.
enter_point();