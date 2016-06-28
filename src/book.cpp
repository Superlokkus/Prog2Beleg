//
// Created by Markus Klemm on 26.06.16.
//

#include "book.h"

std::wstring book::get_description() const {
    return this->author + L": " + this->title;
}
