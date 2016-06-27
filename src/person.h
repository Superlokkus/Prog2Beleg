//
// Created by Markus Klemm on 26.06.16.
//

#ifndef PROG2BELEG_PERSON_H
#define PROG2BELEG_PERSON_H

#include <string>

struct person {
    using id_t = uint64_t;

    std::wstring name;
    std::wstring surname;

    person() = delete;

    person(id_t id, std::wstring name, std::wstring surname);

    id_t get_id() const {
        return this->id_;
    }

    bool operator==(const person &r) const {
        return this->id_ == r.id_;
    }

    bool operator<(const person &r) const {
        return this->id_ < r.id_;
    }
private:
    id_t id_;
};


#endif //PROG2BELEG_PERSON_H
