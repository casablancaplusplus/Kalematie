#ifndef     _AUTHOR_H_
#define     _AUTHOR_H_

#include "dbo/dbo.h"
#include "dbo/kalematieSession.h"
#include <Wt/Dbo/SqlConnectionPool>

class   Author {

    public:
        Quote(Wt::Dbo::SqlConnectionPool&   connectionPool);
        
        void            initWithAuthorId(int        authorId);
        void            initWithNickName(std::sting nickName);
        void            initWithPhoneNum(std::string    phoneNumber);
        void            setDbPtr(dbo::ptr<author>&  ptr); // initialize using an existing ptr

        int             getId();
        std::string     getFirstName();
        std::string     getLastName();
        std::string     getNickName();
        std::string     getPhoneNumber();
        std::string     getPassword();
        float           getRating();
        int             getFollowers();
        int             getFollowing();
        author::role    getRole();
        dbo::collection<dbo::ptr<quotes> >      getQuoteCollection();
        dbo::ptr<author>    getDbPtr(); // returns the smart pointer itself
       

        void            updateFirstName(std::string     firstname);
        void            updateLastName(std::string      lastname);
        void            updateNickName(std::string      nickname);
        void            updatephoneNumber(std::string   phonenumber);
        void            updatePassword(std::string      password);
        void            updateRating(float              rating);
        void            updateFollowers();
        void            updateFollowing();
        void            updateRole(author::role     Role);

        void            commit(); // persists a new author or the modifications of an existing author
        
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
