#include "Rating.h"


Rating::Rating(Wt::Dbo::SqlConnectionPool&  connPool)
    :   _dbPtr(),
    _session(connPool),
    _transaction(_session)
{
}

Rating::~Rating() {}

bool    Rating::initASingleRating(int   quoteId, int    raterId)
{
    if(_transaction.isActive())
    {
        try{
            _dbPtr = _session.find<rating>().where("quoteId = ? and raterId = ?")
                .bind(quoteId).bind(raterId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Rating::initASingleRating()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtr = _session.find<rating>().where("quoteId = ? and raterId = ?")
                .bind(quoteId).bind(raterId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Rating::initASingleRating()" << std::endl;
            return false;
        }
    }
}

bool    Rating::initWithRaterId(int     raterId) 
{
    if(_transaction.isActive())
    {
        try{
            _dbPtrCollection = _session.find<rating>().where("raterId = ?").bind(raterId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Rating::initWithRaterId()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtrCollection = _session.find<rating>().where("raterId = ?").bind(raterId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Rating::initWithRaterId()" << std::endl;
            return false;
        }
    }
}

bool    Rating::initWithQuoteId(int     quoteId)
{

    if(_transaction.isActive())
    {
        try{
            _dbPtrCollection = _session.find<rating>().where("quoteId = ?").bind(quoteId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Rating::initWithQuoteId()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtrCollection = _session.find<rating>().where("quoteId = ?").bind(quoteId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Rating::initWithQuoteId()" << std::endl;
            return false;
        }
    }
}

bool    Rating::initWithRating(float    _rating)
{

    if(_transaction.isActive())
    {
        try{
            _dbPtrCollection = _session.find<rating>().where("rating = ?").bind(_rating);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Rating::initWithRating()" << std::endl;
        }
    }
    else
    {
         Wt::Dbo::Transaction    t(_session);
         try{
            _dbPtrCollection = _session.find<rating>().where("rating = ?").bind(_rating);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Rating::initWithRating()" << std::endl;
            return false;
        }
    }
}

void    Rating::setDbPtr(dbo::ptr<rating>&  ptr)
{

    if(_transaction.isActive())
    {
        _dbPtr = ptr;    
    }
    else
    {
         Wt::Dbo::Transaction    t(_session);
         _dbPtr = ptr;   
    }
}

void    Rating::setDbPtrCollection(rPtrCollection&  ptrColl)
{
    if(_transaction.isActive())
    {
        _dbPtrCollection = ptrColl;    
    }
    else
    {
         Wt::Dbo::Transaction    t(_session);
         _dbPtrCollection = ptrColl;   
    }
}

float   Rating::getRating(dbo::ptr<rating>& ptr) {
    if(ptr.get())    return  ptr->rating;
}

std::vector<float>  Rating::getRatings() {

    if(_dbPtrCollection.size() != 0)
    {
        std::vector<float>  ratingsVec;
        for(rPtrCollection::iterator  it = _dbPtrCollection.begin();
                it != _dbPtrCollection.end(); it++)
        {
            ratingsVec.push_back(getRating((*it)));
        }
    }
    else
    {
        return  std::vector<float>();
    }
}

dbo::ptr<rating>&   Rating::getDbPtr() {
    return _dbPtr;
}

dbo::collection<dbo::ptr<rating> >  Rating::getDbPtrCollection() 
{
    return  _dbPtrCollection;
}

bool    Rating::updateRating(int    _rating) 
{
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> rating = _rating;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateRating()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> rating = _rating;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateText() " << std::endl;
                return false;
            }
        }
}

bool    Rating::commit() {

    try {
        if(_transaction.isActive())
        {
            _transaction.commit();
            return true;
        }
        else    return false;
    }catch(Wt::Dbo::Exception&  e) {
        std::cout << e.what() << std::endl;
        return false;
    }catch(std::exception&  e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

void    Rating::initNewRating() {
    newRating_ = new rating();
}

void    Rating::setQuoteId(int  _quoteId) {

    newRating_-> quoteId = _quoteId;
}

void    Rating::setRaterId(int  _raterId) {

    newRating_-> raterId = _raterId;
}

void    Rating::setRating(float _rating) {

    newRating_-> rating = _rating;
}

void    Rating::addRating() {

    _dbPtr = _session.add(newRating_);
}
