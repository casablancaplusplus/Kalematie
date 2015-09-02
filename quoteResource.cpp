

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


            if(authenticate()) {
             
                // std::string     _url = _request.pathInfo();
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
    std::cout << "___PATH : " << _url << std::endl; 
    if(std::regex_match(_url.begin(), _url.end(), __getOrPostQuoteRating))
    {
        _getQuoteRating_();
    }
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPostQuoteFaves))
    {
        _getQuoteFaves_();
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
    else if(std::regex_match(_url.begin(), _url.end(), __getOrPostQuoteFaves))
    {
        _postFave_();
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
            quote_->commit();
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

void    quoteResource::_getQuoteFaves_()
{

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
            quote_->commit();
        }
        else
        {
            
            WJO resObj;

            resObj["errorMessage"] = WJV(std::string());
            resObj["errorCode"] = WJV(0);
            
            resObj["responseData"] = WJV(Wt::Json::ObjectType);
            WJO& resData = resObj["responseData"];
            resData["faves"] = WJV(quote_->getFaves());

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
        resData["faves"] = WJV(quote_->getFaves());
        resData["originality"] = WJV(quote_->getOriginality());

        responseGenerator   resGen(resObj);
        resGen.putOut(_response);
    }
    quote_->commit();

}

void    quoteResource::_getQuoteCollection_() {
  
    Quote   *quote_ = new Quote(_connectionPool);
    int     quoteCount = 0;
    quoteCount = quote_->getQuoteCount();

    // retrieve the set of parameters
    Wt::Http::ParameterMap     paramMap = _request.getParameterMap();
        // default author id
        int     authorId = 0;
        // default number of quotes fetched
        int     limit = 7; 
        // default start point of the quotes
        int     start = ++quoteCount;

        // the Iterator that holds the parameters
        Wt::Http::ParameterMap::iterator    it;

        //check for the author id
        if((it = paramMap.find("authorId")) != paramMap.end())
        {
            Author  *author_ = new Author(_connectionPool);
            int     authorCount = 0;
            std::string     aId = it->second[0];
            try {
                     authorId = std::stoi(aId);
            }catch(std::exception&  e) {
                std::cout << e.what() << std::endl;
            }
            authorCount = author_->getAuthorCount();
            if(authorId < 1 || authorId > authorCount)
            {
                error   err("THe provided authorId is out of range", 20013);
                err.putOut(_response);
                return; 
            }
            author_->commit();
        }
        

        // check the limit parameter
        auto    limitIt = paramMap.find("limit");
        if(limitIt != paramMap.end())
        {
            try{
                int     tempLimit = std::stoi(limitIt->second[0]);
                limit    = (tempLimit <= 20) ? tempLimit : 7;
            }catch(std::exception&  e) {
                std::cout << e.what() << std::endl;
            }
        }
 
        // check the start parameter
        auto    startIt = paramMap.find("start");
        if(startIt != paramMap.end())
        {
            try{
                int     tempStart = std::stoi(startIt->second[0]);
                start   = (tempStart > 0 && tempStart < quoteCount) 
                    ? tempStart : quoteCount + 1;
            }catch(std::exception&  e){
                std::cout << e.what() << std::endl;
            }
        }


        // generate response based on 
        // the parameters in the url query
        WJO     resObj;
        resObj["errorMessage"] = WJV(std::string());
        resObj["errorCode"] = WJV(0);
        resObj["responseData"] = WJV(Wt::Json::ObjectType);
        // the response data goes in the resData obj
        WJO&    resData = resObj["responseData"];

        if((it = paramMap.find("mostFaved")) != paramMap.end() 
                    && it->second[0] == "yes")
            {
            typedef     boost::tuple<int, std::string, int> result;
            typedef     dbo::collection<result>     ptrColl;

            std::string     query = "select id, text, faves from quote ";

            if(authorId != 0) {
                query += " WHERE Author_id = " + std::to_string(authorId);
                query += " AND id < " + std::to_string(start);
                query += " ORDER BY faves DESC ";
                query += " LIMIT " + std::to_string(limit);
            }
            else
            {
                query += " WHERE id < " + std::to_string(start);
                query += " ORDER BY faves DESC ";
                query += " LIMIT " + std::to_string(limit);
            }

            ptrColl     qPtrColl = quote_->query<result>(query);
            resData["quotes"] = WJV(Wt::Json::ArrayType);
            Wt::Json::Array&    resDataArr = resData["quotes"];
            for(ptrColl::iterator   it = qPtrColl.begin();
                    it != qPtrColl.end(); it++)
            {
                WJV     res = WJV(Wt::Json::ObjectType);
                WJO&    resO = res;
                resO["id"] = WJV((*it).get<0>());
                resO["text"] = WJV((*it).get<1>());
                resO["faves"] = WJV((*it).get<2>());

                resDataArr.push_back(res);
            }

        }
        else if((it = paramMap.find("topRated")) != paramMap.end()
                && it->second[0] == "yes")
        {
            typedef     boost::tuple<int, std::string, double> result;
            typedef     dbo::collection<result>     ptrColl;

            std::string     query = "select id, text, rating from quote ";

            if(authorId != 0) {
                query += " WHERE Author_id = " + std::to_string(authorId);
                query += " AND id < " + std::to_string(start);
                query += " ORDER BY rating DESC ";
                query += " LIMIT " + std::to_string(limit);
            }
            else
            {
                query += " WHERE id < " + std::to_string(start);
                query += " ORDER BY rating DESC ";
                query += " LIMIT " + std::to_string(limit);
            }

            ptrColl     qPtrColl = quote_->query<result>(query);
            resData["quotes"] = WJV(Wt::Json::ArrayType);
            Wt::Json::Array&    resDataArr = resData["quotes"];
            for(ptrColl::iterator   it = qPtrColl.begin();
                    it != qPtrColl.end(); it++)
            {
                WJV     res = WJV(Wt::Json::ObjectType);
                WJO&    resO = res;
                resO["id"] = WJV((*it).get<0>());
                resO["text"] = WJV((*it).get<1>());
                resO["rating"] = WJV((*it).get<2>());

                resDataArr.push_back(res);
            }

        }
        else if((it = paramMap.find("original")) != paramMap.end()
                &&  it->second[0] == "yes")
        {
            typedef     boost::tuple<int, std::string, int> result;
            typedef     dbo::collection<result>     ptrColl;

            std::string     query = "select id, text, originality from quote ";

            if(authorId != 0) {
                query += " WHERE Author_id = " + std::to_string(authorId);
                query += " AND id < " + std::to_string(start);
                query += " ORDER BY originality DESC ";
                query += " LIMIT " + std::to_string(limit);
            }
            else
            {
                query += " WHERE id < " + std::to_string(start);
                query += " ORDER BY originality DESC ";
                query += " LIMIT " + std::to_string(limit);
            }

            ptrColl     qPtrColl = quote_->query<result>(query);
            resData["quotes"] = WJV(Wt::Json::ArrayType);
            Wt::Json::Array&    resDataArr = resData["quotes"];
            for(ptrColl::iterator   it = qPtrColl.begin();
                    it != qPtrColl.end(); it++)
            {
                WJV     res = WJV(Wt::Json::ObjectType);
                WJO&    resO = res;
                resO["id"] = WJV((*it).get<0>());
                resO["text"] = WJV((*it).get<1>());
                resO["originality"] = WJV((*it).get<2>());

                resDataArr.push_back(res);
            }
        }
        else if((it = paramMap.find("faves")) != paramMap.end()
                && it->second[0] == "yes" && authorId != 0)
        {
            Fave    *fave_ = new Fave(_connectionPool);
            int     favedQuoteCount = fave_->query<int>("select count(*) from fave");
            start = favedQuoteCount+1;

            startIt = paramMap.find("start");
            if(startIt != paramMap.end())
            {
                try{
               
                    int     tempStart = std::stoi(startIt->second[0]);
                    start   = (tempStart > 0 && tempStart < favedQuoteCount) 
                        ? tempStart : favedQuoteCount + 1;
            
                }catch(std::exception&  e){
               
                    std::cout << e.what() << std::endl;
                }
        
            }

            typedef     boost::tuple<int, std::string> result;
            typedef     dbo::collection<result>     ptrColl;
            
            std::string     query = "select q.id, q.text from quote  q inner join fave  f on q.id = f.quoteId WHERE f.faverId = " 
                + std::to_string(authorId) + " AND f.quoteId < " + std::to_string(start) + " ORDER BY f.quoteId DESC LIMIT "
                + std::to_string(limit);

            ptrColl     qPtrColl = quote_->query<result>(query);
            resData["quotes"] = WJV(Wt::Json::ArrayType);
            Wt::Json::Array&    resDataArr = resData["quotes"];
            for(ptrColl::iterator   it = qPtrColl.begin();
                    it != qPtrColl.end(); it++)
            {
                WJV     res = WJV(Wt::Json::ObjectType);
                WJO&    resO = res;
                resO["id"] = WJV((*it).get<0>());
                resO["text"] = WJV((*it).get<1>());

                resDataArr.push_back(res);
            }

        }
        else
        {
            typedef     boost::tuple<int, std::string>  result;
            typedef     dbo::collection<result>     ptrColl;

            std::string     query = "select id, text from quote ";
            if(authorId != 0 ) {
                query += " WHERE Author_id = " + std::to_string(authorId);
                query += " AND id < " + std::to_string(start) + " ORDER BY id \
                      DESC LIMIT " + std::to_string(limit);
            }
            else {

                query += " WHERE id < " + std::to_string(start) + " ORDER BY id \
                      DESC LIMIT " + std::to_string(limit);
            }

            ptrColl     qPtrColl = quote_->query<result>(query);

            resData["quotes"] = WJV(Wt::Json::ArrayType);
            Wt::Json::Array&    resDataArr = resData["quotes"];
            for(ptrColl::iterator   it = qPtrColl.begin();
                    it != qPtrColl.end(); it++)
            {
                WJV     res = WJV(Wt::Json::ObjectType);
                WJO&    resO = res;
                resO["id"] = WJV((*it).get<0>());
                resO["text"] = WJV((*it).get<1>());

                resDataArr.push_back(res);
            }
          
        }
        
        responseGenerator   resGen(resObj);
        resGen.putOut(_response);
            
    quote_->commit();    
}

void    quoteResource::_getAuthor_() {


    urlAnalyzer     uAnal(_request.pathInfo());
    std::vector<std::string>    urlVec = uAnal.getResult();
    int     authorId = 0;
    try {
        authorId = std::stoi(urlVec[1]);
    }catch(std::exception&  e) {

        std::cout << e.what() << std::endl;
    }catch(...) {
        std::cout << "Error : There was a problem with the provided \
            author id " << std::endl;
    }
    Author   *author_ = new Author(_connectionPool);
    if(!author_->initWithAuthorId(authorId))
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
        resData["id"] = WJV(author_->getId());
        resData["nickname"] = WJV(author_->getNickName());
        resData["rating"] = WJV(author_->getRating());
        resData["followers"] = WJV(author_->getFollowers());
        resData["following"] = WJV(author_->getFollowing());

        responseGenerator   resGen(resObj);
        resGen.putOut(_response);
    }
    author_->commit();
}
void    quoteResource::_getAuthorCollection_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);
}

void    quoteResource::_getAccessToken_() {
    std::string     authString = _request.headerValue("Authorization");
    tokenExtractor  tokenStr(authString);
    Token    *token_ = new Token(tokenStr.getTokenStr());
    if(token_-> createAccessToken(_connectionPool)) {
        WJO resObj;
        resObj["errorMessage"] = WJV(std::string());
        resObj["errorCode"] = WJV(0);
        resObj["responseData"] = WJV(Wt::Json::ObjectType);
        WJO&    resData = resObj["responseData"];
        resData["accessToken"] = WJV(token_->getAccessToken());

        responseGenerator   resGen(resObj);
        resGen.putOut(_response);
    }
    else {
        error   err("Invalid credentials", 20014);
        err.putOut(_response);
    }
}

void    quoteResource::_invalidateAccessToken_() {
    // TODO : make sure you don't
    // create an access token for 
    // a client that already has one
    std::string     authString  = _request.headerValue("Authorization");
    tokenExtractor  tokenStr(authString);
    Token   *token_ = new Token(tokenStr.getTokenStr());
    // extract the access token from the body
    bodyExtractor   Body(_request);
    if(!Body.turnIntoJsonObj()) {
        error   err("The provided body is not well formed", 20008);
        err.putOut(_response);
        //dbug
        std::cout << Body.getError().what() << std::endl;
        return;
    } else {
        Wt::Json::Object&   jBody = Body.getJsonObjBody();
        Wt::Json::Value     jText = jBody.get("accessToken");
        if(jText.isNull() || jText.type() != Wt::Json::Type::StringType)
        {
            error   err("The provided body is not well formed", 20008);
            err.putOut(_response);
        } else {
            std::string     accessToken = jText;
            if(token_->invalidateAccessToken(accessToken, _connectionPool)) {
                WJO resObj;
                resObj["errorMessage"] = WJV(std::string());
                resObj["errorCode"] = WJV(0);
                resObj["responseData"] = WJV(std::string());

                responseGenerator   resGen(resObj);
                resGen.putOut(_response);
            
            } else {
                error   err("Invalid credentials", 20014);
                err.putOut(_response);
            }
        }
    }
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
                    quote_->commit();
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


void    quoteResource::_postFave_() {
    
    if(_role == author::role::Guest)
    {
        error   err("You don't have enough privilage to perform this\
                operation", 20007);
        err.putOut(_response);
    }
    else
    {
        urlAnalyzer uAnal(_request.pathInfo());
        std::vector<std::string>   urlVec = uAnal.getResult();
        int     quoteId = 0;
        try {
            quoteId = std::stoi(urlVec[1]);
        }catch(std::exception&  e ) {
            std::cout << e.what() << std::endl;
        }
        Quote   *quote_ = new Quote(_connectionPool);
        if(!quote_->initWithQuoteId(quoteId))
        {
            error err("No such resource", 20002);
            err.putOut(_response);
        }
        else
        {
            quote_->commit();

            Fave    *fave_ = new Fave(_connectionPool);
            fave_->initNewFave();
            fave_->setFaverId(_authorId);
            fave_->setQuoteId(quoteId);
            fave_->addFave();

            fave_->commit();

            quote_->updateFaves();
            quote_->commit();
            
            WJO         resObj;
            responseGenerator   resGen(resObj);
            resGen.putOut(_response,true);
        }
    }
}






void    quoteResource::_addAuthor_() {
    bodyExtractor   Body(_request);
    if(!Body.turnIntoJsonObj()) {
        error   err("The provided body is not well formed", 20008);
        err.putOut(_response);
    } else {
        Wt::Json::Object&   jBody = Body.getJsonObjBody();
        Wt::Json::Value     jUsername = jBody.get("username");
        Wt::Json::Value     jNickName = jBody.get("nickName");
        if(jUsername.isNull() || jNickName.isNull() ||
                jUsername.type() != Wt::Json::Type::StringType ||
                jNickName.type() != Wt::Json::Type::StringType ) {
            error err("The provided body is not well formed", 20008);
            err.putOut(_response);
        } else {
            std::string     username = jUsername;
            std::string     nickName = jNickName;
            // use this variable as a reminder of the username type
            // email or phonenumber
            std::string     usernameType = "";
            Credentials     *creds_ = new Credentials(_connectionPool);
            if(std::regex_match(username.begin(), username.end(),
                        Token::getEmailRegex())) {
                if(creds_->initWithEmail(username)) {
                    error   err("User already exists", 20015);
                    err.putOut(_response);
                    creds_-> commit();
                    return;
                } 
                usernameType = "email";
            } else if(std::regex_match(username.begin(), username.end(),
                        Token::getPhoneNumberRegex())) {
                if(creds_->initWithPhoneNumber(username)) {
                    error   err("User already exists", 20015);
                    err.putOut(_response);
                    creds_->commit();
                    return;
                }
                usernameType = "phoneNumber";
            } else if(nickName == "" || nickName.size() < 3) {
                error   err("Invalid username or nickname", 20017);
                err.putOut(_response);
                creds_->commit();
                return;
            } else {
                error   err("Invalid username or nickname", 20017);
                err.putOut(_response);
                creds_->commit();
                return;
            }
            creds_->commit(); // unlock the db

            Author      *author_ = new Author(_connectionPool);
            if(author_->initWithNickName(nickName)) {
                error err("Nickname taken", 20016);
                err.putOut(_response);
                author_->commit();
                return;
            }
            author_->commit();
            try {
            // submit the username and generate a password
            creds_-> initNewCredentials();
            (usernameType == "email" ) ? 
                creds_->setEmail(username) : creds_->setPhoneNumber(username);
            std::string     password = "";
            std::string     rawPassword = "";
            // a boolean that is used to generate a unique password
            bool    generate = true;
            while(generate) {
                Wt::WDateTime   dateTime = Wt::WDateTime::currentDateTime();
                rawPassword = "nazar:masoume:" + 
                    std::to_string(dateTime.toTime_t());
                password = Wt::Utils::base64Encode(Wt::Utils::md5(rawPassword))
                .substr(0,5); // TODO conver to lower case 
                // TODO eliminate any  non alphabet characters
            
                // check for it in the db
                kalematieSession    _session(_connectionPool);
                dbo::Transaction    t(_session);
                
                dbo::ptr<credentials>  tempDbPtr = _session.find<credentials>()
                    .where("password = ?").bind(password);
                if(!tempDbPtr.get()) generate = false; // break the loop
            }
            creds_->setPassword(password);
             
            author_->initNewAuthor();
            author_->setNickName(nickName);
            author_->setRole(author::role::Author);
            author_->addAuthor();
            author_->commit();
            creds_->setAuthor(author_->getDbPtr());
            creds_->addCredentials();
            creds_->commit();
            // send the password to the client
            // via either email or phone number
            /*
            if(usernameType == "email") { // send via email
                Wt::Mail::Message   message;
                message.setFrom(Wt::Mail::Mailbox("no-reply@kalematie.me", "Kalematie"));
                message.addRecipient(Wt::Mail::To, Wt::Mail::Mailbox(username, nickName));
                message.setSubject("Kalematie password");
                std::string b = "There are your kalematie credentials: fuck you "; 
                message.setBody(b);
                Wt::Mail::Client    client;
                client.connect("localhost");
                client.send(message);
            } else if (usernameType == "phoneNumber") {
                Wt::Http::Client    *client = new Wt::Http::Client();
                client->setTimeout(20);
                client->setMaximumResponseSize(10*1024);
                client->done().connect(boost::bind(&quoteResource::handle, this,
                            _1, _2));
                std::string     message = "";
                std::string     tempMess = "http://api.kavenegar.com/v1/4B706A4A50784744734773477049516D313947694D4138513D3D/sms/send.json?receptor=09169211845&sender=30006703323323&message=";
                message += Wt::Utils::htmlEncode("Your Kalematie password is : " + password);
                if(client->request(Wt::Http::Method::Get,tempMess+message,Wt::Http::Message())) { 
                    std::cout << "SMS SENT" << std::endl;
            } else std::cout << "COULD NOT SEND SMS" << std::endl;
            }
            */
            WJO resObj;
            resObj["errorMessage"] = WJV(std::string());
            resObj["errorCode"] = WJV(0);
            resObj["responseData"] = WJV(Wt::Json::ObjectType);
            WJO&    resData = resObj["responseData"];
            resData["password"] = WJV(password);

            responseGenerator   resGen(resObj);
            resGen.putOut(_response);

            } catch(Wt::Dbo::Exception& e) {
                std::cout << e.what() << std::endl;
                return;
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return;
            } catch(...) {
                std::cout << "Something went wrong trying to \
                    register a new user " << std::endl;
                return;
            }
        }
    }
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
                       std::cout << text << std::endl;
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
            return;
        }
        else if(quote_->getAuthor().id() != _authorId)
        {
            error   err("You don't have enough privilage to perform this\
                    operation", 20007);
            err.putOut(_response);
            return;
        }
        quote_->remove();

        quote_->commit();
        
        WJO     resObj;
        responseGenerator   resGen(resObj);
        resGen.putOut(_response, true);
    }
         
}

void    quoteResource::_deleteAuthor_() {
    error   urlError("Resource Not implemented yet", 20003);
    urlError.putOut(_response);

}


bool    quoteResource::authenticate() {

    std::string     authString = _request.headerValue("Authorization");
    // dbug 
    std::cout << "____ AUTH STRING _____ : " << authString << std::endl;
    // TODO : do a size check for the value of the Authorization header
    if ( authString == "") {
        std::string     _url = _request.pathInfo();
        if(_request.method() == "POST" &&
                std::regex_match(_url.begin(), _url.end(), __addAuthor)) {
            return true;
        } else {
            error   authError("No Authorization header was provided",20000);
            authError.putOut(_response);
        }
    }
    else
    {
        std::cout << "____ AUTH STRING _____ : " << authString << std::endl;
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
std::regex      quoteResource::__getOrPostQuoteFaves = std::regex(
        "/quotes/[1-9][0-9]*/faves",    std::regex_constants::icase);

std::regex      quoteResource::__getOrPutOrDeleteQuote = std::regex(
        "/quotes/[1-9][0-9]*",  std::regex_constants::icase);

std::regex      quoteResource::__getQuoteCollection = std::regex(
        "/quotes", std::regex_constants::icase);

std::regex      quoteResource::__addAuthor = std::regex(
        "/authors", std::regex_constants::icase);

std::regex      quoteResource::__getOrPutOrDeleteAuthor = std::regex(
        "/authors/[1-9][0-9]*", std::regex_constants::icase);

std::regex      quoteResource::__getAuthorCollection = std::regex(
        "/authors?(idrange=[1-9][0-9]*-[1-9][0-9]*&)?(ratingrange=[0-9]{1}0*-[0-9]{1}0*)?", std::regex_constants::icase);

        
std::regex      quoteResource::__tokenSearchReg = std::regex(
        "[\\s]+", std::regex_constants::icase);

// test

void    quoteResource::handle(boost::system::error_code err, const Wt::Http::Message&  res) {
    //std::cout << res.body() << std::endl;
    //std::cout << "I'm here" << std::endl;
    if(!err) {
        if(res.status() == 200) {
            std::cout << "DELIVERED" << std::endl;
            //std::cout << res.body() << std::endl;
        } else{
            std::cout << "COULD NOT BE DELIVERED: " << err.message() << std::endl;
        }
    } else {
        std::cout << err.message() << std::endl;
    }
}
