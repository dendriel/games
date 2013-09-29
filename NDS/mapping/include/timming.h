#ifndef TIMMING_H_
#define TIMMING_H_

#define GSLEEP(_value){\
	unsigned int _r=_value;\
	while(_r--){\
		swiWaitForVBlank();\
	}\
}

#endif /*TIMMING_H_*/
