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
            ctemplate::Template* tl=ctemplate::Template::GetTemplate("./html_template/all_questions.html",ctemplate::DO_NOT_STRIP);
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
            ctemplate::Template* tpl=ctemplate::Template::GetTemplate("./html_template/question.html",ctemplate::DO_NOT_STRIP);
            tpl->Expand(html,&dict);
        }
};
