

#include "quoteResource.h"

#include <Wt/Http/Request>

quoteResource::quoteResource(Wt::Dbo::SqlConnectionPool&    connectionPool,
        const   Wt::Http::Request&      request,
        Wt::Http::Response&             response)
    : _connectionPool(connectionPool),
      _request(request),
      _response(response)
    {
        if(_request.headerValue("authorization") == "")
        {
            error   headererror("no authorization header was provided",20000);
            headererror.putOut(response);
        }
        else {


            // authenticate not implemented yet
            if(authenticate()) {
             
                 std::string     _url = _request.pathInfo();
                //check the request method
                if(_request.method() == "GET")
                {
                 initiateGet();
                }
                else if (_request.method() == "POST")
                {
                 initiatePost();   
                }
                else if (_request.method() == "PUT")
                {
                 initiatePut();   
                }
                else if (_request.method() == "DELETE")
                {
                 initiateDelete();   
                }
                else {

                    error methoderror("method not implemented",20001);
                    methoderror.putOut(response);
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
    
        urlAnalyzer uAnal(_request.pathInfo());
        std::vector<std::string>    urlVec = uAnal.getResult();
        int     quoteId = 0;
        try {

             quoteId = std::stoi(urlVec[1]);
        } catch(std::exception& e) {

            std::cout << e.what() << std::endl;

        } catch(...) {
            std::cout << "Error : There was a problem with the provided \
                quote id " << std::endl;
        }
        Quote   *quote_ = new Quote(_connectionPool);
        if(!quote_->initWithQuoteId(quoteId))
        {
            error   err("No such resource", 20002);
            err.putOut(_response);
        }
        else
        {
            
            WJO resObj;

            resObj["errorMessage"] = WJV(std::string());
            resObj["errorCode"] = WJV(0);
            
            resObj["responseData"] = WJV(Wt::Json::ObjectType);
            WJO& resData = resObj["responseData"];
            resData["rating"] = WJV(quote_->getRating());

            responseGenerator       resGen(resObj);
            resGen.putOut(_response);

        }
        quote_-> commit();
        
}

void    quoteResource::_getQuote_() {
   
    urlAnalyzer     uAnal(_request.pathInfo());
    std::vector<std::string>    urlVec = uAnal.getResult();
    int     quoteId = 0;
    try {
        quoteId = std::stoi(urlVec[1]);
    }catch(std::exception&  e) {

        std::cout << e.what() << std::endl;
    }catch(...) {
        std::cout << "Error : There was a problem with the provided \
            quote id " << std::endl;
    }
    Quote   *quote_ = new Quote(_connectionPool);
    if(!quote_->initWithQuoteId(quoteId))
    {
        error err ("No such resource", 20002);
        err.putOut(_response);
    }
    else
    {
        WJO resObj;
        resObj["errorMessage"] = WJV(std::string());
        resObj["errorCode"] = WJV(0);

        resObj["responseData"] = WJV(Wt::Json::ObjectType);
        WJO&    resData = resObj["responseData"];
        resData["id"] = WJV(quote_->getId());
        resData["text"] = WJV(quote_->getText());
        resData["author_id"] = WJV(quote_->getAuthor().id());
        std::string   timeStr = quote_->getDatePublished();
        resData["date_published"]= WJV(Wt::WString::fromUTF8(timeStr));
        resData["rating"]= WJV(quote_->getRating());
        resData["viewers"] = WJV(quote_->getViewers());

        responseGenerator   resGen(resObj);
        resGen.putOut(_response);
    }

}

void    quoteResource::_getQuoteCollection_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_getAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_getAuthorCollection_() {
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
    
    if(_role == author::role::Guest) 
    {
        error   privilageErr("You don't have enough privilage to perform this\
                                operation",20007);
        privilageErr.putOut(_response);
    }
    else
    {
        bodyExtractor   Body(_request);
        if(!Body.turnIntoJsonObj()){
            error   bodyErr("The provided body is not well formed",20008);
            bodyErr.putOut(_response);
            // dbug
            std::cout << Body.getError().what() << std::endl;
        }
        else
        {
            Author      *author_ = new Author(_connectionPool);
            if(author_->initWithAuthorId(_authorId))
            {
               Quote    *quote_ = new Quote(_connectionPool);
               quote_->initNewQuote();

               // retrieve the json body
               Wt::Json::Object&    jBody = Body.getJsonObjBody();
               Wt::Json::Value      jtext = jBody.get("text");
               if(jtext.isNull() || jtext.type() != Wt::Json::Type::StringType)
               {
                    error   bodyErr("The provided body is not well formed",20008);
                    bodyErr.putOut(_response);
               }
               else
               {
                    std::string     text = jtext;
                    quote_->setText(text);
                    quote_->setAuthor(author_->getDbPtr());

                    // TODO check if the following line can be ommited
                    // in other words, check if a transaction can be commited when
                    // there's an active transaction on the same session and 
                    // the transactions are not nested
                    author_->commit();
                    // set the publish date
                    std::time_t     timeT = std::chrono::system_clock::to_time_t(
                            std::chrono::system_clock::now());
                    std::string     strTime = std::to_string(timeT);
                    quote_->setDatePublished(strTime);

                    // persist the quote
                    quote_->addQuote();
                    if(quote_->commit())
                    {
                        std::ostream&   out = _response.out();
                        

                        WJO    resObj;
                        
                        resObj["errorMessage"] = WJV(std::string());
                        resObj["errorCode"] = WJV(0);
                        resObj["responseData"] = WJV(std::string());
                        
                        responseGenerator   resGen(resObj);
                        resGen.putOut(_response);
                    }
                    else
                    {
                        error   err("Could not insert the new quote into the db",
                                20011);
                        err.putOut(_response);
                    }

               }
      


            }
            else
            {
                error   err("The was a problem fetching the author with this id",
                        20010);
                err.putOut(_response);
            }
        }
    }
        

}

void    quoteResource::_postRating_() {

    if(_role == author::role::Guest) 
    {
        error   privilageErr("You don't have enough privilage to perform this\
                                operation",20007);
        privilageErr.putOut(_response);
    }
    else
    {
        urlAnalyzer uAnal(_request.pathInfo());
        std::vector<std::string>    urlVec = uAnal.getResult();
        int     quoteId = std::stoi(urlVec[1]);
        Quote   *quote_ = new Quote(_connectionPool);
        if(!quote_->initWithQuoteId(quoteId))
        {
            error   err("No such resource", 20002);
            err.putOut(_response);
        }
        else
        {
            bodyExtractor   Body(_request);
            if(!Body.turnIntoJsonObj())
            {
                error   err("The provided body is not well formed",20008);
                err.putOut(_response);
            }
            else
            {
                Wt::Json::Object&   jBody = Body.getJsonObjBody();
                Wt::Json::Value     jVal = jBody.get("rating");
                
                if(
                        jVal.isNull() 
                        ||jVal.type() != Wt::Json::NumberType
                //        || (rating > 10.0)
                 //       || (rating < 0.0)
                  )
                {
                    error   err("The provided body is not well formed",20008);
                    err.putOut(_response);
                }
                else
                {
                    double       rating = jVal;
                    dbo::ptr<author>    auth = quote_->getAuthor();
                    if((rating > 10.0)|| (rating < 0.0))
                    {
                        error err ("The provided body is not well formed",20008);
                        err.putOut(_response);
                    }
                    else if(!auth.get()) 
                    {
                         error   err("No such resource",20002);
                         err.putOut(_response);

                    }
                    else if( auth.id() == _authorId)
                    {
                        error   err("You don't have enough privilage to perform\
                                    this operation",20007);
                         err.putOut(_response);
                    }
                    else
                    {

                    quote_->commit();

                    Rating      *rating_=new Rating(_connectionPool);
                    rating_->initNewRating();
                    rating_->setQuoteId(quoteId);
                    rating_->setRaterId(_authorId);
                    rating_->setRating(rating);
                    rating_->addRating();

                    rating_->commit();

                    quote_->updateRating();
                    
                    
                    WJO    resObj;
                        
                    resObj["errorMessage"] = WJV(std::string());
                    resObj["errorCode"] = WJV(0);
                    resObj["responseData"] = WJV(std::string());
                     
                    responseGenerator   resGen(resObj);
                    resGen.putOut(_response);
                    }
 
                }
            }
        }
    }
}

void    quoteResource::_addAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}

void    quoteResource::_modifyQuote_() {
    
   if(_role == author::role::Guest || _role == author::role::Validator)
   {
       error pError("You don't have enough privilage to perform this\
               operation", 20007);
       pError.putOut(_response);
   }
   else
   {
       urlAnalyzer  uAnal(_request.pathInfo());
       std::vector<std::string>     urlVec = uAnal.getResult();
       int      quoteId = 0;
       try {
       
           quoteId = std::stoi(urlVec[1]);
       }catch(std::exception&   e) {
           std::cout << e.what() << std::endl;
       }catch(...) {
           std::cout << "Error : something wrong with the quote id" << std::endl;
       }
       Quote    *quote_ = new Quote(_connectionPool);
       if(!quote_->initWithQuoteId(quoteId))
       {
           error err("No such resource", 20002);
           err.putOut(_response);
       }
       else
       {
           if(quote_->getAuthor().id() == _authorId ||
                   _role == author::role::Administrator )
           {
               bodyExtractor    Body(_request);
               if(!Body.turnIntoJsonObj()) {
                   error    bodyErr("The provided body is not well formed",
                           20008);
                   bodyErr.putOut(_response);
               }
               else {
                   Wt::Json::Object&    jBody = Body.getJsonObjBody();
                   Wt::Json::Value      jText = jBody.get("text");
                   if(jText.isNull() 
                           || jText.type() != Wt::Json::Type::StringType)
                   {
                       error    bodyErr("The provided body is not well formed",
                               20008);
                       bodyErr.putOut(_response);
                   }
                   else
                   {
                       std::string  text = jText;
                       quote_->updateText(text);
                       quote_->updateVerificationStatus(false);
                       quote_->commit();
                        
                       responseGenerator    resGen;
                       resGen.putOut(_response, true);
                   }
               }
           }
           else
           {
               error pError("You don't have enough privilage to perform this\
               operation", 20007);
               pError.putOut(_response);
           }
       }
   }
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
    /*
     * test code
     * you used this code to add records to the tables
     *

            kalematieSession        session(_connectionPool);
            Wt::Dbo::Transaction    t(session);
            
            accessToken     *aToken = new   accessToken();
            aToken -> token = "accesstoken";
            aToken -> userId= 1;
            aToken -> role = author::Author;

            author          *anAuthor = new author();
            anAuthor -> firstName = "Nazar";
            anAuthor -> lastName = "Abdolkhanie";
            anAuthor -> nickName = "casablanca";
            anAuthor -> phoneNumber = "09169211845";
            anAuthor -> password = "secret";
            anAuthor -> rating = 8.9;
            anAuthor -> followers = 1232;
            anAuthor -> following = 452;
            anAuthor -> authorRole = author::Author;
            
            session.add(aToken);
            session.add(anAuthor);


    ********end**************/

    std::string     authString = _request.headerValue("Authorization");
    // TODO : do a size check for the value of the Authorization header
    if ( authString == "") {
        error   authError("No Authorization header was provided",20000);
        authError.putOut(_response);
    }
    else
    {
        if(authString.find("Bearer")!=std::string::npos)
        {
            tokenExtractor  tokenStr(authString);

            if(!tokenStr.empty()) { 
            //check for the token in the db
            kalematieSession        session(_connectionPool);
            Wt::Dbo::Transaction    t(session);
            try {
                Wt::Dbo::ptr<accessToken>       token =
                    session.find<accessToken>().where("token = ?")
                    .bind(tokenStr.getTokenStr()); 
                _role = token->role;
                _authorId = token->userId;

                return true;

            }catch(Wt::Dbo::Exception&  e){
                error   tokenError("Invalid access token",20006);
                tokenError.putOut(_response);
                return false;
            }
            }
            else {

                error tokenError("Invalid access token", 20006);
                tokenError.putOut(_response);
                return false;
            }


                        
        }
        else if(authString.find("Basic")!=std::string::npos)
        {
            std::string     _url = _request.pathInfo();
            if(_request.method() == "POST")
            {
                if(std::regex_match(_url.begin(), _url.end(), __getAccessToken)
                    || std::regex_match(_url.begin(), _url.end(), __invalidateAccessToken))
                {
                    return true;
                }
                else
                {
                    error invalidReqErr("Basic token but invalid url or method",20005);
                    invalidReqErr.putOut(_response);
                    return false;
                }

            }
            else
            {
                error invalidReqErr("Basic token But invalid url or method", 20005);
                invalidReqErr.putOut(_response);
                return false;
            }



        }
        else
        {

            error   authHeaderErr("Incorrect Authorization header value",20004);
            authHeaderErr.putOut(_response);
            
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

        
std::regex      quoteResource::__tokenSearchReg = std::regex(
        "[\\s]+", std::regex_constants::icase);
