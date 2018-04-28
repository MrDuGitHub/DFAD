#include "log.h"
#include <stdio.h> 
#include <string.h>

void LOG(char* s)
{
	FILE* Log;
	if((Log=fopen("//home//mrd//桌面//log.txt","a+"))==NULL)
	{
		printf("不能打开日志文件!\n");
		return;
	}
	fseek(Log, 0, SEEK_END);
    fwrite(s,strlen(s),1,Log);
    fflush(Log);
	fclose(Log); 
}
