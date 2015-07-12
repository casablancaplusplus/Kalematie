#ifndef     _TOKEN_H_
#define     _TOKEN_H_

// This class takes care of creating an access token or invalidating it
// It also contains the actual username and password

class   token {

    public:
        token(std::string   base64str);
        
        // creates an access token using the provided base64 string on construction
        // and returns true on success
        // or returns false on failure
        bool     createAccessToken();

        // In order for this funciton to work, It needs to compare the
        // accessToken parameter with the one it creates from the base64str
        // that is taken in construction and if equal -> does the job and returns true
        // else -> return false
        bool     invalidateAccessToken(std::string   accessToken);
        
        // getters
        std::string     getUsername();
        std::string     getPassword();
        std::string     getAccessToken();
        std::string     getBase64str();

    private:
        std::string     _base64str;
        std::string     _accessToken; // an empty string initially
        std::string     _username;
        std::string     _password;
};


#endif
