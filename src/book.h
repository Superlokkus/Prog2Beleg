//
// Created by Markus Klemm on 26.06.16.
//

#ifndef PROG2BELEG_BOOK_H
#define PROG2BELEG_BOOK_H

#include <string>

#include "medium.h"

struct book : medium {
    std::wstring get_description() const override;

    std::wstring title;
    std::wstring author;
    std::wstring isbn;

    book() = delete;

    book(id_t id, std::wstring title, std::wstring author) :
            book(id, title, author, L"") { }

    book(id_t id, std::wstring title, std::wstring author, std::wstring isbn) :
            medium(id), title(title), author(author), isbn(isbn) { }
};


#endif //PROG2BELEG_BOOK_H
