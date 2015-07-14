#ifndef     _TOKEN_EXTRACTOR_H_
#define     _TOKEN_EXTRACTOR_H_

#include    <string>


class   tokenExtractor {

    public:
        tokenExtractor(std::string  str)
        {
            std::string::size_type  pos;
            if((pos=str.find("Bearer"))!=std::string::npos)
            {
                std::string     tokenStr="";
                std::string::iterator     it = str.begin();
                it = it + pos + 7;
                bool passed = false;
                for(std::string::iterator   It = it; It != str.end();
                        It++)
                {
                if(*It == ' ' && tokenStr != "") passed = true;
                if(passed && tokenStr != "") break;
                if(*It != ' ') tokenStr += *It;
                }
                token = tokenStr;

            }
            else if((pos=str.find("Basic"))!=std::string::npos)
            {
                std::string     tokenStr="";
                std::string::iterator     it = str.begin();
                it = it + pos + 6;
                bool passed = false;
                for(std::string::iterator   It = it; It != str.end();
                        It++)
                {
                if(*It == ' ' && tokenStr != "") passed = true;
                if(passed && tokenStr != "") break;
                if(*It != ' ') tokenStr += *It;
                }
                token = tokenStr;

            }
        }

        bool    empty() {
            if(token == "") return true;
            else return false;
        }

        std::string     getTokenStr()
        {
            return token;
        }

    private:
        std::string token = "";
};

#endif
