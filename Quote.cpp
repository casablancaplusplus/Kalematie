#include "Quote.h"


Quote::Quote(Wt::Dbo::SqlConnectionPool&    connPool)
    : _dbPtr(),
    _session(connPool),
    _transaction(_session)

{
}
Quote::~Quote() {}

//Used to inialize the _dbPtr using the quotes id
bool    Quote::initWithQuoteId(int  quoteId)
{

    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<quote>().where("id = ? ").bind(quoteId);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::initWithQuoteID()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = _session.find<quote>().where("id = ? ").bind(quoteId);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::initWithQuoteId() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;


}

bool    Quote::initWithQuoteText(std::string    text)
{
    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<quote>().where("text = ? ").bind(text);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::initWithQuoteText()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr = _session.find<quote>().where("text = ? ").bind(text);
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::initWithQuoteText() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::setDbPtr(dbo::ptr<quote>&     ptr)
{

    if(_dbPtr)
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

int     Quote::getId() {
    // check if _dbPtr is null
    if(_dbPtr) return -1;
    else
        return _dbPtr.id();
}

std::string     Quote::getText() {
    // check if _dbPtr is null
    if(_dbPtr) return "";
    else
        return _dbPtr->text;
}

Wt::WDateTime       Quote::getDatePublished() {
    // check if _dbPtr is null
    if(_dbPtr) return  Wt::WDateTime();
    else
        _dbPtr -> date_published;
}

float   Quote::getRating() {
    if(_dbPtr) return -1;
    else
        return _dbPtr -> rating;
}

int     Quote::getViewers() {
    if(_dbPtr)  return -1;
    else
        return _dbPtr -> viewers;
}

bool    Quote::getVerificationStatus() {
    if(!_dbPtr) return _dbPtr->verified;
}

dbo::ptr<author>   Quote::getAuthor() {
    if(_dbPtr) return dbo::ptr<author>();
    else
        return _dbPtr -> Author;
}

dbo::ptr<quote>&    Quote::getDbPtr() {

    return _dbPtr;
}

bool    Quote::updateText(std::string   _text) {

    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> text = _text;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateText()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> text = _text;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateText() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::updateDatePublished(Wt::WDateTime  date) {

    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> date_published = date;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateDatePublished()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> date_published = date;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateDatePublished() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::updateRating() {
   
    std::cout << "NOT IMPLEMENTED : update Overall rating is not implemented yet" <<std::endl;
    // TODO implement this later
    return false;

}

bool    Quote::updateViewers() {


    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> viewers++;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateViewers()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> viewers++;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateViewers() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::updateVerificationStatus(bool    tOrf) {

    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> verified = tOrf;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateVerificationStatus()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> verified = tOrf;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateVerificationStatus() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::updateAuthor(dbo::ptr<author>&   authorPtr) {


    if(_dbPtr)
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> Author = authorPtr;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateAuthor()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> Author = authorPtr;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateAuthor() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::commit() {
    
    try {
        if(_transaction.isActive()) std::cout << "\n\n\nIs Active\n\n\n" ;
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

void    Quote::initNewQuote() {
    newQuote_ = new quote();
}

void    Quote::setText(std::string  text) {

    newQuote_ -> text = text;

}

void    Quote::setDatePublished(Wt::WDateTime&   date) {

    newQuote_ -> date_published = date;

}

void    Quote::setAuthor(dbo::ptr<author>    authorPtr) {
    
    newQuote_ -> Author = authorPtr;

}

void    Quote::addQuote() {

    _dbPtr = _session.add(newQuote_);

}


