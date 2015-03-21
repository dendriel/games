FrogGreenClass = FrogClass.extend(
{
    init : function()
    {
        this.sprites.standing.push("frog_green_standing_0000.png",
                                    "frog_green_standing_0001.png",
                                    "frog_green_standing_0002.png");
                                    
        this.sprites.leaping.push("frog_green_leaping_0000.png",
                                    "frog_green_leaping_0001.png",
                                    "frog_green_leaping_0002.png",
                                    "frog_green_leaping_0003.png");
                                    
        console.log("Green frog constructor.");
    }

});