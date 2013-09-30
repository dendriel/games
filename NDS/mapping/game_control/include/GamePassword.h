/*
 * GamePassword.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEPASSWORD_H_
#define GAMEPASSWORD_H_


//TODO

/**
 * \brief Manage password to levels.
 */
class GamePassword {

public:
	/**
	 * \brief Get and validate user password.
	 * \return The matching level from the password or -1 if the password is invalid.
	 */
	int get_levelByPassword(void);

};


#endif /* GAMEPASSWORD_H_ */
