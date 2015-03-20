var TiledMapClass = Class.extend
({
    // JSON data.
    currMapData: null,

    // This is where we store the width and height of the map in tiles.
    numXTiles: 0,
    numYTiles: 0,

    // The size of each individual map tile, in pixels.
    tileSize: {
        "x": 0,
        "y": 0
    },

    // The size of the entire map, in pixels.
    pixelSize: {
        "x": 0,
        "y": 0
    },

    // tilesets stores each individual tileset from the map.json's 'tilesets' Array.
    // The structure of each entry of this Array is explained below in the
    // parseAtlasDefinition method.
    tilesets: [],

    // Counter to keep track of how many tile images we have successfully loaded.
    imgLoadCount: 0,

    // Boolean flag we set once our map atlas has finished loading.
    fullyLoaded: false,

    //-----------------------------------------
    // Load the json file at the url 'map' into memory. This is similar to the
    // requests we've done in the past using XMLHttpRequests.
    load: function (map_data)
    {
        this.parseMapJSON(map_data);
    },

    //---------------------------
    // Internal use.
    parseMapJSON: function (map_data)
    {
        this.currMapData = map_data;
        
        this.tileSize.x = this.currMapData.tilewidth;
        this.tileSize.y = this.currMapData.tileheight;
        this.numXTiles = this.currMapData.width;
        this.numYTiles = this.currMapData.height;
        this.pixelSize.x = this.currMapData.width * this.currMapData.tilewidth;
        this.pixelSize.y = this.currMapData.height * this.currMapData.tileheight;
        
        // Loop through 'map.tilesets', an Array, loading each of the provided
        // tilesets as Images. Increment the above 'imgLoadCount' field of
        // 'TILEDMap' as each tileset is loading. Once all the tilesets are
        // loaded, set the 'fullyLoaded' flag to true.
        for (var i = 0; i < this.currMapData.tilesets.length; i++)
        {
            var tileset = this.currMapData.tilesets[i];
            
            var img = new Image();
            img.onload = this.increaseCounter();
            img.src = tileset.image;
            
            // This is the javascript object we'll create for the 'tilesets'
            // Array above. First, fill in the given fields with the
            // corresponding fields from the 'tilesets' Array in 'currMapData'.
            var ts = {
                // All of these fields have incorrect dummy data currently! You
                // need to replace this with the correct data.
                "firstgid": tileset.firstgid,

                // 'image' should equal the Image object we
                // just created.

                "image": img,
                "imageheight": tileset.imageheight,
                "imagewidth": tileset.imagewidth,
                "name": tileset.image.replace(/^.*[\\\/]/, ''),

                // These next two fields are tricky. You'll need to calculate this data from the
                // width and height of the overall image and the size of each individual tile.
                // 
                // Remember: This should be an integer, so you might need to do a bit of manipulation after
                // you calculate it.
                "numXTiles": Math.floor(tileset.imagewidth / tileset.tilewidth),
                "numYTiles": Math.floor(tileset.imageheight / tileset.tileheight)
            };
            
            // After that, push the newly created object into the 'tilesets' Array above. Javascript Arrays
            // have a handy method called, appropriately, 'push' does exactly this. It takes the object
            this.tilesets.push(ts);
        }
        
    },
    
    increaseCounter: function()
    {
        this.imgLoadCount++;
        if (this.imgLoadCount === this.currMapData.tilesets.length)
        {
            this.fullyLoaded = true;
        }
    },
    
    //-----------------------------------------
    // Grabs a tile from our 'layer' data and returns the 'pkt' object for the layer we want to draw.
    // It takes as a parameter 'tileIndex', which is the id of the tile we'd like to draw in our
    // layer data.
    getTilePacket: function (tileIndex)
    {
        // We define a 'pkt' object that will contain
        // 
        // 1) The Image object of the given tile.
        // 2) The (x,y) values that we want to draw the tile to in map coordinates.
        var pkt = {
            "img": null,
            "px": 0,
            "py": 0
        };

        // The first thing we need to do is find the appropriate tileset that we
        // want to draw from.
        //
        // Remember, if the tileset's 'firstgid' parameter is less than the 'tileIndex'
        // of the tile we want to draw, then we know that tile is not in the given tileset and
        // we can skip to the next one.
        //
        var ts = null;
        for (var i = (this.tilesets.length - 1); i >= 0; i--)
        {
            if (this.tilesets[i].firstgid <= tileIndex)
            {
                ts = this.tilesets[i];
                break;
            }
        }
        
        if (ts == null)
        {
            return null;
        }

        // Next, we need to set the 'img' parameter in our 'pkt' object to the Image object
        // of the appropriate 'tileset' that we found above.
        //
        pkt.img = ts.image;
        
        // Finally, we need to calculate the position to draw to based on:
        //
        // 1) The local id of the tile, calculated from the 'tileIndex' of the
        // tile we want to draw and the 'firstgid' of the tileset we found earlier.
        //
        var local_id = tileIndex - ts.firstgid;


        // 2) The (x,y) position of the tile in terms of the number of tiles in
        // our tileset. This is based on the 'numXTiles' of the given tileset.
        // Note that 'numYTiles' isn't actually needed here. Think about how the
        // tiles are arranged if you don't see this, It's a little tricky. You
        // might want to use the modulo and division operators here.
        //
        // YOUR CODE HERE
        var lTileX = local_id % ts.numXTiles;
        var lTileY = Math.floor(local_id  / ts.numXTiles);

        // 3) the (x,y) pixel position in our tileset image of the tile we want
        // to draw. This is based on the tile position we just calculated and
        // the (x,y) size of each tile in pixels.
        //
        pkt.px = lTileX * this.tileSize.x;
        pkt.py = lTileY * this.tileSize.y;

        return pkt;
    },
    
    //-----------------------------------------
    // Draws all of the map data to the passed-in canvas context, 'ctx'.
    draw: function (ctx) {
        // First, we need to check if the map data has already finished loading.
        if(this.fullyLoaded !== true)
        {
            return;
        }

        // Now, for every single layer in the 'layers' Array of 'currMapData', we need to:
        // 
        // 1) Check if the 'type' of the layer is "tilelayer".
        //    If it isn't, we don't care about drawing it.
        //
        // 2) If it is a "tilelayer", we grab the 'data' Array
        //    of the given layer.
        //
        // 3) For each tile id in the 'data' Array, we need
        //    to:
        //    
        //    a) Check if the tile id is 0. An id of 0 means that
        //       we don't need to worry about drawing it, so we
        //       don't need to do anything further with it.
        //
        //    b) If the tile id is not 0, then we need to grab
        //       the packet data using 'getTilePacket' called
        //       on that tile id.
        //
        for (var i = 0; i < this.currMapData.layers.length; i++)
        {
            var layer = this.currMapData.layers[i];
            
            if (layer.type !== "tilelayer")
            {
                continue;
            }
            
            var data_arr = layer.data;
            
            for (var j = 0; j < data_arr.length; j++)
            {
                var tile = data_arr[j];
                if (tile === 0)
                {
                    continue;
                }
                
                var pkt = this.getTilePacket(tile);

                // Now we need to calculate the (x,y) position we want to draw
                // to in our game world.                
                var destx = (j % this.tileSize.x) * this.tileSize.x;
                var desty = (Math.floor(j  / this.tileSize.y)) * this.tileSize.y;
                
//                console.log("img: " + pkt.img + "; "+
//                        pkt.px + "," + pkt.py + "; "+
//                        this.tileSize.x + "," + this.tileSize.y + "; "+
//                        destx + "," + desty + "; "+
//                        this.tileSize.x + "," + this.tileSize.y);
                ctx.drawImage(
                        pkt.img,
                        pkt.px, pkt.py,
                        this.tileSize.x, this.tileSize.y,
                        destx, desty,
                        this.tileSize.x, this.tileSize.y);
            }
        }
    }

});

//var gMap = new TiledMapClass();
//gMap.load("js/map.json");
//
//var body = document.getElementById("body");
//var canvas = document.createElement("canvas");
//canvas.setAttribute('width', 6400);
//canvas.setAttribute('height', 6400);
//var drawctx = canvas.getContext("2d");
//drawctx.fillStyle = "#ff00ff";
//drawctx.fillRect(0,0,6400,6400);
////canvas.style.opacity = '0.2';
//
//body.appendChild(canvas);
//
//
//
//setTimeout(function()
//{
////console.log(gMap.currMapData);
////console.log(gMap.numXTiles + "," + gMap.numYTiles);
//console.log(gMap.tileSize.x + "," + gMap.tileSize.y);
//console.log(gMap.pixelSize.x + "," + gMap.pixelSize.y);
//gMap.draw(drawctx);
//}, 1000);
