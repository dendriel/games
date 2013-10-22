
//{{BLOCK(Layer_1)

//======================================================================
//
//	Layer_1, 256x256@8, 
//	Transparent color : FF,00,FF
//	+ regular map (flat), not compressed, 32x32 
//	External tile file: (null).
//	Total size: 2048 = 2048
//
//	Time-stamp: 2013-10-19, 14:42:33
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef SEWER_TILESET_H
#define SEWER_TILESET_H

#define sewer_width_tiles 8
#define sewer_height_tiles 8

extern const unsigned short sewer_tileset_map[1024];

extern const unsigned int sewer_tileset_collision_map[64];

//}}BLOCK(Layer_1)

//{{BLOCK(sewer_tilesetShared)

//======================================================================
//
//	sewer_tilesetShared, 8x2832@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 354 tiles not compressed
//	Total size: 512 + 22656 = 23168
//
//	Time-stamp: 2013-10-19, 14:42:33
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#define sewer_tilesetSharedTilesLen_bytes 24448
extern const unsigned int sewer_tilesetSharedTiles[6112];

#define sewer_tilesetSharedPalLen_bytes 512
extern const unsigned short sewer_tilesetSharedPal[256];


#endif // SEWER_TILESET_H

//}}BLOCK(sewer_tilesetShared)
