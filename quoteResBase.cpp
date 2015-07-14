#include "quoteResBase.h"

quoteResBase::quoteResBase(Wt::Dbo::SqlConnectionPool&  connPool)
    :_connectionPool(connPool)
    {
    }


void    quoteResBase::handleRequest(
        const   Wt::Http::Request&  request,
        Wt::Http::Response&         response
        )
{
    quoteResource   res(_connectionPool,request,response);
}

