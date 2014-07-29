//
//  menu.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "menu.h"


using namespace std;

void runloop ()
{
    unsigned command;
    
    while (true)
    {
        
        cout << "Menu: " << endl << endl;;
        cout << "1 Lend" << endl;
        cout << "2 Give Back: " << endl;
        cout << "3X Person Management:" << endl;
        cout << "    31 List Persons           " << endl;
        cout << "    32 Inform about a Person " << endl;
        cout << "    33 Register a Person     " << endl;
        cout << "    34 Delete a Person       " << endl;
        cout << "4X Media Management           " << endl;
        cout << "    41 List Media          " << endl;
        cout << "    42 Inform about a Media" << endl;
        cout << "    43 Register Media      " << endl;
        cout << "    44 Delete Media        " << endl;
        cout << "To save and quit any other input" << endl;
        cout << "==============================" << endl;
        cout << "-> ";
        
        if (!(cin >> command))
        {
            break;
        }
        
        switch (command) {
            case 11:
                cout << "book lend" << endl;
                break;
                
            default:
                cout << "Invald option" << endl;
                break;
        }
    }
}
