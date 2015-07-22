#ifndef     _RATING_H_
#define     _RATING_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"

#include <Wt/Dbo/SqlConnectionPool>

#include <vector>

typedef     dbo::collection<dbo::ptr<rating> >  rPtrCollection;

class   Rating {

    public:
        Rating(Wt::Dbo::SqlConnectionPool&  connPool);
        ~Rating();
        
        // used to manipulate a single rating
        // this function tries to fetch the rating
        // and assign it to _dbPtr and return true But if the rating
        // doesn't exist, it instead initialized the
        // newRating_ property and returns false;
        bool        initASingleRating(int   quoteId, int    raterId);

        bool        initWithRaterId(int raterId);
        bool        initWithQuoteId(int quoteId);
        bool        initWithRating(double    rating);
        void        setDbPtr(dbo::ptr<rating>&  ptr);
        void        setDbPtrCollection(rPtrCollection&  ptrColl);
        
        //int         getQuoteId();
        //int         getRaterId();
        double       getRating(dbo::ptr<rating>& ptr);
        std::vector<double>  getRatings();
        dbo::ptr<rating>&   getDbPtr();
        dbo::collection<dbo::ptr<rating> >  getDbPtrCollection();
        
        // This function operates on _dbPtr
        bool        updateRating(int    rating);
        
        bool        commit();

        void        initNewRating();
        void        setQuoteId(int  quoteId);
        void        setRaterId(int  raterId);
        void        setRating(double rating);
        
        void        addRating();

    private:
        dbo::ptr<rating>    _dbPtr; // when dealing with a single rating
        rPtrCollection  _dbPtrCollection; // when dealing with a bunch of ratings
        rating      *newRating_;

        kalematieSession        _session;
        Wt::Dbo::Transaction    _transaction;

};

#endif  
