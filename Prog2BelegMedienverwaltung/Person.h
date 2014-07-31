//
//  Person.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef __Prog2BelegMedienverwaltung__Person__
#define __Prog2BelegMedienverwaltung__Person__

#include <iostream>
#include <list>

class Media;

class Person
{
private:
    const std::string pName;
    unsigned pMaxItems;
    unsigned pLentItemsCount;
    std::list<Media*> pLentMedia;
public:
    std::string name() const;
    /*! Returns the limits of items the person can lend, or zero if there is none
     @return Limit or zero
     */
    unsigned maxItems() const;
    /*! Set the limit of items the person can lend, or zero if there is none
     @param itemLimit Limit or zero
     */
    void setmaxItems(unsigned itemLimit);
    
    bool lend       (Media &toLend);
    bool giveback   (Media &toGiveBack);
    
    std::list <Media*> lentMedia() const;
    Person (const std::string &name);
    Person (const std::string &name, unsigned itemLimit);
    
    Person& operator= (const Person *) = delete;
    Person (const Person&) = delete;
};

#endif /* defined(__Prog2BelegMedienverwaltung__Person__) */
