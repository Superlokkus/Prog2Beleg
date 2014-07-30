//
//  menu.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef __Prog2BelegMedienverwaltung__menu__
#define __Prog2BelegMedienverwaltung__menu__

#include <iostream>
#include "Media.h"
#include "Person.h"
#include "MediaPersonDB.h"

namespace runloop {
    static MediaPersonDB *mpdb;

    void runloop (MediaPersonDB &mpdb);
    
    void lendBook();
    void lendDVD();
    
    void giveBackBook();
    void giveBackDVD();
    
    void listPersons();
    void infoPerson();
    void storePerson();
    void deletePerson();
    
    void listMedia();
    void infoMedia();
    void storeBook();
    void storeDVD();
    void deleteBook();
    void deleteDVD();

}

#endif /* defined(__Prog2BelegMedienverwaltung__menu__) */
