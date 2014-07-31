//
//  Person.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "Person.h"
#include "Media.h"

Person::Person (const std::string &name)
: pName(name), pMaxItems(0), pLentItemsCount(0)
{
}

Person::Person (const std::string &name, unsigned itemLimit)
: pName(name), pMaxItems(itemLimit), pLentItemsCount(0)
{
    
}

bool Person::lend       (Media &toLend)
{
    if (pLentItemsCount == maxItems() || toLend.lendstatus() != nullptr) {
        return false;
    }
    toLend.setLender(this); pLentItemsCount++;
    return true;
    
}
bool Person::giveback   (Media &toGiveBack)
{
    if (toGiveBack.lendstatus() != this)
        return false;
    toGiveBack.setLender(nullptr); pLentItemsCount--;
    return true;
}
std::string Person::name() const
{
    return std::string(pName);
}
unsigned Person::maxItems() const
{
    return pMaxItems;
}
void Person::setmaxItems(unsigned itemLimit)
{
    pMaxItems = itemLimit;
}
std::list <Media*> Person::lentMedia() const
{
    return pLentMedia;
}