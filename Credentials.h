#ifndef     _CREDENTIALS_H_
#define     _CREDENTIALS_H_


#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"

#include <Wt/Dbo/SqlConnectionPool>

class   Credentials {
    public:
        Credentials(Wt::Dbo::SqlConnectionPool& connPool);
        ~Credentials();

        bool    initWithEmail(std::string   email);
        bool    initWithPhoneNumber(std::string phone);
        bool    setDbPtr(dbo::ptr<credentials>& ptr);

        int     getId();
        std::string     getEmail();
        std::string     getPhoneNumber();
        std::string     getPassword();
        dbo::ptr<author>   getAuthor();
        dbo::ptr<credentials>&  getDbPtr();

        bool    commit();

        void    initNewCredentials();
        void    setEmail(std::string    email);
        void    setPhoneNumber(std::string  phone);
        void    setPassword(std::string pass);
        void    setAuthor(dbo::ptr<author>& author);

        void    addCredentials();

    private:
        dbo::ptr<credentials>   _dbPtr;

        credentials     *newCredentials_;

        Wt::Dbo::SqlConnectionPool&     _connectionPool;
        kalematieSession                _session;
        Wt::Dbo::Transaction            _transaction;
};
#endif      
