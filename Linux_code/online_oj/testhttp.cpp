#include <stdio.h>
#include "httplib.h"

using namespace httplib;


int main()
{
    Server svr;
    svr.Get("/",[](const Request& req,Response& resp)
            {
                (void)req;
                resp.set_content("<html>hello!</html>","123"); 
            });
    svr.listen("192.168.231.128",9090);
    return 0;
}
