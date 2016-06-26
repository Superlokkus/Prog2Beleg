/*! @file Medium.h
 * */

#ifndef PROG2BELEG_MEDIUM_H
#define PROG2BELEG_MEDIUM_H

#include <string>

class Medium {
public:
    virtual std::string get_Description() const;

    Medium () = delete;
    Medium (std::string uid);

protected:
    std::string uid;
};


#endif //PROG2BELEG_MEDIUM_H
