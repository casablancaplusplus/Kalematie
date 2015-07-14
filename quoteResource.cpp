

#include "quoteResource.h"


quoteResource::quoteResource(Wt::Dbo::SqlConnectionPool&    connectionPool)
    : _connectionPool(connectionPool)
    {
    }

void    quoteResource::handleRequest(   const Wt::Http::Request&    request,
                                        Wt::Http::Response&         response)
{
    
   if(request.headerValue("Authorization") == "")
    {
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

void    quoteResource::initiatePut() {

    std::string     _url = _request.pathInfo();

    if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteQuote))
    {
        _modifyQuote_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteAuthor))
    {
        _modifyAuthor_();
    }
    else
    {
        error urlError("No such resource", 20002);
        urlError.putOut(_response);
    }
}

void    quoteResource::initiateDelete() {

    std::string     _url = _request.pathInfo();

    if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteQuote))
    {
        _deleteQuote_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPutOrDeleteAuthor))
    {
        _deleteAuthor_();
    }
    else 
    {
        error urlError("No such resource", 20002);
        urlError.putOut(_response);
    }
}

void    quoteResource::_getQuoteRating_() {

    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);
}

void    quoteResource::_getQuote_() {

    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);
}

void    quoteResource::_getQuoteCollection_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_getAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_getAccessToken_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_invalidateAccessToken_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_createQuote_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_postRating_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_addAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_modifyQuote_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_modifyAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_deleteQuote_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_deleteAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}


bool    quoteResource::authenticate() {
    
    std::string     authString = _request.headerValue("Authorization");
    // TODO : do a size check for the value of the Authorization header
    if ( authString == "") {
        error   authError("No Authorization header was provided");
        authError.putOut();
    }
    else
    {
        std::size_type  pos;
        if((pos=authString.find("Bearer"))!=std::basic_string::npos)
        {
            
            // extract the access token
            std::string     tokenStr;
            std::string::const_iterator     it = authString.begin();
            it = it + pos + 6;

            for(;it != authString.end(); it++)
            {
                if((*it)!=" ")
                {
                     while((*(++it))!=" " || it!=authString.end())
                     {
                         tokenStr+=*it;
                     }
                     it = authString.end();

                }
            }

            //check for the token in the db
            kalematieSession        session(_connectionPool);
            Wt::Dbo::Transaction    t(session);
            try {
                Wt::Dbo::ptr<accessToken>       token =
                    session.find<accessToken>().where("token = ?").bind(tokenStr);
            }catch(Wt::Dbo::Exception&  e){
                error   tokenError("Invalid access token",20006);
                tokenError.putOut(_response);
                return false;
            }

            _role = token->role;
            _authorId = token->userId;

            return true;
            
        }
        else if(authString.find("Basic")!=std::basic_string::npos)
        {
            std::string     _url = _request.pathInfo();
            if(_request.method() == "POST")
            {
                if(std::regex_match(_url.begin(), _url.end(), __getAccessToken)
                    || std::regex_match(_url.begin(), _url.end(), _invalidateAccessToken))
                {
                    return true;
                }

            }
            else
            {
                error invalidReqErr("Basic token But invalid url or method", 20005);
                invalidReqErr.putOut();
                return false;
            }



        }
        else
        {

            error   authHeaderErr("Incorrect Authorization header value",20004);
            authHeaderErr.putOut();
            
            return false;

        }

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

        


