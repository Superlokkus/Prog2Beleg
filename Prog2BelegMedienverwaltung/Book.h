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

class Book : Media
{
private:
    const std::string ptitle;
    const std::string pauthor;
    
    
public:
    std::string name ();
    Book (const std::string &title, const std::string &author);
    
};


#endif /* defined(__Prog2BelegMedienverwaltung__Book__) */
