#pragma once
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "oj_tools.hpp"
class LogTime
{
    public:
    static int64_t GetTimeStamp()
    {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return tv.tv_sec;
    }
    
    static void GetTimeStamp(std::string* TimeStamp)
    {
        time_t SysTime;
        time(&SysTime);
        struct tm* st=localtime(&SysTime);
        char buf[30]={'\0'};
        snprintf(buf,sizeof(buf)-1,"%04d-%02d-%02d %02d:%02d:%02d",
                st->tm_year+1900,st->tm_mon+1,st->tm_mday,st->tm_hour,st->tm_min,st->tm_sec);
        TimeStamp->assign(buf,strlen(buf));
    }
};

const char* Level[]
{
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
    "DEBUG"
};

enum LogLevel
{
    INFO=0,
    WARNING,
    ERROR,
    FATAL,
    DEBUG
};

inline void Log(LogLevel lev,const char* file,int line,const std::string& logmsg)
{

    std::string level_info=Level[lev];
    std::string TimeStamp;
    std::ofstream log_file;
    LogTime::GetTimeStamp(&TimeStamp);
    log_file.open("./logfile.log",std::ios::app);
    if(!log_file.is_open())
    {
        log_file<<"["<<TimeStamp<<" "<<Level[2]<<" "<<"log_file open fault!"<<std::endl;
        return ;
    }
    log_file<<"["<<TimeStamp<<" "<<level_info<<" "<<file<<":"<<line<<"]"<<std::endl<<logmsg<<std::endl;
    log_file<<"--------------------------------------------------------"<<std::endl;
    log_file.close();
}

#define LOG(lev,msg) Log(lev,__FILE__,__LINE__,msg);

