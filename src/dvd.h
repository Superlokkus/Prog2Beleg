//
// Created by Markus Klemm on 26.06.16.
//

#ifndef PROG2BELEG_DVD_H
#define PROG2BELEG_DVD_H

#include <string>
#include "medium.h"

struct dvd : medium {
    std::wstring get_description() const override;

    std::wstring title;
    std::wstring director;

    dvd() = delete;

    dvd(id_t id, std::wstring title, std::wstring director)
            : medium(id), title(title), director(director) { }
};


#endif //PROG2BELEG_DVD_H
