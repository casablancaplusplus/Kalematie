#ifndef     _QUOTE_RESOURCE_H_
#define     _QUOTE_RESOURCE_H_

#include "util/error.h"

#include <regex>

#include <Wt/WResource>



class quoteResource : public    Wt::WResource {
        

    public:
        quoteResource();
        
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

        // the POST group
        void    _getAccessToken_();
        void    _invalidateAccessToken_();
        void    _createQuote_();
        void    _postRating_();
        void    _addAuthor_();



    protected:
        virtual void    handleRequest (
                                        const   Wt::Http::Request&  request,
                                                Wt::Http::Response& response
                                      );
    
    private:
        
        const Wt::Http::Request&    _request;
        Wt::Http::Response&         _response;

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

};
#endif