#include "Quote.h"


Quote::Quote(Wt::Dbo::SqlConnectionPool&    connPool)
    : _dbPtr(),
    _connectionPool(connPool),
    _session(connPool),
    _transaction(_session)

{
}
Quote::~Quote() {}



int     Quote::getQuoteCount() 
{
    int     count = 0;
    if(_transaction.isActive())
    {
        try{
            count = _session.query<int>("select count(*) from quote");
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
            count = _session.query<int>("select count(*) from quote");
            t.commit();
            return count;
        }catch(Wt::Dbo::Exception&  e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }
    return count;

}


//Used to inialize the _dbPtr using the quotes id
bool    Quote::initWithQuoteId(int  quoteId)
{

    //if(!_dbPtr.get())
    //{
        if(_transaction.isActive())
        {
            try{
                _dbPtr = _session.find<quote>().where("id = ? ").bind(quoteId);
                if(_dbPtr.get())
                    return true;
                else return false;
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
   // }
   // else
    //    return false;


}

bool    Quote::initWithQuoteText(std::string    text)
{
    if(!_dbPtr.get())
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

int     Quote::getId() {
    // check if _dbPtr is null
    if(!_dbPtr.get()) return -1;
    else
        return _dbPtr.id();
}

std::string     Quote::getText() {
    // check if _dbPtr is null
    if(!_dbPtr.get()) return "";
    else
        return _dbPtr->text;
}

std::string       Quote::getDatePublished() {
    // check if _dbPtr is null
    if(!_dbPtr.get()) return std::string();
    else
        return _dbPtr -> date_published;

}

double   Quote::getRating() {
 
    if(!_dbPtr.get()) return -1;
    else
        return _dbPtr -> rating;
}

int     Quote::getViewers() {
    if(!_dbPtr.get())  return -1;
    else
        return _dbPtr -> viewers;
}

int     Quote::getFaves() {

    if(!_dbPtr.get())   return -1;
    else
        return  _dbPtr -> faves;
}

int     Quote::getOriginality() {
    if(!_dbPtr.get())   return  -1;
    else
        return  _dbPtr -> originality;
}

bool    Quote::getVerificationStatus() {
    if(!_dbPtr) return _dbPtr->verified;
}

dbo::ptr<author>   Quote::getAuthor() {
       try { 

            return _dbPtr -> Author;

       }catch(Wt::Dbo::Exception&   e) {
           std::cout << e.what() << std::endl;
           return dbo::ptr<author>();
       }
}

dbo::ptr<quote>&    Quote::getDbPtr() {

    return _dbPtr;
}

bool    Quote::updateText(std::string   _text) {

    if(_dbPtr.get())
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

bool    Quote::updateDatePublished(std::string&  date) {

    if(!_dbPtr.get())
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
  
    if(_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                Rating      *rating_ = new Rating(_connectionPool);
                rating_-> initWithQuoteId(_dbPtr.id());
                std::vector<double>     ratings = rating_-> getRatings();
                rating_->commit();
                if(ratings.empty())
                {
                    _dbPtr.modify() -> rating = -1;
                    return true;
                }
                else
                {
                    std::map<double, int>   ratingMap;
                    for(double  d = 0.0; d <= 10.0; d+=0.1)
                        ratingMap[d] = 0;

                    for(std::vector<double>::const_iterator it = ratings.begin();
                            it != ratings.end(); it++)
                        ratingMap[*it]++;

                    int wAll = 0;
                    double  wSum = 0.0;
                    for(const auto &pair : ratingMap)
                        if(pair.second != 0)
                        {
                            wAll++;
                            wSum += pair.first * pair.second;
                        }
                    double  result = wSum/wAll;

                    _dbPtr.modify() -> rating = result;
                    return true;
                }
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateRating()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                Rating      *rating_ = new Rating(_connectionPool);
                rating_-> initWithQuoteId(_dbPtr.id());
                std::vector<double>     ratings = rating_-> getRatings();
                rating_->commit();
                if(ratings.empty())
                {
                    _dbPtr.modify() -> rating = -1;
                    return true;
                }
                else
                {
                    std::map<double, int>   ratingMap;
                    for(double  d = 0.0; d <= 10.0; d+=0.1)
                        ratingMap[d] = 0;

                    for(std::vector<double>::const_iterator it = ratings.begin();
                            it != ratings.end(); it++)
                        ratingMap[*it]++;

                    int wAll = 0;
                    double  wSum = 0.0;
                    for(const auto &pair : ratingMap)
                        if(pair.second != 0)
                        {
                            wAll++;
                            wSum += pair.first * pair.second;
                        }
                    double  result = wSum/wAll;

                    _dbPtr.modify() -> rating = result;
                    t.commit();
                    return true;
                }
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateRating()" << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}


bool    Quote::updateViewers() {


    if(_dbPtr.get())
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

bool    Quote::updateFaves() {


    if(_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> faves++;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateFaves()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> faves++;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateFaves() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}

bool    Quote::updateOriginality() {

    if(_dbPtr.get())
    {
        if(_transaction.isActive())
        {
            try{
                _dbPtr.modify() -> originality++;
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateOriginality()" << std::endl;
                return false;
            }
        }
        else
        {
            Wt::Dbo::Transaction    t(_session);
            try{
                _dbPtr.modify() -> originality++;
                t.commit();
                return true;
            }catch(Wt::Dbo::Exception&  e){
                std::cout << e.what() << std::endl;
                return false;
            }catch(...){
                std::cout << "Source: Quote::updateOriginality() " << std::endl;
                return false;
            }
        }
    }
    else
        return false;
}


bool    Quote::updateVerificationStatus(bool    tOrf) {

    if(_dbPtr.get())
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


    if(!_dbPtr.get())
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
    if(_transaction.isActive())
    {
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
    else
        return true; // suspicious

}

void    Quote::initNewQuote() {
    newQuote_ = new quote();
}

void    Quote::setText(std::string  text) {

    newQuote_ -> text = text;

}

void    Quote::setDatePublished(std::string&   date) {

    newQuote_ -> date_published = date;

}

void    Quote::setAuthor(dbo::ptr<author>    authorPtr) {
    
    newQuote_ -> Author = authorPtr;

}

void    Quote::addQuote() {

    _dbPtr = _session.add(newQuote_);

}

void    Quote::remove() {

    if(_dbPtr.get()) _dbPtr.remove();
}
