//
//  Book.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 28.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef __Prog2BelegMedienverwaltung__Book__
#define __Prog2BelegMedienverwaltung__Book__

#include <iostream>
#include "Media.h"

class Book : public Media
{
public:
    const std::string pTitle;
    const std::string pAuthor;
    std::string name ();
    Book (const std::string &title, const std::string &author);
    
};


#endif /* defined(__Prog2BelegMedienverwaltung__Book__) */
