var gCachedAssets = {};

function loadAsset(assetName, callbackFcn)
{
    // If asset is already loaded.
    if ( (assetName in gCachedAssets) === true)
    {
        callbackFcn(gCachedAssets.assetName);
        return;
    }

    var img = new Image();
    img.onload = function ()
    {
        callbackFcn(assetName);
    };
    img.src = assetName;
    gCachedAssets[assetName] = img;
}

function loadAssets(assetsList, callbackFcn)
{
    var batch = {
        loaded : 0,
        total : assetsList.length,
        cb : callbackFcn
    };
    
    for (var i = 0; i < assetsList.length; i++)
    {
        var asset = assetsList[i];
        
        if ( (asset in gCachedAssets) === true)
        {
            batch.loaded++;
            continue;
        }
        
        var file_type = getAssetTypeFromExtension(asset);
        // Handle image files.
        if (file_type === 0)
        {
            var img = new Image();
            img.onload = function () {onLoadedAssetCb(assetsList, batch);};
            img.src = asset;
            gCachedAssets[asset] = img;
        }
        // Handle javascript files.
        else if (file_type === 1)
        {
            var new_js = document.createElement("script");
            
            new_js.setAttribute('type', "text/javascript");
            new_js.onload = function () {onLoadedAssetCb(assetsList, batch);};
            new_js.src = asset;
            
            var tags_list = document.getElementsByTagName('head');
            tags_list[0].appendChild(new_js);
        }
        // Handle json files.
        else if (file_type === 2)
        {
            gCachedAssets[asset] = null;
            $.getJSON(asset, function(response)
            {
                var json_name = "json/" + response.meta.image.substr(0, response.meta.image.lastIndexOf(".")) + ".json";
                gCachedAssets[json_name] = response;
                console.log("New json loaded \"" + json_name + "\"");
                onLoadedAssetCb(assetsList, batch);
            });
        }
        else
        {
            console.log("Received unhandled file type " + file_type);
        }
    
    }
}

function onLoadedAssetCb(assetsList, batch, data)
{
    batch.loaded++;
    
    if (batch.total === batch.loaded)
    {
        batch.cb(assetsList);
    }
}

// We've provided you a handy function for determining the asset type from the file extension.
// Images return 0, javascript returns 1, and everything else returns -1.
function getAssetTypeFromExtension(fname)
{
    if (fname.indexOf('.jpg') !== -1 ||
        fname.indexOf('.jpeg') !== -1 ||
        fname.indexOf('.png') !== -1 ||
        fname.indexOf('.gif') !== -1 ||
        fname.indexOf('.wp') !== -1)
    {
        return 0;
    }
    
    // This first. Otherwise, looking for indexOf ".js" will return 1 for both
    // json an js.
    if (fname.indexOf('.json') !== -1)
    {
        return 2;
    }
    
    if (fname.indexOf('.js') !== -1)
    {
        return 1;
    }

    return -1;
}
//
//var loadCb = function load_cb(asset)
//{
//    console.log("Asset \"" + asset + "\" were loaded!");
//    var ent = new EntityClass(10, 20);
//    console.log(ent.x + " " + ent.y);
//};
//
//var key = "here";
//console.log(key in gCachedAssets);
//
////loadAssets(["image/slime.png"], load_cb);
//
//loadAssets(["image/slime.png", "js/Entity.js"], loadCb);
//
//console.log("image/slime.png" in gCachedAssets);