//
//  Book.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 28.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef MK_Book
#define MK_Book

#include <iostream>
#include "Media.h"

class Book : public Media
{
public:
    const std::string pTitle;
    const std::string pAuthor;
    std::string name ();
    Book (const std::string &title, const std::string &author);
    bool operator==(const Book& r);
    
};


#endif /* defined(MK_Book) */
