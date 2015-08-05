#include "Fave.h"


Fave::Fave(Wt::Dbo::SqlConnectionPool&      connPool)
    :   _dbPtr(),
    _session(connPool),
    _transaction(_session)
{
}

Fave::~Fave() {}


bool    Fave::initASingleFave(int   quoteId, int    faverId)
{


    if(_transaction.isActive())
    {
        try{
            _dbPtr = _session.find<fave>().where("quoteId = ? and faverId = ?")
                .bind(quoteId).bind(faverId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Fave::initASingleFave()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtr = _session.find<fave>().where("quoteId = ? and faverId = ?")
                .bind(quoteId).bind(faverId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Fave::initASingleFave()" << std::endl;
            return false;
        }
    }
}

bool    Fave::initWithFaverId(int   faverId)
{

    if(_transaction.isActive())
    {
        try{
            _dbPtrCollection = _session.find<fave>().where("faverId = ?")
                .bind(faverId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Fave::initWithFaverId()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtrCollection = _session.find<fave>().where("faverId = ?")
                .bind(faverId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Fave::initWithFaverId()" << std::endl;
            return false;
        }
    }
}

bool    Fave::initWithQuoteId(int   quoteId)
{

    if(_transaction.isActive())
    {
        try{
            _dbPtrCollection = _session.find<fave>().where("quoteId = ?")
                .bind(quoteId);
            return  true;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source:   Fave::initWithQuoteId()" << std::endl;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try{
            _dbPtrCollection = _session.find<fave>().where("quoteId = ?")
                .bind(quoteId);
            t.commit();
            return  true;
        }catch(Wt::Dbo::Exception&   e) {
            std::cout << e.what() << std::endl;
            return false;
        }catch(...) {
            std::cout << "Source: Fave::initWithQuoteId()" << std::endl;
            return false;
        }
    }
}

void    Fave::setDbPtr(dbo::ptr<fave>&    ptr)
{
    _dbPtr = ptr;
}

void    Fave::setDbPtrCollection(fPtrCollection&  ptrColl)
{
    _dbPtrCollection = ptrColl;
}

dbo::ptr<fave>&   Fave::getDbPtr() {
    
    return _dbPtr;
}

fPtrCollection&     Fave::getDbPtrCollection()
{
    return _dbPtrCollection;
}

bool        Fave::commit() {
    try{
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

void    Fave::initNewFave() {
    newFave_ = new fave();
}

void    Fave::setFaverId(int    _faverId)
{
    newFave_-> faverId = _faverId;
}

void    Fave::setQuoteId(int    _quoteId)
{
    newFave_-> quoteId = _quoteId;
}

void    Fave::addFave()
{
    _dbPtr = _session.add(newFave_);
}
