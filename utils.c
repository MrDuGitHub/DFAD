#include "utils.h"
#include "stdio.h"

char* int2str(char* s,int x)
{
	sprintf(s,"%d",x);
	printf("%s\n",s);
	return s;
}

char* double2str(char* s,double x)
{
	sprintf(s,"%f",x);
	return s;
}
