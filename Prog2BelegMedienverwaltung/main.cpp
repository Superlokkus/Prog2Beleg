//
//  main.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include <iostream>
#include <list>
#include "menu.h"
#include "MediaPersonDB.h"


int main(int argc, const char * argv[])
{
    MediaPersonDB mpdb;
    
    //load saved records in mpdb
    
    runloop(mpdb);
    
    //save recods in mpdb

    return 0;
}

