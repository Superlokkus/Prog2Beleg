//
//  menu.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "menu.h"



using namespace std;
using namespace runloop;

void runloop::runloop (MediaPersonDB &mpdb)
{
    unsigned command;
    runloop::mpdb = &mpdb;
    
    while (true)
    {
        
        cout << "Menu: " << endl << endl;;
        cout << "1X Lend" << endl;
        cout << "   11 A Book " << endl;
        cout << "   12 A DVD " << endl;
        cout << "2X Give Back: " << endl;
        cout << "   21 A Book " << endl;
        cout << "   22 A DVD " << endl;
        cout << "3X Person Management:" << endl;
        cout << "    31 List Persons           " << endl;
        cout << "    32 Inform about a Person " << endl;
        cout << "    33 Register a Person     " << endl;
        cout << "    34 Delete a Person       " << endl;
        cout << "4X Media Management           " << endl;
        cout << "    41 List Media          " << endl;
        cout << "    42 Inform about a Media" << endl;
        cout << "    43 Register Book      " << endl;
        cout << "    43 Register DVD      " << endl;
        cout << "    44 Delete Book        " << endl;
        cout << "    44 Delete DVD        " << endl;
        cout << "To save and quit any other input" << endl;
        cout << "==============================" << endl;
        cout << "-> ";
        
        if (!(cin >> command))
        {
            break;
        }
        
        switch (command) {
            case 11:
                lendBook();
                break;
            case 12:
                lendDVD();
                break;
            case 21:
                giveBackBook();
                break;
            case 22:
                giveBackDVD();
                break;
            case 31:
                listPersons();
                break;
            case 32:
                infoPerson();
                break;
            case 33:
                storePerson();
                break;
            case 34:
                deletePerson();
                break;
            case 41:
                listMedia();
                break;
            case 42:
                infoMedia();
                break;
            case 43:
                storeBook();
                break;
            case 44:
                storeDVD();
                break;
            case 45:
                deleteBook();
                break;
            case 46:
                deleteDVD();
                break;
                
            default:
                cout << "Invald option" << endl;
                break;
        }
    }
}

void runloop::lendBook()
{
    string searchString;
    cout << "Please enter book title: " << endl;
    cin >> searchString;
    Book *bookToLend = mpdb->getBookByTitle(searchString);
    if (bookToLend == nullptr)
    {
        cout << "Book not found by title, please enter author: " << endl;
        cin >> searchString;
        bookToLend = mpdb->getBookByAuthor(searchString);
        if (bookToLend == nullptr) {
            cout << "Book not found either by author, aborting." << endl;
            return;
        }
    }
    cout << "Enter the persons name you want to lend to" << endl;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    p->lend(*bookToLend);
    
    
}
void runloop::lendDVD()
{
    string searchString;
    cout << "Please enter DVD title: " << endl;
    cin >> searchString;
    DVD *dvdToLend = mpdb->getDVDByTitle(searchString);
    if (dvdToLend == nullptr)
    {
        cout << "DVD not found by title, please enter director: " << endl;
        cin >> searchString;
        dvdToLend = mpdb->getDVDByDirector(searchString);
        if (dvdToLend == nullptr) {
            cout << "DVD not found either by director, aborting." << endl;
            return;
        }
    }
    cout << "Enter the persons name you want to lend to" << endl;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    p->lend(*dvdToLend);
}

void runloop::giveBackBook()
{
    
}
void runloop::giveBackDVD()
{
    
}

void runloop::listPersons()
{
    
}
void runloop::infoPerson()
{
    
}
void runloop::storePerson()
{
    
}
void runloop::deletePerson()
{
    
}

void runloop::listMedia()
{
    
}
void runloop::infoMedia()
{
	
}

void runloop::storeBook()
{
	
}

void runloop::storeDVD()
{
	
}

void runloop::deleteBook()
{
	
}

void runloop::deleteDVD()
{
	
}

