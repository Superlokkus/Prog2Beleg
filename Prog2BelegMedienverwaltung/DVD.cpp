//
//  DVD.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "DVD.h"


std::string DVD::name ()
{
    return "Title: " + pTitle + " Director: " + pDirector;
}

DVD::DVD (const std::string &title, const std::string &director)
: pTitle(title), pDirector(director)
{
}

DVD::DVD (const std::string &title, const std::string &director, unsigned DVDCount)
: pTitle(title), pDirector(director), pDVDCount(DVDCount)
{
}

void DVD::setDVDCount (unsigned count)
{
    pDVDCount = count;
}
unsigned DVD::DVDCount ()
{
    return pDVDCount;
}