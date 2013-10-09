//======================================================================
//
//	mytiles, 256x96@8,
//	Transparent color : FF,00,FF
//	+ regular map (flat), not compressed, 32x12
//	External tile file: (null).
//	Total size: 768 = 768
//
//	Time-stamp: 2013-09-17, 21:44:07
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef MYTILES_TILESET_H
#define MYTILES_TILESET_H

#define mytiles_width_tiles 8
#define mytiles_height_tiles 3

extern const unsigned short mytiles_map[384];

extern const unsigned int mytiles_collision_map[24];

//{{BLOCK(mytilesShared)

//======================================================================
//
//	mytilesShared, 8x624@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 78 tiles not compressed
//	Total size: 512 + 4992 = 5504
//
//	Time-stamp: 2013-09-17, 21:44:07
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#define mytiles_sharedTilesLen_bytes 4992
extern const unsigned int mytiles_sharedTiles[1248];

#define mytiles_sharedPalLen_bytes 512
extern const unsigned short mytiles_sharedPal[256];

#endif /* MYTILES_TILESET_H */
