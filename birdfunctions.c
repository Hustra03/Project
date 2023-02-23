#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

void init(void)
{

    TRISE &= ~0xff;
	TRISD |= 0xFE0;

}