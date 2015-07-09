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
        error(std::string   errMessage, int errCode);
        
        // used to output the error to the client 
        void    putOut(Wt::Http::Response&  response); 
    private:
        std::string     errMessage;
        int             errCode;

#endif
