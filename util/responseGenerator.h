#ifndef     _RESPONSE_GENERATOR_H_
#define     _RESPONSE_GENERATOR_H_

#include <Wt/Http/Response>
#include <Wt/Json/Object>
#include <Wt/Json/Serializer>


class   responseGenerator {

    public:
        responseGenerator(){}
        responseGenerator(Wt::Json::Object&     jObj)
            : jResObj(jObj)
        {
        }
       
        // if you want the out put to be a default empty response which means success, provide the 
        // second argument a true value
        void    putOut(Wt::Http::Response&   res, bool  emptyRes = false)
        {
            res.addHeader("Access-Control-Allow-Origin","*");
            res.addHeader("Access-Control-Allow-Headers","Content-Type, Authorization");
            res.setMimeType("application/json");
            if(emptyRes)
            {
                std::ostream&   out = res.out();
                out << "{" << std::endl;
                out << "    \"errorMessage\":\"\"," << std::endl;
                out << "    \"errorCode\":0," << std::endl;
                out << "    \"responseData\":\"\"" << std::endl;
                out << "}" << std::endl;

            }
            else
            {
                std::string     resStr = Wt::Json::serialize(jResObj);
                res.out() << resStr << std::endl;
            }
        }
    private:
        Wt::Json::Object    jResObj;

};

#endif
