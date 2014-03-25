
#include "fn_time.h"

void pause(double timeDiff)
{
	if (timeDiff<0)
		timeDiff=0.0;
	usleep((int) (timeDiff*1000000));
}
