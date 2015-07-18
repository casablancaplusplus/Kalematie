#ifndef     _RESPONSE_GENERATOR_H_
#define     _RESPONSE_GENERATOR_H_

#include <Wt/Http/Response>
#include <Wt/Json/Object>
#include <Wt/Json/Serializer>


class   responseGenerator {

    public:
        responseGenerator(Wt::Json::Object&     jObj)
            : jResObj(jObj)
        {
        }
        
        void    putOut(Wt::Http::Response&   res)
        {
            res.setMimeType("application/json");
            std::string     resStr = Wt::Json::serialize(jResObj);
            res.out() << resStr << std::endl;
        }
    private:
        Wt::Json::Object    jResObj;

};

#endif
