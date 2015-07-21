#include "Author.h"


Author::Author(Wt::Dbo::SqlConnectionPool&  connectionPool) 
    : _dbPtr(),
    _session(connectionPool),
    _transaction(_session)

{
}

Author::~Author() {}
bool    Author::initWithAuthorId(int    authorId)
{
    //if(!_dbPtr.get())
   // {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<author>().where("id = ? ").bind(authorId);
                return true;
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
                return true;
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
                return true;
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


bool    Author::initWithPhoneNum(std::string    phoneNum)
{
    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<author>().where("phoneNumber = ? ").bind(phoneNum);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithPhoneNum()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = _session.find<author>().where("phoneNumber = ? ").bind(phoneNum);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::initWithPhoneNum() " << std::endl;
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

std::string     Author::getFirstName() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr->firstName;
}

std::string     Author::getLastName() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr->lastName;
}

std::string     Author::getNickName() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr-> nickName;
}

std::string     Author::getPhoneNumber() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr->phoneNumber;
}

std::string     Author::getPassword() {

    if(!_dbPtr.get()) return "";
    else
        return _dbPtr->password;

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

bool    Author::updateFirstName(std::string     firstname) {
    
    
    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> firstName = firstname;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFirstName()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> firstName = firstname;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateFirstName() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Author::updateLastName(std::string      lastname) {

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> lastName = lastname;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateLastName()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> lastName = lastname;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updateLastName() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
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

bool    Author::updatePhoneNumber(std::string   phonenum) {

    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> phoneNumber = phonenum;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updatePhoneNumber()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> phoneNumber = phonenum;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updatePhoneNumber() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Author::updatePassword(std::string  _password) {


    if(!_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> password = _password;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updatePassword()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> password = _password;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Author::updatePassword() " << std::endl;
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

void    Author::setFirstName(std::string    firstname) {

    newAuthor_ -> firstName = firstname;
}

void    Author::setLastName(std::string     lastname) {

    newAuthor_ -> lastName = lastname;
}

void    Author::setNickName(std::string     nickname) {

    newAuthor_ -> nickName = nickname;
}

void    Author::setPhoneNumber(std::string  phonenum) {

    newAuthor_ -> phoneNumber = phonenum;

}

void    Author::setPassword(std::string     _password) {

    newAuthor_ -> password = _password;

}

void    Author::setRole(author::role        Role) {

    newAuthor_ -> authorRole = Role;
}

void    Author::addAuthor() {

    _dbPtr = _session.add(newAuthor_);
}
