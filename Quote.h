#ifndef     _QUOTE_H_
#define     _QUOTE_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"
#include "Rating.h"

#include <Wt/Dbo/SqlConnectionPool>
#include <Wt/Dbo/Query>

class   Quote {
    
    public:
        Quote(Wt::Dbo::SqlConnectionPool&   connectionPool);
        ~Quote();

        int             getQuoteCount();
        template<class  T>
        dbo::collection<T>   query(std::string  qStr){

            if(_transaction.isActive())
    
            {
        try {
        Wt::Dbo::Query<T>    q =
            _session.query<T>(qStr);
        dbo::collection<T>   qPtrColl = q.resultList();
        return qPtrColl;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return dbo::collection<T>();
        }catch(...) {
            std::cout << "Quote::query() cath(...)" << std::endl;
            return dbo::collection<T>();
        }
        
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try {
            Wt::Dbo::Query<T>    q =
                _session.query<T>(qStr);
            dbo::collection<T>   qPtrColl = q.resultList();
            t.commit();
            return qPtrColl;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return dbo::collection<T>();
        }catch(...) {
            std::cout << "Quote::query() cath(...)" << std::endl;
            return dbo::collection<T>();
        }

       
    }
        }

        // these functions initialize dbPtr
        // these function should check if the dbPtr is iniated first
        bool            initWithQuoteId(int     quoteId);
        bool            initWithQuoteText(std::string   text);
        bool            setDbPtr(dbo::ptr<quote>&   ptr); // initialize using an existing ptr
        int             getId();
        std::string     getText();
        std::string     getDatePublished();
        double          getRating();
        int             getViewers();
        int             getFaves();  
        // do a manual null check for _dbPtr before using this method
        bool            getVerificationStatus();
        dbo::ptr<author>    getAuthor();
        dbo::ptr<quote>&     getDbPtr(); // returns the smart pointer itself
        
        bool            updateText(std::string  text);
        bool            updateDatePublished(std::string&   date);
        bool            updateRating();// this is the overall rating of a quote
        bool            updateViewers();
        bool            updateFaves(); //
        bool            updateVerificationStatus(bool   tOrf);
        bool            updateAuthor(dbo::ptr<author>&  authorPtr);

        bool            commit(); // persists a new quote or the modifications of an existing quote
        
        void            initNewQuote();
        void            setText(std::string text);
        void            setDatePublished(std::string&  date);
        void            setAuthor(dbo::ptr<author>  authorPtr);
        void            addQuote();
        
    private:
        // the smart db pointer incase of working with an existing quote
        dbo::ptr<quote>     _dbPtr;

        // a quote object in case of dealing with a new quote that isn't in the
        // database yet
        quote       *newQuote_;

        Wt::Dbo::SqlConnectionPool&     _connectionPool;
        kalematieSession                _session;
        Wt::Dbo::Transaction            _transaction;

};
#endif  
