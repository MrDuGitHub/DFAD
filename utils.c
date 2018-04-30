#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int str2int(char* s)
{
	int v=0,i=0;
	while (s[i]!='\0')
	{
		if (s[i]<'0'||s[i]>'9')return 0;
		v=v*10+s[i]-'0';
		i++;	
	}
	return v;
}

char* join(char* s1,char* s2)
{
    char *c = (char*) malloc(strlen(s1) + strlen(s2) + 1);
    if (c == NULL) exit (1);    
    char *tempc = c;  
    while (*s1 != '\0') *c++ = *s1++;      
    while ((*c++ = *s2++)!='\0');  
    return tempc; 
}
