#include <stdio.h>
#include <string.h>
#include "collector.h"
#include "utils.h"
#include "log.h"

static char* ports="123";
static int RP_Local[num_X],RP[num_X];

void init()
{
    for (int i=0;i<num_X;i++) RP[i]=0;
}

FILE* send_order()
{  
	FILE* pipe; 
	char cmd[1024];   
	pipe = popen("sudo ovs-ofctl dump-flows s1 --name", "r");  
	if(NULL == pipe)  
	{
		printf("popen() failed: %s\n", cmd);  
		return 0;
	}
	return pipe;
}

void get_flow_data(char* s)
{
    char* output=strstr(s,"output:p");
    if (output!=NULL)
    {
        char* n_packets=strstr(s,"n_packets=");
   	    int num=0,i=10;
        while(n_packets[i]<='9'&&n_packets[i]>='0')
        {
			num=num*10+n_packets[i]-'0';
			i++;
		}
        for (int i=0;i<strlen(ports);i++)
            if (output[8]==ports[i])
                RP[i]+=num;
    }
}

void get_X(int X[])
{
	char cmd[1024];  
	char line[1024];

    FILE* pipe=send_order();
	while(fgets(line, sizeof(line),pipe) != NULL)  
	{  
		get_flow_data(line);
 		fflush(pipe); 
	}  
	pclose(pipe);

    for (int i=0;i<num_X;i++)
    {
        X[i]=RP[i]-RP_Local[i];
        RP_Local[i]=RP[i];
	//	printf("X[%d]=%d,RP_Local[%d]=%d\n",i,X[i],i,RP_Local[i]);
    }
	char s[20];
	LOG("RP_local[0]=");LOG(int2str(s,RP_Local[0]));LOG(",RP_local[1]=");LOG(int2str(s,RP_Local[1]));
	LOG(",RP_local[2]=");LOG(int2str(s,RP_Local[2]));LOG("\n");

	LOG("X[0]=");LOG(int2str(s,X[0]));LOG(",X[1]=");LOG(int2str(s,X[1]));
	LOG(",X[2]=");LOG(int2str(s,X[2]));LOG("\n");
}
