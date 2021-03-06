#include <Wt/WServer>
#include <Wt/Dbo/SqlConnectionPool>


#include "dbo/kalematieSession.h"
#include "quoteResBase.h"

#include <locale>

int main(int    argc, char  **argv) {
    
    std::locale::global(std::locale("en_US.UTF8"));
    try{
        Wt::WServer server(argv[0], "");

        try{
            server.setServerConfiguration(argc,argv);
            Wt::Dbo::SqlConnectionPool  *quoteDb
                = kalematieSession::createConnectionPool(server.appRoot() +
                        "quoteDb.db");
            quoteResBase   res(*quoteDb);
            server.addResource(&res, "/api");

            try{
                server.start();
                Wt::WServer::waitForShutdown();
                server.stop();
            }catch(Wt::WServer::Exception&  e) {
                std::cout << e.what() << std::endl;
                return 1;
            }

            return 0;
        }catch(Wt::WServer::Exception&  e) {
            std::cout << e.what() << std::endl;
            return 1;
        }catch(std::exception&  e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }catch(Wt::WServer::Exception&  e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

