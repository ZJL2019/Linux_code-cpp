#include "httplib.h"

#include "oj_model.hpp"
#include "oj_view.hpp"
#include "oj_log.hpp"

int main()
{
    using namespace httplib;
    Server svr;
    OjModel ojmodel;
    svr.Get("/all_questions",[&ojmodel](const Request& req,Response& resp){
            (void)req;

            std::vector<Topic> topic; //通过出参获取题目信息
            ojmodel.GetAllTpoic(&topic);

            std::string html;
            OJ_View::ExpandAllQuestionshtml(&html,topic);
            LOG(INFO,html)
            resp.set_content(html,"text/html;charset=UTF-8");
            });

    svr.Get(R"(/question/(\d+))",[&ojmodel](const Request& req,Response& resp){

            std::string desc;
            std::string header;
            std::string tmp;
            tmp+="req.mathches"+req.matches[0].str()+":"+req.matches[1].str();
            LOG(INFO,tmp)
            
            struct Topic topic; 
            ojmodel.GetOneTopic(req.matches[1].str(),&desc,&header,&topic);

            std::string html;
            OJ_View::ExpandOneQuestion(&html,topic,desc,header);
            LOG(INFO,html);
            
            resp.set_content(html,"text/html;charset=UTF-8");
            });
    LOG(INFO,"listen in 0.0.0.0:9090");
    LOG(INFO,"Server ready");
    svr.listen("0.0.0.0",9090);
    return 0;
}
