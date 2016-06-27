/*! @file medium.h
 * */

#ifndef PROG2BELEG_MEDIUM_H
#define PROG2BELEG_MEDIUM_H

#include <string>

class medium {
public:
    using id_t = uint8_t;

    virtual std::string get_description() const = 0;

    medium() = delete;

    medium(id_t id);

    virtual ~medium() { }

protected:
    id_t id_;
};


#endif //PROG2BELEG_MEDIUM_H
