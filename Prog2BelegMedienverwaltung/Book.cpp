//
//  Book.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 28.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "Book.h"

std::string Book::name ()
{
    return "Title: " + pTitle + " Author: " + pAuthor;
}

 Book::Book (const std::string &title, const std::string &author)
: pTitle(title), pAuthor(title)
{
    
}
bool Book::operator==(const Book& r)
{
    if (this->pTitle == r.pTitle && this->pAuthor == r.pAuthor) {
        return true;
    }
    else{
        return false;
    }
}