/*
 * CollisionElement.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONELEMENT_H_
#define COLLISIONELEMENT_H_


typedef enum {
	INANIMATED = 0,
	ANIMATED
} en_collElement_type;

class CollisionElement {
private:
	const en_collElement_type m_Type;

public:
	CollisionElement(const en_collElement_type type = INANIMATED);
	inline en_collElement_type type(void);
};


#endif /* COLLISIONELEMENT_H_ */
