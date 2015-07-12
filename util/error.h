#ifndef     _ERROR_H_
#define     _ERROR_H_

/*  This class is used to instantiate error objects.
 *  since all the errors have the same format it is
 *  good to have such class that takes care of formatting
 *  the error and actually outputting it to the client.
 */


#include <string>

#include <Wt/Http/Response>

class   error {

    public:
        error();
        error(std::string   errMessage, int errCode)
            : _errMessage(errMessage),
              _errCode(errCode)
        {
        }
        
        // used to output the error to the client 
        void    putOut(Wt::Http::Response&  response)
        {
            std::ostream&   out = response.out();
            
            response.setMimeType("application/json");
            out << "{" << std::endl;
            out << "    \"errorMessage\":\""<<_errMessage<<"\"," <<std::endl;
            out << "    \"errorCode\":\""<< _errCode <<"\"," << std::endl;
            out << "    \"responseData\":\"\"" << std::endl;
            out << "}" << std::endl;

        }
    private:
        std::string     _errMessage;
        int             _errCode;
};

#endif
