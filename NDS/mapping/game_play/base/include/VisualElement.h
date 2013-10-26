/*
 * GameCharacter.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef VISUALELEMENT_H_
#define VISUALELEMENT_H_

#include <nds.h>

#include "util.h"

/* Definitions. */
#define SPRITE_LENGHT_BYTES 32*32
#define SPRITE_POSITIONS 128
#define SPRITE_PIVOT_INDEX 0

//!< Facility. Enumerate sprite positions.
typedef enum sprite_character_positions {
	SPRITE_FACING_NORTH_STEP_RIGHT = 0,
	SPRITE_FACING_NORTH_STOPPED,
	SPRITE_FACING_NORTH_STEP_LEFT,
	SPRITE_FACING_EAST_STEP_RIGHT,
	SPRITE_FACING_EAST_STOPPED,
	SPRITE_FACING_EAST_STEP_LEFT,
	SPRITE_FACING_SOUTH_STEP_RIGHT,
	SPRITE_FACING_SOUTH_STOPPED,
	SPRITE_FACING_SOUTH_STEP_LEFT,
	SPRITE_FACING_WEST_STEP_RIGHT,
	SPRITE_FACING_WEST_STOPPED,
	SPRITE_FACING_WEST_STEP_LEFT,
	SPRITE_FACING_NONE = 0//!< Control purpose.
} sprite_character_positions;


/* Structures */
//!< Represent the possible sprite positions to be used.
typedef struct {
	bool in_use;
	u16 *mem_addr;
	u8 *charset_data;
	st_offset *offset;			//!< Relative position.
	bool hide;
} st_sprite;

/**
 * \brief Game character class.
 */
class VisualElement {
private:
	int m_SpritePosition;		//!< Allocated sprite position.
	static st_sprite s_SpritePositions[SPRITE_POSITIONS];	//!< Controls the sprite memory occupation.
	/**
	 * The first slot is the pivot slot. The oam memory region will be moving according to it. The others sprites
	 * will be given an offset relative to the pivot (that should be the main character).
	 */
	static st_offset *s_PivotOffset_8px;

public:

	/**
	 * \brief Class constructor.
	 */
	VisualElement(st_offset *offset, u8* charset = 0, bool display=true);

	/**
	 * \brief Class destructor.
	 */
	~VisualElement(void);

	void update_sprite(const unsigned int offset_bytes=0);

	void update_position(void);

	bool alloc_SpriteData(int *sprite_position, u8 *charset, st_offset *offset, bool display);

	void free_SpriteData(const int sprite_position);

	/**
	 * \brief Set visual element visibility.
	 * \parameter display Display (true) or not (false) the element in the screen.
	 */
	inline void set_Display(const bool display)
	{
		st_sprite& sprite = s_SpritePositions[m_SpritePosition];
		sprite.hide = !display;
		/* Update right after so won't be needed to wait the character moving around to update the
		 * sprite.
		 */
		update_sprite();
	}

/*************************************************************************************************/
/* Static Functions                                                                              */
/*************************************************************************************************/

public:
	/**
	 * \brief Allocate memory for sprite. Must be called during initialization.
	 */
	static void init_SpritePositions(void)
	{
		for (unsigned int i = 0; i < SPRITE_POSITIONS; ++i) {
			VisualElement::s_SpritePositions[i].mem_addr =  oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			VisualElement::s_SpritePositions[i].in_use = false;
			VisualElement::s_SpritePositions[i].hide = false;
		}
	}

	static void set_PivotOffset(st_offset *offset_8px)
	{
		VisualElement::s_PivotOffset_8px = offset_8px;
	}
};

#endif /* VISUALELEMENT_H_ */
