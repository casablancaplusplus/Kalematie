#include "Credentials.h"



Credentials::Credentials(Wt::Dbo::SqlConnectionPool&    connPool)
    :   _dbPtr(),
        _connectionPool(connPool),
        _session(connPool),
        _transaction(_session)
{
}
Credentials::~Credentials() {}


bool    Credentials::initWithEmail(std::string      email) {
    if(!_dbPtr.get())
    {
        if(_transaction.isActive()) {
            try {
                _dbPtr = _session.find<credentials>().where("email = ?").bind(email);
                if(_dbPtr.get()) return true;
                else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::initWithEmail()" << std::endl;
                return false;
            }
        } else {
            Wt::Dbo::Transaction    t(_session);
            try {
                _dbPtr = _session.find<credentials>().where("email = ?").bind(email);
                if(_dbPtr.get()) {
                    t.commit();
                    return true;
                } else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::initWithEmail()" << std::endl;
                return false;
            }
        }
    } else return false;
}

bool    Credentials::initWithPhoneNumber(std::string    phone) {
    if(!_dbPtr.get())
    {
        if(_transaction.isActive()) {
            try {
                _dbPtr = _session.find<credentials>().where("phoneNumber = ?").bind(phone);
                if(_dbPtr.get()) return true;
                else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::initWithPhoneNumber()" << std::endl;
                return false;
            }
        } else {
            Wt::Dbo::Transaction    t(_session);
            try {
                _dbPtr = _session.find<credentials>().where("phoneNumber = ?").bind(phone);
                if(_dbPtr.get()) {
                    t.commit();
                    return true;
                } else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::initWithPhoneNumber()" << std::endl;
                return false;
            }
        }
    } else return false;
}

bool    Credentials::setDbPtr(dbo::ptr<credentials>&    ptr) {
    if(!_dbPtr.get())
    {
        if(_transaction.isActive()) {
            try {
                _dbPtr = ptr; 
                if(_dbPtr.get()) return true;
                else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::setDbPtr()" << std::endl;
                return false;
            }
        } else {
            Wt::Dbo::Transaction    t(_session);
            try {
                _dbPtr = ptr;
                if(_dbPtr.get()) {
                    t.commit();
                    return true;
                } else return false;
            }catch(Wt::Dbo::Exception&  e) {
                std::cout << e.what() << std::endl;
                return false;
            }catch(...) {
                std::cout << "Source: Credentials::setDbPtr()" << std::endl;
                return false;
            }
        }
    } else return false;
}

int     Credentials::getId() {
    if(!_dbPtr.get()) return -1;
    else              return _dbPtr.id();
}

std::string     Credentials::getEmail() {
    if(!_dbPtr.get())   return "";
    else    return  _dbPtr->email;
}

std::string     Credentials::getPhoneNumber() {
    if(!_dbPtr.get())   return "";
    else    return  _dbPtr->phoneNumber;
}

std::string     Credentials::getPassword() {
    if(!_dbPtr.get())   return "";
    else    return  _dbPtr->password;
}

dbo::ptr<author>   Credentials::getAuthor() {
    try {
        return  _dbPtr -> Author;
    } catch( Wt::Dbo::Exception&    e) {
        std::cout << e.what() << std::endl;
        return  dbo::ptr<author>();
    }
}

dbo::ptr<credentials>& Credentials::getDbPtr() {
    return  _dbPtr;
}

bool    Credentials::commit() {
    if(_transaction.isActive()) {
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
    } else return true; // suspicious
}

void    Credentials::initNewCredentials() {
    newCredentials_ = new credentials();
}

void    Credentials::setEmail(std::string    _email) {
    newCredentials_ -> email = _email;
}

void    Credentials::setPhoneNumber(std::string     phone) {
    newCredentials_ -> phoneNumber = phone;
}

void    Credentials::setPassword(std::string    pass) {
    newCredentials_ -> password = pass;
}

void    Credentials::setAuthor(dbo::ptr<author>&    author) {
    newCredentials_ -> Author = author;
}

void    Credentials::addCredentials() {
    if(_transaction.isActive()) 
        _dbPtr = _session.add(newCredentials_);
    else {
        dbo::Transaction    t(_session);
        _dbPtr = _session.add(newCredentials_);
    }
}
