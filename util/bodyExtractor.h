#ifndef     _BODY_EXTRACTOR_H_
#define     _BODY_EXTRACTOR_H_

#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Array>
#include <Wt/Http/Request>

class   bodyExtractor {

    public:
        bodyExtractor(const Wt::Http::Request&     req)
        {
            int contentLength = req.contentLength();
            rawBody = new char[contentLength + 1];
            req.in().read(rawBody, contentLength);
            rawBody[contentLength] = 0;
        }

        char*   getRawBody()
        {
            return  rawBody;
        }

        // assigns the jsonObjBody and returns true or 
        // false if faild and sets the error property
        bool    turnIntoJsonObj()
        {
            return  Wt::Json::parse(rawBody, jsonObjBody, error, true);
        }
        
        Wt::Json::Object&    getJsonObjBody()
        {
            return  jsonObjBody;
        }

        Wt::Json::ParseError&    getError()
        {
            return  error;
        }

    private:
        char*   rawBody;
        Wt::Json::Object    jsonObjBody;
        Wt::Json::ParseError    error;

};

#endif
