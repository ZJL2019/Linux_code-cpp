#pragma once
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

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
