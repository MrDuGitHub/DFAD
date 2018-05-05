#include <stdio.h>
#include <string.h>
#include "collector.h"
#include "utils.h"
#include "log.h"

static char* ports="123";
static int RP_Local[num_X],RP[num_X];
static Mode MODE=Switch;

void init()
{
    for (int i=0;i<num_X;i++) RP[i]=0;
}

FILE* send_order()
{  
    FILE* pipe; 
    char cmd[1024];   
    char line[1024];
    switch (MODE)
    {
        case Switch:
            pipe = popen("sudo ovs-ofctl dump-flows s1 --name", "r");  
            if(NULL == pipe)  
            {
	            printf("popen() failed: %s\n", cmd);  
	            return 0;
            }
            break;  
        case Controller:
            pipe = popen("curl -X GET http://127.0.0.1:8080/stats/switches -s", "r");  
            if(NULL == pipe)
            {
                printf("popen() failed: %s\n", cmd);  
                return 0;
            }
            strcpy(cmd,"curl -X GET http://127.0.0.1:8080/stats/flow/");
            char s1[20];
            while(fgets(line, sizeof(line),pipe) != NULL)  
            {  
                int l=strchr(line,',')-line;
                l=strlen(line)-l-3;
                strcat(cmd,strncpy(s1,strchr(line,',')+2,l));
                fflush(pipe); 
            }
            strcat(cmd," -s");
           // printf("%s\n",cmd);
            pipe = popen(cmd,"r");
            if(NULL == pipe)
            {
                printf("popen() failed: %s\n", cmd);  
                return 0;
            }
            break;
    }    
    return pipe;
}

void get_flow_data(char* s)
{
    char* output,*n_packets;
    switch (MODE)
    {
        case Switch:
            output=strstr(s,"output:p");
            if (output!=NULL)
            {
                n_packets=strstr(s,"n_packets=");
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
            break;
        case Controller:
            output=strstr(s,"OUTPUT:");
            while (output!=NULL)
            {
                n_packets=strstr(output,"packet_count");
                if (n_packets==NULL) break;
                int num=0,i=15;
                while(n_packets[i]<='9'&&n_packets[i]>='0')
                {
                    num=num*10+n_packets[i]-'0';
                    i++;
               	}
                for (int i=0;i<strlen(ports);i++)
                    if (output[8]==('0'+i))
                    {    RP[i]+=num;}
                s=n_packets;
                output=strstr(s,"OUTPUT:");
            }
            break;
    }
}

void get_X(int X[])
{
    char cmd[1024];  
    char line[4096];
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
    	//printf("X[%d]=%d,RP_Local[%d]=%d\n",i,X[i],i,RP_Local[i]);
    	LOG("X[%d]=%d,RP_Local[%d]=%d\n",i,X[i],i,RP_Local[i]);
    }
}

void setMode(char c)
{
    if (c=='s') MODE=Switch;
    if (c=='c') MODE=Controller; 
    //printf("%d\n",MODE); 
}
