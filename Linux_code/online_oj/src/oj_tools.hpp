#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "oj_log.hpp"
#define CHECK_RET(exp) if(!(exp)) {return false;}


class StringTools
{
    public:
        //提供字符串切割工具
        static void Split(std::string& input,const std::string& split_char,std::vector<std::string>* output)
        {
            boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);
        }
};


class FileOper
{
    public:
        static int ReadDateFromFile(const std::string& filename,std::string* content)
        {
            std::ifstream file(filename.c_str());
            if(!file.is_open())
            {
                std::string tmp;
                tmp+="Open file failed filename is "+filename;
                LOG(ERROR,tmp);
                return -1;
            }
            
            std::string line;
            while(std::getline(file,line))
            {
                *content+=line+"\n";
            }
            file.close();
            return 0;
        }
};
