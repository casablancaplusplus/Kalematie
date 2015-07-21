#ifndef     _AUTHOR_H_
#define     _AUTHOR_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"
#include <Wt/Dbo/SqlConnectionPool>

class   Author {

    public:
        Author(Wt::Dbo::SqlConnectionPool&   connectionPool);
        ~Author();
        bool            initWithAuthorId(int        authorId);
        bool            initWithNickName(std::string nickName);
        bool            initWithPhoneNum(std::string    phoneNumber);
        bool            setDbPtr(dbo::ptr<author>&  ptr); // initialize using an existing ptr

        int             getId();
        std::string     getFirstName();
        std::string     getLastName();
        std::string     getNickName();
        std::string     getPhoneNumber();
        std::string     getPassword();
        double           getRating();
        int             getFollowers();
        int             getFollowing();

        // do a manual null check for _dbPtr before calling this method
        author::role    getRole();
        dbo::collection<dbo::ptr<quote> >      getQuoteCollection();
        dbo::ptr<author>&    getDbPtr(); // returns the smart pointer itself
       

        bool            updateFirstName(std::string     firstname);
        bool            updateLastName(std::string      lastname);
        bool            updateNickName(std::string      nickname);
        bool            updatePhoneNumber(std::string   phonenumber);
        bool            updatePassword(std::string      password);
        bool            updateRating();
        bool            updateFollowers();
        bool            updateFollowing();
        bool            updateRole(author::role     Role);

        bool            commit(); // persists a new author or the modifications of an existing author
        
        void            initNewAuthor();
        void            setFirstName(std::string        firstname);
        void            setLastName(std::string         lastname);
        void            setNickName(std::string         nickname);
        void            setPhoneNumber(std::string      phonenumber);
        void            setPassword(std::string         password);
        void            setRole(author::role            Role);
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
