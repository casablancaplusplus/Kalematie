#ifndef     _KALEMATIE_SESSION_H_
#define     _KALEMATIE_SESSION_H_

#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>

namespace dbo = Wt::Dbo;

class kalematieSession : public dbo::Session
{
    public:
        
        kalematieSession(dbo::SqlConnectionPool& connectionPool);
        
        static dbo::SqlConnectionPool *createConnectionPool(
                const std::string& sqlite3);

    private:
        dbo::SqlConnectionPool& connectionPool_;
};

#endif 
