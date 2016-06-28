//
// Created by Markus Klemm on 26.06.16.
//

#include "dvd.h"

std::wstring dvd::get_description() const {
    return this->director + L": " + this->title;
}