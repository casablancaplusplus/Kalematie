#ifndef     _DBO_H_
#define     _DBO_H_


#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/WDate>
#include <Wt/WDateTime>

namespace   dbo = Wt::Dbo;


class author;

class   quote {

    public:

        std::string     text;
        std::string      date_published = "1";
        double           rating = -1;
        int             viewers = 1;
        bool            verified = false;

        dbo::ptr<author>    Author;

        template<class Action>
            void    persist(Action& a)
            {
                dbo::field(a,   text,   "text");
                dbo::field(a,   date_published, "date_published");
                dbo::field(a,   rating,         "rating");
                dbo::field(a,   viewers,        "viewers");

                dbo::belongsTo(a,   Author, "Author");
            }
                
};

class author {

    public:
        enum    role {
            Administrator,
            Validator,
            Author,
            Guest
        };

        std::string     firstName;
        std::string     lastName;
        std::string     nickName;
        std::string     phoneNumber;
        std::string     password;
        double           rating;
        int             followers; // the number of the followes
        int             following; // the number of the others this user 
                                 // follows
        role            authorRole;

        dbo::collection< dbo::ptr<quote> >  quotes;

        template<class  Action>
            void    persist(Action& a)
            {
                dbo::field(a,   firstName,  "firstName");
                dbo::field(a,   lastName,   "lastName");
                dbo::field(a,   nickName,   "nickName");
                dbo::field(a,   phoneNumber,"phoneNumber");
                dbo::field(a,   password,   "password");
                dbo::field(a,   rating,     "rating");
                dbo::field(a,   followers,  "followers");
                dbo::field(a,   following,  "following");
                dbo::field(a,   authorRole, "authorRole");

                dbo::hasMany(a, quotes, dbo::ManyToOne, "Author");
            }
};
class rating {
    
    public:
        int     quoteId;
        int     raterId; // the id of the user who rated
        double   rating;

        template<class Action>
            void    persist(Action& a)
            {
                dbo::field(a,   quoteId,    "quoteId");
                dbo::field(a,   raterId,    "raterId");
                dbo::field(a,   rating,     "rating");
            }
};

class following {

    public:
        int     followerId;
        int     followedId;

        template<class Action>
            void    persist(Action&     a)
            {
                dbo::field(a,   followerId, "followerId");
                dbo::field(a,   followedId, "followedId");
            }


};

class   accessToken {
    
    public:
        std::string     token;
        int             userId;
        author::role    role;

        template<class  Action>
            void    persist(Action&     a)
            {
                dbo::field(a,   token,  "token");
                dbo::field(a,   userId, "userId");
                dbo::field(a,   role,   "role");
            }
};

#endif
