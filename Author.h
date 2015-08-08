#ifndef     _AUTHOR_H_
#define     _AUTHOR_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"
#include <Wt/Dbo/SqlConnectionPool>

class   Author {

    public:
        Author(Wt::Dbo::SqlConnectionPool&   connectionPool);
        ~Author();

        int             getAuthorCount();

        bool            initWithAuthorId(int        authorId);
        bool            initWithNickName(std::string nickName);
        bool            setDbPtr(dbo::ptr<author>&  ptr); // initialize using an existing ptr

        int             getId();
        std::string     getNickName();
        double           getRating();
        int             getFollowers();
        int             getFollowing();

        // do a manual null check for _dbPtr before calling this method
        author::role    getRole();
        dbo::collection<dbo::ptr<quote> >      getQuoteCollection();
        dbo::ptr<author>&    getDbPtr(); // returns the smart pointer itself
        const dbo::weak_ptr<credentials>&  getCredentials(); 

        bool            updateNickName(std::string      nickname);
        bool            updateRating();
        bool            updateFollowers();
        bool            updateFollowing();
        bool            updateRole(author::role     Role);
        bool            updateCredentials(dbo::weak_ptr<credentials>&   cred);

        bool            commit(); // persists a new author or the modifications of an existing author
        
        void            initNewAuthor();
        void            setNickName(std::string         nickname);
        void            setRole(author::role            Role);
        void            setCredentials(dbo::weak_ptr<credentials>&  cred);
        // this method should add the author to the db and if successful
        // it should inialize the _dbPtr property with the returned ptr
        void            addAuthor();
    private:
        // the smart db pointer incase of working with an existing author
        dbo::ptr<author>    _dbPtr;

        // an author object in case of dealing with a new quote that isn't in the
        // database yet
        author              *newAuthor_;

        //Wt::Dbo::SqlConnectionPool&     _connectionPool;
        kalematieSession                _session;
        Wt::Dbo::Transaction            _transaction;
};
#endif  
