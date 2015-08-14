#include "Token.h"

Token::Token(std::string    base64str)
    : _base64str(base64str),
      _accessToken(""),
      _username(""),
      _password("")
{

    std::string     decodedStr = Wt::Utils::base64Decode(_base64str);
    std::string::size_type  semiPos = decodedStr.find(':');
    if(semiPos != std::string::npos) {
        _username = decodedStr.substr(0, semiPos);
        _password = decodedStr.substr(semiPos+1, std::string::npos);
    }
}


bool    Token::createAccessToken(Wt::Dbo::SqlConnectionPool&    connPool) {
    /* dbug code
    std::cout << "________ in the create token function _____  " << std::endl;

    std::cout << "______ USERNAME : " << _username << std::endl;
    std::cout << "______ PASSWORD : " << _password << std::endl;
    */

    if(_username == "" || _password == "") return false;
    else if(_username == "guest" || _password == "guest") {
        try {
                // create and return the accessToken
                Wt::WDateTime   dateTime = Wt::WDateTime::currentDateTime();
                std::string     unixTimeAsStr = std::to_string(dateTime.toTime_t());
                std::string     rawString =
                    _username + ':' + _password + ":Masoume:" + unixTimeAsStr;
                _accessToken = Wt::Utils::sha1(rawString);
                _accessToken = Wt::Utils::base64Encode(_accessToken);
                // fetch the user info before commiting 
                author::role    role_ = author::role::Guest;
                try { 
                    // add it to the accessToken table
                    kalematieSession   _session(connPool);
                    dbo::Transaction        t(_session);

                    accessToken     *dbPtr_ = new accessToken();
 
                    dbPtr_ -> token = _accessToken;
                    dbPtr_ -> role  = role_;
                    dbPtr_ -> creationDate = unixTimeAsStr;

                    _session.add(dbPtr_);

                    t.commit();

                    return true;
                } catch(Wt::Dbo::Exception& e) {
                    std::cout << e.what() << std::endl;
                    return false;
                } catch(...) {
                    std::cout << "Something went wrong trying to register the token in the \
                        accessToken table" << std::endl;
                    return false;
                }
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return false;
            } catch(...) {
                std::cout << "Something went wrong trying to create the token string" << std::endl;
                return false;
            }
    }
    else {
        /* dbug code
        std::cout << "______ USERNAME : " << _username << std::endl;
        std::cout << "______ PASSWORD : " << _password << std::endl;
        */
        Credentials     *creds = new Credentials(connPool);
        if(std::regex_match(_username.begin(), _username.end(), __phoneNumber)) {
            // dbug passed
            //std::cout << "______ I'm in the phone regex ______" << std::endl;
            creds -> initWithPhoneNumber(_username);
        }
        else if (std::regex_match(_username.begin(), _username.end(), __email)) {
            // dbug
            //std::cout << "________ I'm in the email regex ______ " << std::endl;
            creds -> initWithEmail(_username);
        } else return false;
        if( creds -> getPassword() != _password ) {
            // dbug
            //std::cout << "_______ DB password : " << creds -> getPassword() << '\n';
            //std::cout << "_______ User pass : " << _password << std::endl;
            return false;
        }
        else {
            //std::cout << "______ I passed the password check ______ " << std::endl;
            try {
                // create and return the accessToken
                Wt::WDateTime   dateTime = Wt::WDateTime::currentDateTime();
                std::string     unixTimeAsStr = std::to_string(dateTime.toTime_t());
                std::string     rawString =
                    _username + ':' + _password + ":Masoume:" + unixTimeAsStr;
                _accessToken = Wt::Utils::sha1(rawString);
                _accessToken = Wt::Utils::base64Encode(_accessToken);
                // fetch the user info before commiting 
                int     userId_ = creds -> getAuthor().id();
                author::role    role_ = creds -> getAuthor() -> authorRole;
                creds -> commit();
                try { 
                    // add it to the accessToken table
                    kalematieSession   _session(connPool);
                    dbo::Transaction        t(_session);
                    // check for an accessToken for the requesting user
                    dbo::ptr<accessToken>   dbPtr = _session.find<accessToken>()
                        .where("userId = ?").bind(userId_);
                    // terminate if found
                    if(dbPtr.get()) return false;

                    accessToken     *dbPtr_ = new accessToken();
 
                    dbPtr_ -> token = _accessToken;
                    dbPtr_ -> userId = userId_; 
                    dbPtr_ -> role  = role_;
                    dbPtr_ -> creationDate = unixTimeAsStr;

                    _session.add(dbPtr_);

                    t.commit();

                    return true;
                } catch(Wt::Dbo::Exception& e) {
                    std::cout << e.what() << std::endl;
                    return false;
                } catch(...) {
                    std::cout << "Something went wrong trying to register the token in the \
                        accessToken table" << std::endl;
                    return false;
                }
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return false;
            } catch(...) {
                std::cout << "Something went wrong trying to create the token string" << std::endl;
                return false;
            }
        }
    }
}


bool    Token::invalidateAccessToken(std::string    accessToken_,
        Wt::Dbo::SqlConnectionPool& connPool) {
    if(_username == "" || _password == "") return false;
    else {
        Credentials     *creds_ = new Credentials(connPool);
        if(std::regex_match(_username.begin(), _username.end(), __phoneNumber)) {
            // dbug passed
            //std::cout << "______ I'm in the phone regex ______" << std::endl;
            creds_ -> initWithPhoneNumber(_username);
        }
        else if (std::regex_match(_username.begin(), _username.end(), __email)) {
            // dbug
            //std::cout << "________ I'm in the email regex ______ " << std::endl;
            creds_ -> initWithEmail(_username);
        } else return false;
        if( creds_ -> getPassword() != _password ) {
            // dbug
            //std::cout << "_______ DB password : " << creds -> getPassword() << '\n';
            //std::cout << "_______ User pass : " << _password << std::endl;
            return false;
        }
        else {
            int     userId_ = creds_ -> getAuthor().id();
            creds_ -> commit();
            std::string     dbToken = "";
            std::string     dbTokenTime = "";
            try {
                kalematieSession    _session(connPool);
                dbo::Transaction    t(_session);
                // test
                dbo::ptr<accessToken>   dbPtr_ = _session.find<accessToken>().where("userId = ?").bind(userId_);
                dbToken = dbPtr_ -> token;
                dbTokenTime = dbPtr_ -> creationDate;

                // create a token and compare with the db version
                std::string     rawString =
                    _username + ':' + _password + ":Masoume:" + dbTokenTime;
                _accessToken = Wt::Utils::base64Encode(
                        Wt::Utils::sha1(rawString));

                if(accessToken_ == dbToken) {
                    dbPtr_.remove();
                    t.commit();
                    return true;
                } else {
                    t.commit();
                    return false;
                }
            } catch(Wt::Dbo::Exception& e) {
                std::cout << e.what() << std::endl;
                return false;
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return false;
            } catch(...) {
                std::cout << "Something went wrong trying to invalidate \
                    and accessToken" << std::endl;
                return false;
            }
        }
    }
}

                





std::string     Token::getUsername() {
    return  _username;
}

std::string     Token::getPassword() {
    return  _password;
}

std::string     Token::getAccessToken() {
    return _accessToken;
}

std::string     Token::getBase64str() {
    return _base64str;
}

// TODO : implement the regexes
std::regex  Token::__email = std::regex(
        "^[A-Za-z0-9](([_\\.\\-]?[a-zA-Z0-9]+)*)@([A-Za-z0-9]+)(([\\.\\-]?[a-zA-Z0-9]+)*)\\.([A-Za-z]{2,})$", std::regex_constants::icase);

std::regex  Token::__phoneNumber = std::regex(
        "^09[0-9]{9}$", std::regex_constants::icase);
