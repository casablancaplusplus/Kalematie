#include "quoteResBase.h"
#include "dbo/kalematieSession.h"

quoteResBase::quoteResBase(Wt::Dbo::SqlConnectionPool&  connPool)
    :_connectionPool(connPool)
    {
        kalematieSession    session(_connectionPool);
        session.mapTheClasses();
    }


void    quoteResBase::handleRequest(
        const   Wt::Http::Request&  request,
        Wt::Http::Response&         response
        )
{
    quoteResource   res(_connectionPool,request,response);
}

