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
    return "Title: " + ptitle + " Author: " + pauthor;
}

 Book::Book (const std::string &title, const std::string &author)
: ptitle(title), pauthor(title)
{
    
}