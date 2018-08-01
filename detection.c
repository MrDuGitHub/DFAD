#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "detection.h"
#include "collector.h"
#include "log.h"
#include "utils.h"

#define K 10

static const double alpha=1.618;
static int M=2,W=3,Lambda=3;

static int times=0,initial_n=10;
static double E=0,Delta=0;
static double hk[K];
static struct Count t,*c;
static char* s0;

void init_work()
{
    c=&t;
    c->k=0;c->m=0;c->w=0;	
    s0=(char*)malloc(sizeof(char)*W);
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
    int tx=num_X;
    for (int i=0;i<num_X;i++)
    {
        if (X[i]<=5) tx--;
        p[i]=X[i]/(double)sum_X;
        if (p[i]!=0)H+=-p[i]*log(p[i]);
	//printf("%f ",H);
    }
    H/=log(tx);
    //printf("%f \n",H);	
    char s[20];
    LOG("%s%s\n","H=",double2str(s,H));
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
    char s[20],s1[20];
    LOG("%s%s%s%s\n","Update: New Delta = ",double2str(s,Delta)," New E = ",double2str(s1,E));
}

void work()
{
    double H;
    init();
    H=get_H();
    hk[c->k%K]=H;
    c->k++; 
    if (c->k==2*K) c->k=K;
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
                s0[c->w]='1';
                c->m++;c->w++;
                LOG("%s%s%s%s\n","E-H>Delta! ",int2str(l,c->m),"/",int2str(l,W));			
            }
            else
            {
                if (s0[0]=='0') c->m++;
                LOG("%s%s%s%s\n","E-H>Delta! ",int2str(l,c->m),"/",int2str(l,W));			
                for(int i=0;i<W;i++) s0[i]=s0[i+1];
                s0[W-1]='1';
                if (c->m>=M) 
                {	
                    LOG("DDos attack!\n");
                //	report();
                }
            }
            c->k--;
        }
        else
        {
            if (c->w<W){s0[c->w]='0';c->w++;}
            else
            {
                if (s0[0]=='1') c->m--;
                for(int i=0;i<W;i++) s0[i]=s0[i+1];
                s0[W-1]='0';
            }
            update_E(hk,c->k);
        }
        LOG("%s%s\n","Recently : ",s0);
    }
}

void set_value(char x,int v0,int v1)
{
    switch (x)
    {
        case 'm': M=v0; W=v1;  break;
        case 'l': Lambda=v0;   break;
        case 'i': initial_n=v0;break;
    }
}

void get_log(int interval)
{
    LOG("interval=%d,M=%d,W=%d,Lambda=%d,initial_n=%d\n",interval,M,W,Lambda,initial_n);
}

