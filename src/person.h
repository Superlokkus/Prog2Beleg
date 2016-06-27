//
// Created by Markus Klemm on 26.06.16.
//

#ifndef PROG2BELEG_PERSON_H
#define PROG2BELEG_PERSON_H

#include <string>

struct person {
    using id_t = uint8_t;
    id_t id;

private:
    std::wstring name_;
    std::wstring surname_;
};


#endif //PROG2BELEG_PERSON_H
