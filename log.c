#include "log.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>

int LOG(const char *format, ...)
{
    va_list arg;  
    int done;    
    va_start (arg, format);  
    FILE* Log=get_file();
    struct timeval tv;  
    struct tm * time_ptr;  
    memset(&tv, 0, sizeof(tv));  
    gettimeofday(&tv, NULL);  
    time_ptr = localtime(&tv.tv_sec);  
    fprintf(Log,"[%d-%02d-%02d %02d:%02d:%02d.%.04ld] ",  
            time_ptr->tm_year + 1900,  
            time_ptr->tm_mon + 1,  
            time_ptr->tm_mday,  
            time_ptr->tm_hour,  
            time_ptr->tm_min,  
            time_ptr->tm_sec,  
            tv.tv_usec/1000);  

    done = vfprintf (Log, format, arg);  	
    va_end (arg);  
    fflush(Log);  
    fclose(Log);
    return done;
}

FILE* get_file()
{
    FILE* Log;
    if((Log=fopen("..//log.txt","a+"))==NULL)
    {
        printf("不能打开日志文件!\n");
        return NULL;
    }
    fseek(Log, 0, SEEK_END);
    return Log;
}
