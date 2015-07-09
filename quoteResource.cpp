

#include "quoteResource.h"


quoteResource::quoteResource() {}

void    quoteResource::handleRequest(   const Wt::Http::Request&    request,
                                        Wt::Http::Response&         response)
{
    
   if(request.headerValue("Authorization") == "")
    {
        // Not implemented yet
        error   headerError("No Authorization header was provided",20000);
        headerError.putOut(response);
    }
   else {

       _request = request;
       _response = response;

        // authenticate not implemented yet
        if(authenticate()) {
            
            std::string     _url = request.pathInfo();
            //check the request method
            if(request.method() == "GET")
            {
                initiateGet();
            }
            else if (request.method() == "POST")
            {
                initiatePost();   
            }
            else if (request.method() == "PUT")
            {
                initiatePut();   
            }
            else if (request.method() == "DELETE")
            {
                initiateDelete();   
            }
            else {

                error methodError("Method not implemented",20001);
                methodError.putOut(response);
            }

        }
    }
}


void    quoteResource::initiateGet() {

    std::string     _url = _request.pathInfo();
    
    if(std::regex_match(_url.begin(), _url.end(), __getOrPostQuoteRating))
    {
        _getQuoteRating_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteQuote))
    {
        _getQuote_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getQuoteCollection))
    {
        _getQuoteCollection_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteAuthor))
    {
        _getAuthor_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getAuthorCollection))
    {
        _getAuthorCollection_();
    }
    else 
    {
        error urlError("No such resource",20002);
        urlError.putOut(_response);
    }

}

void    quoteResource::initiatePost() {

    std::string     _url = _request.pathInfo();

    if(std::regex_match(_url.begin(), _url.end(), __getAccessToken))
    {
        _getAccessToken_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __invalidateAccessToken))
    {
        _invalidateAccessToken_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __createQuote))
    {
        _createQuote_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPostQuoteRating))
    {
        _postRating_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __addAuthor))
    {
        _addAuthor_();
    }
    else 
    {
        error urlError("No such resource",20002);
        urlError.putOut(_response);
    }
}


/* The Regexes */

std::regex      quoteResource::__getAccessToken = std::regex(
        "/token",   std::regex_constants::icase);

std::regex      quoteResource::__invalidateAccessToken = std::regex(
        "/invalidate_token",    std::regex_constants::icase);

std::regex      quoteResource::__createQuote = std::regex(
        "/quotes",  std::regex_constants::icase);

std::regex      quoteResource::__getOrPostQuoteRating = std::regex(
        "/quotes/[1-9][0-9]*/rating",   std::regex_constants::icase);

std::regex      quoteResource::__getOrPutOrDeleteQuote = std::regex(
        "/quotes/[1-9][0-9]*",  std::regex_constants::icase);

std::regex      quoteResource::__getQuoteCollection = std::regex(
        "/quotes?(sq=.*)?(idrange=[1-9][0-9]*-[1-9][0-9]*&)?(ratingrange=[0-9]{1}0*-[0-9]{1}0*&)?(authorid=[1-9][0-9]*&)?(authorratingrange=[0-9]{1}0*-[0-9]{1}0*&)?(authoridrange=[1-9][0-9]*-[1-9][0-9]*)?", 
        std::regex_constants::icase);

std::regex      quoteResource::__addAuthor = std::regex(
        "/authors", std::regex_constants::icase);

std::regex      quoteResource::__getOrPutOrDeleteAuthor = std::regex(
        "/authors/[1-9][0-9]*", std::regex_constants::icase);

std::regex      quoteResource::__getAuthorCollection = std::regex(
        "/authors?(idrange=[1-9][0-9]*-[1-9][0-9]*&)?(ratingrange=[0-9]{1}0*-[0-9]{1}0*)?", std::regex_constants::icase);

std::regex      quoteResource::__searchQuotes = std::regex(
        


