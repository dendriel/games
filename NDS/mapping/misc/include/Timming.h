/*
 * Timming.h
 *
 *  Created on: 01/10/2013
 *      Author: vitor
 */

#ifndef TIMMING_H_
#define TIMMING_H_

//!< Fake sleep. Stop using..
#define GSLEEP(_value){\
	unsigned int _r=_value;\
	while(_r--){\
		swiWaitForVBlank();\
	}\
}

/**
 * \brief Time operations.
 */
class Timming {
private:
	unsigned int m_Ticks;
public:
	/**
	 * \brief Class constructor.
	 */
	Timming(): m_Ticks(0) {}
	/**
	 * \brief Start a counter.
	 */
	void start(void);

	/**
	 * \brief Stop the counter.
	 * \return Ellapsed time.
	 */
	unsigned int  stop(void);

	/**
	 * \brief Reset the counter.
	 */
	void reset(void);

	/**
	 * \brief Wait x mili seconds.
	 */
	void wait(const unsigned int time_ms);

	/**
	 * \brief Must be called every interaction.
	 */
	void update(void);

	/**
	 * \brief Return elapsed time in seconds.
	 */
	unsigned int elapsed_seconds(void);

	/**
	 * \brief Return elapsed time in mili seconds.
	 */
	unsigned int elapsed_miliseconds(void);
};

#endif /* TIMMING_H_ */
