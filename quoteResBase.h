#ifndef     _QUOTE_RES_BASE_H_
#define     _QUOTE_RES_BASE_H_


#include <Wt/WResource>
#include <Wt/Dbo/SqlConnectionPool>

#include "quoteResource.h"

class quoteResBase : public Wt::WResource {


    public:
        quoteResBase(Wt::Dbo::SqlConnectionPool&    connectionPool);


    protected:
        virtual void    handleRequest(
                const   Wt::Http::Request&  request,
                Wt::Http::Response&         response
                );
    private:
        Wt::Dbo::SqlConnectionPool&     _connectionPool;
};

#endif  
