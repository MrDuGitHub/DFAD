#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "entropy.h"
#include "detection.h"
#include "collector.h"
#include "log.h"
#include "utils.h"

static int interval=5;

int run(int argc,char *argv[])
{
    if (parse_options(argc,argv))
    {
        printf("参数错误！\n");
        return 0;
    }
    loop();
    return 0;
}

int parse_options(int argc,char *argv[])
{
    if (argc==1) return 0;
    for (int i=1;i<argc;i++)
    {
        if (argv[i][0]!='-') return -1;		
        switch (argv[i][1])
        {
            int t0=0,t1=0;
            case 'm':
                i++;t0=str2int(argv[i]);
                if (!t0) return -1;
                i++;t1=str2int(argv[i]);
                if (!t1) return -1;
                if (t0>t1)return -1;
                set_value('m',t0,t1);
                break;
            case 'l':
                i++;t0=str2int(argv[i]);
                if (!t0) return -1;
                set_value('l',t0,t1);
                break;
            case 'i':
                i++;t0=str2int(argv[i]);
                if (!t0) return -1;
                set_value('i',t0,t1);
                break;
            case 't':
                i++;t0=str2int(argv[i]);
                if (!t0) return -1;
                interval=t0;
                break;
            case 's':
            case 'c':
                setMode(argv[i][1],argv[i+1]);i++;
                break;
        }
    }
    return 0;	
}

void loop()
{
    time_t timep,timen;
    time(&timep);
    timen=timep-interval;
    init_work();
    LOG("-----------------------------------------------\n");
    get_log(interval);
    for (int i=0;;)
    {
        if (timep-timen<interval)
            sleep(1);
        else
        {
            if (i==0) LOG("Start running...\n");
            else LOG("The Program has run %ds\n",interval*i);
            work();
            i++;
            timen=timep;
        }
        time(&timep);
        fflush(stdout);    
    }
}
