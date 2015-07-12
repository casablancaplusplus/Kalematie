#ifndef     _DBO_H_
#define     _DBO_H_


#include <Wt/Dbo/Dbo>


namespace   dbo = Wt::Dbo;



class   accessToken {

};

class   quote {

};

class author {

    public:
        enum    role {
            administrator,
            validator,
            author,
            guest
        }

};
class rating {

};

class following {

}
#endif
