//
//  Media.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef __Prog2BelegMedienverwaltung__Media__
#define __Prog2BelegMedienverwaltung__Media__

#include <iostream>

class Person;

/*!
Abstract Base Class for all media types which should be managed
*/
class Media {
private:
    const Person* pLender;
    Media ();
    
public:
    /*! If Media is lend to someone, returns the person, otherwise a nullptr
     @return Pointer to a person class instance or nullptr if not lend
     */
    const Person* lendstatus () const;
    
    void setLender(const Person *lender);
    
    virtual std::string name () = 0;
    Media& operator= (const Media *) = delete;
    Media (const Media&) = delete;
};

#endif /* defined(__Prog2BelegMedienverwaltung__Media__) */
