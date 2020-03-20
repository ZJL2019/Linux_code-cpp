#include "httplib.h"

#include "oj_model.hpp"

int main()
{
    using namespace httplib;
    Server svr;
    OjModel ojmodel;
    svr.Get("/all_questions",[&ojmodel](const Request& req,Response& resp){
            std::vector<Topic> topic; //通过出参获取题目信息
            ojmodel.GetAllTpoic(&topic);
            resp.set_content("","text/html");
            });
    svr.listen("0.0.0.0",9090);
    return 0;
}
