#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define num_X 3
static const int M=2,W=3,K=10,Lambda=3,interval=5;
static const double alpha=1.618;
static int RP_Local[num_X],RP[num_X];
static int times=0,initial_n=12;
static double E=0,Delta=0;
static char* ports="123";

struct Count {int k;int m;int w;};

char* int2str(char* s,int x)
{
	sprintf(s,"%d",x);
	return s;
}

char* double2str(char* s,double x)
{
	sprintf(s,"%f",x);
	return s;
}

void LOG(char* s)
{
	FILE* Log;
	if((Log=fopen("//home//mrd//桌面//log.txt","a+"))==NULL)
	{
		printf("不能打开日志文件\n");
		exit(0);
	}
	fseek(Log, 0, SEEK_END);
    fwrite(s,strlen(s),1,Log);
    fflush(Log);
	fclose(Log); 
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
	fgets(line, sizeof(line),pipe);
    for (int i=0;i<num_X;i++) RP[i]=0;
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

double get_H()
{
    int X[num_X],sum_X;
	double p[num_X],H;
    get_X(X);
    sum_X=0;
    for (int i=0;i<num_X;i++) sum_X+=X[i];
	if (sum_X==0) return H;
	H=0;
    for (int i=0;i<num_X;i++)
    {
        p[i]=X[i]/(double)sum_X;
        if (p[i]!=0)H+=-p[i]*log(p[i]);
    }
    H/=log(num_X);
	char s[20];
	LOG("H=");LOG(double2str(s,H));LOG("\n");
	return H;
}

void update_E(double H[],int k)
{
    double vari=0,a=1,sum;
	E=0;
    if (k<=K)
    {
        sum=(1-pow(alpha,k))/(1-alpha);
        for (int i=0;i<k;i++)
        {
            E+=a/sum*H[i];
            a*=alpha;
        }
		for (int i=0;i<k;i++)
			vari+=(H[i]-E)*(H[i]-E);
        vari=sqrt(vari/k);
        Delta=Lambda*vari;
    }
    else
    {
        sum=(1-pow(alpha,K))/(1-alpha);
        for (int i=0;i<K;i++)
        {
            int ri=(i+k-K)%K;
            E+=a/sum*H[ri];
            a*=alpha;
        }
		for (int i=0;i<K;i++)
        {
            int ri=(i+k-K)%K;
            vari+=(H[ri]-E)*(H[ri]-E);
        }
        vari=sqrt(vari/K);
        Delta=Lambda*vari;
    }
	char s[20];
	LOG("New Delta = ");LOG(double2str(s,Delta));LOG(" New E = ");LOG(double2str(s,E));LOG("\n");;

}

void work(double hk[],struct Count* c,char* s)
{
    double H=get_H();
    hk[c->k%K]=H;
    c->k++; if (c->k==2*K) c->k=K;
    if (initial_n)
    {
		LOG("Initial...\n");
        initial_n--;
        update_E(hk,c->k);
    }
    else
    {
        if (E-H>Delta)
        {
			char l[20];        
			if (c->w<W)
            {
                s[c->w]='1';
                c->m++;c->w++;
				LOG("E-H>Delta! ");LOG(int2str(l,c->m));LOG("/");LOG(int2str(l,W));LOG("\n");
            }
            else
            {
                if (s[0]=='0') c->m++;
				LOG("E-H>Delta! ");LOG(int2str(l,c->m));LOG("/");LOG(int2str(l,W));LOG("\n");
                for(int i=0;i<W;i++) s[i]=s[i+1];
                s[W-1]='1';
                if (c->m>=M) 
				{	
					LOG("\nDDos attack!\n");
				//	report();
				}
            }
            c->k--;
        }
        else
        {
            if (c->w<W){s[c->w]='0';c->w++;}
			else
			{
				if (s[0]=='1') c->m--;
				for(int i=0;i<W;i++) s[i]=s[i+1];
                s[W-1]='0';
			}
            update_E(hk,c->k);
        }
		LOG(s);LOG("\n");
    }
}

int main()
{
    double hk[K];
    char* s=(char*)malloc(sizeof(char)*K);
    
	struct Count* c;
	c->k=0;c->m=0;c->w=0;
    double H;
    for (int i=0;i<num_X;i++) RP_Local[i]=0;
    time_t timep,timen;
    time(&timep);
	timen=timep-interval;
    while(1)
    {
        if (timep-timen<interval)
       		sleep(1);
        else
		{
			LOG(asctime(gmtime(&timep)));
			work(hk,c,s);
			timen=timep;
		}
		time(&timep);
		fflush(stdout);    
	}
	return 0;
}
