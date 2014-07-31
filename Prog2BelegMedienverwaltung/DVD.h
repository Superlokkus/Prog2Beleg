//
//  DVD.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef MK_DVD
#define MK_DVD

#include <iostream>
#include "Media.h"

class DVD: public Media {
private:
    unsigned pDVDCount;
    
public:
    const std::string pTitle;
    const std::string pDirector;
    std::string name ();
    DVD (const std::string &title, const std::string &director);
    DVD (const std::string &title, const std::string &director, unsigned DVDCount);
    void setDVDCount (unsigned count);
    unsigned DVDCount ();
    bool operator== (const DVD&r);
};

#endif /* defined(MK_DVD) */
