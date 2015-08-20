#include "Author.h"


Author::Author(Wt::Dbo::SqlConnectionPool&  connectionPool) 
    : _dbPtr(),
    _session(connectionPool),
    _transaction(_session)

{
}

Author::~Author() {}

int     Author::getAuthorCount() 
{
    int     count = 0;
    if(_transaction.isActive())
    {
        try{
            count = _session.query<int>("select count(*) from author");
            return count;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }
    else
    {
        Wt::Dbo::Transaction    t(_session);
        try {
            count = _session.query<int>("select count(*) from author");
            return count;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }
    return count;
}


bool    Author::initWithAuthorId(int    authorId)
{
    //if(!_dbPtr.get())
   // {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<author>().where("id = ? ").bind(authorId);
                if(_dbPtr.get())
                    return true;
                else    return false;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithAuthorId()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = _session.find<author>().where("id = ? ").bind(authorId);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithAuthorId() " << std::endl;
                return false;
            }
        }
   // }
    //else
     //   return false;
}

bool    Author::initWithNickName(std::string    nickName)
{
    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<author>().where("nickName = ? ").bind(nickName);
                if(_dbPtr.get())    return true;
                else                return false;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithNickName()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = _session.find<author>().where("nickName = ? ").bind(nickName);
                if(_dbPtr.get())    return true;
                else                return false;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithNickName() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}


bool    Author::setDbPtr(dbo::ptr<author>&  ptr) 
{

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = ptr;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::setDbPtr()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = ptr; 
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::setDbPtr() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

int     Author::getId() {
    // check if _dbPtr is null
    if(!_dbPtr.get()) return 0;
    else
        return _dbPtr.id();
}


std::string     Author::getNickName() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr-> nickName;
}

double       Author::getRating() {
    
    if(!_dbPtr.get()) return  -1;
    else
        return _dbPtr->rating;
}

int         Author::getFollowers() {

    if(!_dbPtr.get()) return -1;
    else
        return  _dbPtr->followers;
}
   
int         Author::getFollowing() {
    if(!_dbPtr.get()) return -1;
    else
        return _dbPtr->following;
}

author::role    Author::getRole() {
    if(!_dbPtr)  return _dbPtr->authorRole;
}

dbo::collection<dbo::ptr<quote> >   Author::getQuoteCollection() {

    // if _dbPtr is null return an empty collection
    if(!_dbPtr.get())  return  dbo::collection<dbo::ptr<quote> >();
    else
        return  _dbPtr -> quotes;
}

dbo::ptr<author>&    Author::getDbPtr(){

    return  _dbPtr;
}

dbo::collection<dbo::ptr<credentials> >  Author::getCredentials() {

        if(_transaction.isActive())
        {
             return  _dbPtr->Credentials;
        }
        else
        {
            dbo::Transaction    t(_session);
            return  _dbPtr->Credentials;
        }
}
bool    Author::updateNickName(std::string      nickname) {

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> nickName = nickname;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateNickName()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> nickName = nickname;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateNickName() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}


bool    Author::updateRating() {

    std::cout << "NOT IMPLEMENTED : updating a users rating is not implemented yet"
        << std::endl;

    return false;
}

bool    Author::updateFollowers() {

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> followers++;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFollowers()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> followers++;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFollowers() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}


bool    Author::updateFollowing() {

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> following++;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFollowing()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> following++;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFollowing() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Author::updateRole(author::role     Role) {


    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> authorRole = Role;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateRole()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> authorRole = Role;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateRole() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}
/*
bool    Author::updateCredentials(dbo::weak_ptr<credentials>&   creds)
{
    // TODO you probably should invalidate any access token with the 
    // previous credentials after this operation
    
    if(_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> Credentials = creds;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateCredentials()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> Credentials = creds; 
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateCredentials() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}
*/

bool    Author::commit() {
    
    try {

        _transaction.commit();
        return true;
    }catch(Wt::Dbo::Exception&  e) {
        std::cout << e.what() << std::endl;
        return false;
    }catch(std::exception&  e) {
        std::cout << e.what() << std::endl;
        return false;
    }

}


void    Author::initNewAuthor() {

    newAuthor_ = new author();

}

void    Author::setNickName(std::string     nickname) {

    newAuthor_ -> nickName = nickname;
}


void    Author::setRole(author::role        Role) {

    newAuthor_ -> authorRole = Role;
}
/*
void    Author::setCredentials(dbo::weak_ptr<credentials>&  creds)
{
    if(_transaction.isActive())
        newAuthor_ -> Credentials = creds;
    else
    {
        dbo::Transaction    t(_session);
        newAuthor_ -> Credentials = creds;
        t.commit();
    }
}
*/
void    Author::addAuthor() {
    if(_transaction.isActive())
        _dbPtr = _session.add(newAuthor_);
    else {
        dbo::Transaction    t(_session);
        _dbPtr = _session.add(newAuthor_);
    }
}
