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

        int     id;
        std::string     text;
        Wt::WDate       date_published;
        float           rating;
        int             viewers;

        dbo::ptr<author>    quoteAuthor;

        template<class Action>
            void    persist(Action& a)
            {
                dbo::field(a,   id,     "id");
                dbo::field(a,   text,   "text");
                dbo::field(a,   date_published, "date_published");
                dbo::field(a,   rating,         "rating");
                dbo::field(a,   viewers,        "viewers");

                dbo::belongsTo(a,   quoteAuthor, "quoteAuthor");
            }
                
};

class author {

    public:
        enum    role {
            Administrator,
            Validator,
            Author,
            Vuest
        };

        int     id;
        std::string     firstName;
        std::string     lastName;
        std::string     nickName;
        int             phoneNumber;
        std::string     password;
        float           rating;
        int             followers; // the number of the followes
        int             following; // the number of the others this user 
                                    // follows
        role            authorRole;

        dbo::collection< dbo::ptr<quote> >  quotes;

        template<class  Action>
            void    persist(Action& a)
            {
                dbo::field(a,   id,     "id");
                dbo::field(a,   firstName,  "firstName");
                dbo::field(a,   lastName,   "lastName");
                dbo::field(a,   nickName,   "nickName");
                dbo::field(a,   phoneNumber,"phoneNumber");
                dbo::field(a,   password,   "password");
                dbo::field(a,   rating,     "rating");
                dbo::field(a,   followers,  "followers");
                dbo::field(a,   following,  "following");

                dbo::hasMany(a, quotes, dbo::ManyToOne, "author");
            }
};
class rating {
    
    public:
        int     quoteId;
        int     raterId; // the id of the user who rated
        float   rating;

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
