#pragma once
#include <ctemplate/template.h>
#include "oj_model.hpp"

class OJ_View
{
    public:
        static void ExpandAllQuestionshtml(std::string* html,std::vector<Topic>& topic)
        {
            ctemplate::TemplateDictionary dict("all_questions");
            for(const auto& tpc:topic)
            {
                ctemplate::TemplateDictionary* section_dict=dict.AddSectionDictionary("question");
                section_dict->SetValue("id",tpc.id_);
                section_dict->SetValue("id",tpc.id_);
                section_dict->SetValue("name",tpc.name_);
                section_dict->SetValue("star",tpc.star_);
            }
            ctemplate::Template* tl=ctemplate::Template::GetTemplate("../src/html_template/all_questions.html",ctemplate::DO_NOT_STRIP);
            tl->Expand(html,&dict);
        }
        
        static void ExpandOneQuestion(std::string* html,const Topic& topic,std::string& desc,std::string& header)
        {
            ctemplate::TemplateDictionary dict("question");
            dict.SetValue("id",topic.id_);
            dict.SetValue("name",topic.name_);
            dict.SetValue("star",topic.star_);
            dict.SetValue("desc",desc);
            dict.SetValue("header",header);
            ctemplate::Template* tpl=ctemplate::Template::GetTemplate("../src/html_template/question.html",ctemplate::DO_NOT_STRIP);
            tpl->Expand(html,&dict);
        }

        static void ExpandReason(const std::string& errorno,const std::string& reason,const std::string&stdout_reason,const std::string& stderr_reason,std::string* html)
        {
            ctemplate::TemplateDictionary dict("reason");
            dict.SetValue("errorno",errorno); 
            dict.SetValue("reason",reason);
            dict.SetValue("stdout",stdout_reason);
            dict.SetValue("stderr",stderr_reason);
            
            ctemplate::Template* tpl=ctemplate::Template::GetTemplate("../src/html_template/reason.html",ctemplate::DO_NOT_STRIP);
            tpl->Expand(html,&dict);
        }
};
