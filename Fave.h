#ifndef     _FAVE_H_
#define     _FAVE_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"

#include <Wt/Dbo/SqlConnectionPool>

typedef     dbo::collection<dbo::ptr<fave> >    fPtrCollection;
class   Fave {

    public:
        Fave(Wt::Dbo::SqlConnectionPool&    connPool);
        ~Fave();

        template<class  T>
            T   query(std::string   qStr)
            {
                if(_transaction.isActive())
                {
                    try {
                        T   result = _session.query<T>(qStr);
                        return result;
                    }catch(Wt::Dbo::Exception&  e) {
                        std::cout << e.what() << std::endl;
                        return T();
                    }catch(...){
                        std::cout << "Fave::query()" << std::endl;
                        return T();
                    }
                }
                else
                {
                    Wt::Dbo::Transaction    t(_session);
                    try{
                        T   result = _session.query<T>(qStr);
                        t.commit();
                        return result;
                    }catch(Wt::Dbo::Exception&  e) {
                        std::cout << e.what() << std::endl;
                        return T();
                    }catch(...) {
                        std::cout << "Fave::query() " << std::endl;
                        return T();
                    }
                }
            }

        bool    initASingleFave(int quoteId, int    faverId);

        bool    initWithFaverId(int faverId);
        bool    initWithQuoteId(int quoteId);
        
        void    setDbPtr(dbo::ptr<fave>&    ptr);
        void    setDbPtrCollection(fPtrCollection&  ptrColl);

        dbo::ptr<fave>&   getDbPtr();
        fPtrCollection&     getDbPtrCollection();

        bool    commit();

        void    initNewFave();
        void    setFaverId(int  faverId);
        void    setQuoteId(int  quoteId);

        void    addFave();

    private:
        dbo::ptr<fave>      _dbPtr;
        fPtrCollection      _dbPtrCollection;
        fave                *newFave_;

        kalematieSession        _session;
        Wt::Dbo::Transaction    _transaction;
};

#endif


