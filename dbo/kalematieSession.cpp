#include <Wt/Dbo/FixedSqlConnectionPool>

#include "kalematieSession.h"
#include "dbo.h"

kalematieSession::kalematieSession(dbo::SqlConnectionPool& connectionPool)
    :connectionPool_(connectionPool)
{
    setConnectionPool(connectionPool_);
    
    mapClass<quote>("quote");
    mapClass<author>("author");
    mapClass<rating>("rating");
    mapClass<following>("following");
    mapClass<accessToken>("accessToken");

    try {
        dbo::Transaction t(*this);
        this->createTables();
        t.commit();
    }catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using existing database";
    }
}

dbo::SqlConnectionPool  *kalematieSession::createConnectionPool(
        const std::string& sqliteDb)
{
    dbo::backend::Sqlite3   *connection = new dbo::backend::Sqlite3(sqliteDb);

    connection->setProperty("show-queries", "true");
    connection->setDateTimeStorage(Wt::Dbo::SqlDateTime,
            Wt::Dbo::backend::Sqlite3::PseudoISO8601AsText);

    return new dbo::FixedSqlConnectionPool(connection, 10);
}

