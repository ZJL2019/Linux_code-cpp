#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

#include "oj_log.hpp"
#include "oj_tools.hpp"
enum ErrorNo
{
    OK=0,
    COMPILE_ERROR,
    RUN_ERROR,
    PRAM_ERROR,
    INTERNAL_ERROR
};

class Compiler
{
    public:
        static void CompilerAndRun(Json::Value req,Json::Value* resp)
        {
            if(req["code"].empty())
            {
                LOG(ERROR,"Resqest code is empty!");
                return ;
            }

            std::string code=req["code"].asString();

            std::string tmp_filename=WriteTmpFile(code);
            if(tmp_filename=="")
            {
                (*resp)["erorno"]=INTERNAL_ERROR;
                (*resp)["reason"]="Create file failed!";
                LOG(ERROR,"Write source failed!");
                return ;
            }
            if(!Compile(tmp_filename))
            {
                (*resp)["errorno"]=COMPILE_ERROR;
                std::string reason;
                FileOper::ReadDateFromFile(ErrorPath(tmp_filename),&reason);
                (*resp)["reason"]=reason;
                LOG(ERROR,"Compile error!");
                return ;
            }
            int sig=Run(tmp_filename);
            if(sig!=0)
            {
                (*resp)["errorno"]=RUN_ERROR;
                (*resp)["reason"]="Program exit by signal "+std::to_string(sig);
                LOG(ERROR,"Run Error");
                return ;
            }
            (*resp)["errorno"]=OK;
            (*resp)["reason"]="Compile and run is okey!";
            std::string stdout_reason;
            FileOper::ReadDateFromFile(StdoutPath(tmp_filename),&stdout_reason);
            (*resp)["stdout"]=stdout_reason;
            
            std::string stderr_reason;
            FileOper::ReadDateFromFile(StderrPath(tmp_filename),&stderr_reason);
            (*resp)["stderr"]=stderr_reason;

            Clean(tmp_filename);
            return ;
        }

    private:
        static std::string WriteTmpFile(const std::string& code)
        {
            std::string tmp_filename="/tmp_"+std::to_string(LogTime::GetTimeStamp());
            int ret=FileOper::WriteDataToFile(SrcPath(tmp_filename),code);
            if(ret < 0)
            {
                LOG(ERROR,"Write code to source failed!");
                return "";
            }
            return tmp_filename;
        }

        static std::string SrcPath(const std::string& filename)
        {
            return  "./tmp_files"+filename+".cpp";
        }

        static std::string ErrorPath(const std::string& filename)
        {
            return  "./tmp_files"+filename+".err";
        }

        static std::string ExePath(const std::string& filename)
        {
            return  "./tmp_files"+filename+".exe";
        }

        static std::string StdoutPath(const std::string& filename)
        {
            return  "./tmp_files"+filename+".stdout";
        }

        static std::string StderrPath(const std::string& filename)
        {
            return  "./tmp_files"+filename+".stderr";
        }

        static bool Compile(const std::string& filename)
        {
            const int commandcount=20;
            char buf[commandcount][50]={{0}};
            char* Command[commandcount]={0};
            for(int i=0;i < commandcount;i++)
            {
                Command[i]=buf[i];
            }
            snprintf(Command[0],49,"%s","g++");
            snprintf(Command[1],49,"%s",SrcPath(filename).c_str());
            snprintf(Command[2],49,"%s","-o");
            snprintf(Command[3],49,"%s",ExePath(filename).c_str());
            snprintf(Command[4],49,"%s","-std=c++11");
            snprintf(Command[5],49,"%s","-D");
            snprintf(Command[6],49,"%s","CompileOnline");
            Command[7]=NULL;

            int pid=fork();
            if(pid < 0)
            {
                LOG(ERROR,"Create child process failed!");
                return false;
            }
            else if(pid==0)
            {
                int fd=open(ErrorPath(filename).c_str(),O_CREAT|O_RDWR,0644);
                if(fd < 0)
                {
                    std::string tmp="Open error file failed is "+ErrorPath(filename);
                    LOG(ERROR,tmp);
                }
                dup2(fd,2);
                execvp(Command[0],Command);
                exit(0);
            }
            else
            {
                waitpid(pid,NULL,0);
            }
            return true;
        }

        static int Run(const std::string& filename)
        {
            int pid=fork();
            if(pid < 0)
            {
                LOG(ERROR,"Exec pragma failed! Create child process failed!");
                return -1;
            }
            else if (pid==0)
            {
                alarm(1);
                struct rlimit rl;
                rl.rlim_cur=1024*30000;
                rl.rlim_max=RLIM_INFINITY;
                setrlimit(RLIMIT_AS,&rl);
                int stdout_fd=open(StdoutPath(filename).c_str(),O_CREAT|O_RDWR,0664);
                if(stdout_fd < 0)
                {
                    std::string tmp="Open stdout file failed "+StdoutPath(filename);
                    LOG(ERROR,tmp);
                    return -1;
                }
                dup2(stdout_fd,1);
                
                int stderr_fd=open(StderrPath(filename).c_str(),O_CREAT|O_RDWR,0664);
                if(stderr_fd < 0)
                {
                    std::string tmp="Open stderr file failed "+StderrPath(filename);
                    LOG(ERROR,tmp);
                    return -1;
                }
                dup2(stderr_fd,2);
                
                execl(ExePath(filename).c_str(),ExePath(filename).c_str(),NULL);
                exit(1);

            }
            int Status=-1;
            waitpid(pid,&Status,0);
            return Status & 0X7f;
        }

        static void Clean(std::string filename)
        {
            unlink(SrcPath(filename).c_str());
            unlink(ExePath(filename).c_str());
            unlink(ErrorPath(filename).c_str());
            unlink(StdoutPath(filename).c_str());
            unlink(StderrPath(filename).c_str());
        }
};
