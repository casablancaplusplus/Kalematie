#ifndef     _QUOTE_RESOURCE_H_
#define     _QUOTE_RESOURCE_H_

#include "util/error.h"
#include "util/tokenExtractor.h"
#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"

#include <regex>

#include <Wt/Dbo/SqlConnectionPool>



class quoteResource  {
        

    public:
        quoteResource(Wt::Dbo::SqlConnectionPool&   connectionPool,
                const Wt::Http::Request&    request,
                Wt::Http::Response&         response);
        
        bool authenticate();

        /* the following function compare the request.pathInfo()
         * with to regexes to determine what response generating
         * functions to call and actually call them
         */
        
        void    initiateGet();
        void    initiatePost();
        void    initiatePut();
        void    initiateDelete();
        

        /* functions that take care of generating 
         * the response based on the clients request
         */

        // the GET group
        void    _getQuoteRating_();
        void    _getQuote_();
        void    _getQuoteCollection_();
        void    _getAuthor_();
        void    _getAuthorCollection_();

        // the POST group
        void    _getAccessToken_();         // security layer 
        void    _invalidateAccessToken_();  // security layer

        void    _createQuote_();
        void    _postRating_();
        void    _addAuthor_();


        // the PUT group
        void    _modifyQuote_();
        void    _modifyAuthor_();

        // the DELETE group
        void    _deleteQuote_();
        void    _deleteAuthor_();

    private:
        
        const Wt::Http::Request&    _request;
        Wt::Http::Response&         _response;


        // User Role and id
        author::role                _role;
        int                         _authorId;

        // the connection pool
        Wt::Dbo::SqlConnectionPool&     _connectionPool;
        
        
        // These regex objects are used to determine
        // what member function to call
        static  std::regex      __getAccessToken;
        static  std::regex      __invalidateAccessToken;
        static  std::regex      __createQuote;

        // The function call corresponding to this regex match
        // will be different based on the request method
        // if get -> rating is retrieved
        // if post -> a quote gets rated
        static  std::regex      __getOrPostQuoteRating;
        
        // The function call corresponding to this regex match
        // will be different based on the request method
        // if get -> a quote is retrieved
        // if put -> a quote is updated
        // if delete -> a quote is deleted
        static  std::regex      __getOrPutOrDeleteQuote;
        
        // This function call is used to search quotes as well
        static  std::regex      __getQuoteCollection;

        static  std::regex      __addAuthor;

        // The function call corresponding to this regex match
        // will be different based on the request method 
        // if get -> the author's info will be retrieved
        // if put -> the autho's information will be updated
        // if delete -> the author will be deleted
        static  std::regex      __getOrPutOrDeleteAuthor;
        
        static  std::regex      __getAuthorCollection;

        // token search regex
        static  std::regex      __tokenSearchReg;
};
#endif
