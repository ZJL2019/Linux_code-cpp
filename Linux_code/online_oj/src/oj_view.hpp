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

};
