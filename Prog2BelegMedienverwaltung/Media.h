//
//  Media.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef MK_Media
#define MK_Media

#include <iostream>

class Person;

/*!
Abstract Base Class for all media types which should be managed
*/
class Media {
private:
     Person* pLender;

protected:
       Media ();

public:
    /*! If Media is lend to someone, returns the person, otherwise a nullptr
     @return Pointer to a person class instance or nullptr if not lend
     */
    virtual Person* lendstatus () const;
    
    virtual void setLender(Person *lender);
    
    virtual std::string name () = 0;
    Media& operator= (const Media *) = delete;
    Media (const Media&) = delete;
};

#endif /* defined(MK_Media) */
