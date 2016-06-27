/*! @file medium.h
 * */

#ifndef PROG2BELEG_MEDIUM_H
#define PROG2BELEG_MEDIUM_H

#include <string>

class medium {
public:
    using id_t = uint8_t;

    id_t get_id() const {
        return this->id_;
    }

    bool operator==(const medium &r) const {
        return this->id_ == r.id_;
    }

    bool operator<(const medium &r) const {
        return this->id_ < r.id_;
    }

    virtual std::string get_description() const = 0;

    medium() = delete;

    medium(id_t id);

    virtual ~medium() { }

protected:
    id_t id_;
};


#endif //PROG2BELEG_MEDIUM_H
