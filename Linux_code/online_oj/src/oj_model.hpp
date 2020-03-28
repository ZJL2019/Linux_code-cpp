#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_map>

#include <algorithm>

#include "oj_tools.hpp"
#include "oj_log.hpp"
typedef struct Topic  //组织题目结构
{
    std::string id_;
    std::string name_;
    std::string path_;
    std::string star_;
}TOPIC;

class OjModel
{
    public:
        OjModel()
        {
            if(!LoadTopic("./config_oj.cfg"))
            {
                LOG(ERROR,"Loading failed!");
            }
        }

        bool GetAllTpoic(std::vector<Topic>* topic) //获取题目信息
        {
            for(const auto& kv:model_map_)
            {
                topic->push_back(kv.second);
            }
            //排序哈希查询结果
            std::sort(topic->begin(),topic->end(),[](const Topic& left,const Topic& right){ 
                    return std::stoi(left.id_) < std::stoi(right.id_);
                    }); 
            return true;
        }
        
        bool GetOneTopic(const std::string& id,std::string* desc,std::string* header,Topic* topic)
        {
            auto iter=model_map_.find(id);
            if(iter==model_map_.end())
            {
                std::string tmp;
                tmp+="Not found topic id is"+id;
                LOG(ERROR,tmp);
                return false;
            }
            *topic=iter->second;

            int ret=FileOper::ReadDateFromFile(DescPath(iter->second.path_),desc);
            if(ret==-1)
            {
                LOG(ERROR,"Read desc failed");
                return false;
            }

            ret=FileOper::ReadDateFromFile(HeaderPath(iter->second.path_),header);
            if(ret==-1)
            {
                LOG(ERROR,"Read header failed");
                return false;
            }
            return true;
        }

    private:
       bool LoadTopic(const std::string& configfile_path) //加载题目文件内容
       {
           std::ifstream file(configfile_path.c_str());
           if(!file.is_open())
           {
               std::string tmp;
               tmp+="Loading open failed topic_path is"+configfile_path;
               LOG(ERROR,tmp);
           }
           std::string line;
           while(std::getline(file,line))
           {
               std::vector<std::string> vec;
               StringTools::Split(line," ",&vec); //切割题目内容信息
               if(vec.size()!=4)
               {
                   continue;
               }

               Topic pic;
               pic.id_=vec[0];
               pic.name_=vec[1];
               pic.path_=vec[2];
               pic.star_=vec[3];
               model_map_[pic.id_]=pic;
           }
           file.close();
           return true;
       }
       
       std::string DescPath(const std::string& ques_path)
       {
           return ques_path+"desc.txt";
       }

       std::string HeaderPath(const std::string& ques_path)
       {
           return ques_path+"header.cpp";
       }

    private:
        std::unordered_map<std::string,Topic> model_map_;
};
