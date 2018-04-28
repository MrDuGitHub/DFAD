#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "entropy.h"
#include "detection.h"
#include "log.h"

static const int interval=5;

int main()
{
	loop();
	return 0;
}

void loop()
{
	time_t timep,timen;
    time(&timep);
	timen=timep-interval;
	init_work();
    while(1)
    {
        if (timep-timen<interval)
       		sleep(1);
        else
		{
			LOG(asctime(gmtime(&timep)));
			work();
			timen=timep;
		}
		time(&timep);
		fflush(stdout);    
	}
}
