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

Book* askForBook()
{
    string searchString;
    cout << "Please enter book title: " << endl;
    cin >> searchString;
    Book *book = mpdb->getBookByTitle(searchString);
    if (book == nullptr)
    {
        cout << "Book not found by title, please enter author: " << endl;
        cin.clear();
        cin >> searchString;
        book = mpdb->getBookByAuthor(searchString);
        if (book == nullptr) {
            cout << "Book not found either by author, aborting." << endl;
            return nullptr;
        }
    }
    return book;
}
DVD* askForDVD()
{
    string searchString;
    cout << "Please enter DVD title: " << endl;
    cin >> searchString;
    DVD *dvd = mpdb->getDVDByTitle(searchString);
    if (dvd == nullptr)
    {
        cout << "DVD not found by title, please enter director: " << endl;
        cin.clear();
        cin >> searchString;
        dvd = mpdb->getDVDByDirector(searchString);
        if (dvd == nullptr) {
            cout << "DVD not found either by director, aborting." << endl;
            return nullptr;
        }
    }
    return dvd;
}

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
    Book* bookToLend(askForBook());
    if (!bookToLend) {
        return;
    }
    cout << "Enter the persons name you want to lend to" << endl;
    cin.clear(); std::string searchString;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    if (!p->lend(*bookToLend))
    {
        cout << "Can't lend " << bookToLend->name() << " to " << p->name() << endl;
    }
    cout << "Successfully lent " << bookToLend->name() << " to " << p->name() << endl;
    
}
void runloop::lendDVD()
{
    DVD* dvdToLend(askForDVD());
    if (!dvdToLend) {
        return;
    }
    cout << "Enter the persons name you want to lend to" << endl;
    cin.clear(); string searchString;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    if (!p->lend(*dvdToLend))
    {
        cout << "Can't lend " << dvdToLend->name() << " to " << p->name() << endl;
    }
    cout << "Successfully lent " << dvdToLend->name() << " to " << p->name() << endl;
}

void runloop::giveBackBook()
{
    Book* bookToGiveBack(askForBook());
    if (!bookToGiveBack)
        return;
    cout << "Enter the persons name which is giving back the book" << endl;
    cin.clear(); string searchString;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    if (!p->giveback(*bookToGiveBack))
    {
        cout << bookToGiveBack->name() << " wasn't lent to " << p->name() << endl;
    }
    cout << bookToGiveBack->name() << " returned by " << p->name() << endl;
    
}
void runloop::giveBackDVD()
{
    DVD* dvdToGiveBack(askForDVD());
    if (!dvdToGiveBack)
        return;
    cout << "Enter the persons name which is giving back the DVD" << endl;
    cin.clear(); string searchString;
    cin >> searchString;
    Person * p = mpdb->getPersonByName(searchString);
    if (p == nullptr)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    if (!p->giveback(*dvdToGiveBack))
    {
        cout << dvdToGiveBack->name() << " wasn't lent to " << p->name() << endl;
    }
    cout << dvdToGiveBack->name() << " returned by " << p->name() << endl;

}

void runloop::listPersons()
{
    cout << "==============================" << endl;
    cout << "Name:" << endl;
    for (auto p : mpdb->getPersonList())
    {
        cout << p->name() << endl;;
    }
    cout << "==============================" << endl;
    
}
void runloop::infoPerson()
{
    cout << "Please enter the name of the person whom details should be displayed" << endl;
    string searchString;
    cin >> searchString;
    Person *p = mpdb->getPersonByName(searchString);
    if (!p)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    cout << "==============================" << endl;
    cout << "Name: " << p->name() << endl;
    cout << "==============================" << endl;
    cout << "Lent media:" << endl;
    for (auto m : (p->lentMedia()))
    {
        cout << m->name();
    }
    cout << "==============================" << endl;
    return;
}
void runloop::storePerson()
{
    string name;
    cout << "Please enter the name of the Person:" << endl;
    cin >> name;
    unsigned limit = 0; cin.clear();
    cout << "Should " << name << " have a maximum of lent media? Type in 0 or a nonnumerical for no limit" << endl;
    cin >> limit;
    Person p(name,limit);
    mpdb->storePerson(std::move(p));
    
}
void runloop::deletePerson()
{
    cout << "Please enter the name of the person whom shall be deleted" << endl;
    string searchString;
    cin >> searchString;
    Person *p = mpdb->getPersonByName(searchString);
    if (!p)
    {
        cout << "Person not found, aborting." << endl;
        return;
    }
    if (!mpdb->deletePerson(p))
    {
        cout << p->name() << " did not brought back all lent items! Will not delete in your sake" << endl;
    }
    cout << searchString << "Person successfully erased. hasta la vista" << endl; //For further reading consider "ArnoldC"

}

void runloop::listMedia()
{
    cout << "==============================" << endl;
	cout << "Books: \tTitle\tAuthor" << endl;
    for (auto b : mpdb->getBookList())
    {
        cout << "\t" << b->pTitle << "\t" << b->pAuthor << endl;
    }
    cout << "DVDs: \tTitle\tDirector" << endl;
    for (auto d : mpdb->getDVDList())
    {
        cout << "\t" << d->pTitle << "\t" << d->pDirector << endl;
    }
    cout << "==============================" << endl;
}
void runloop::infoMedia()
{
    cout << "Please enter a title:" << endl;
    string searchString;
    cin >> searchString;
    Book *b = mpdb->getBookByTitle(searchString);
    DVD *d = mpdb->getDVDByTitle(searchString);
    Person *p;
    cout << "==============================" << endl;
    if (b)
    {
        cout << "Found book:" << endl;
        cout << "Title: " << b->pTitle << endl;
        cout << "Author: " << b->pAuthor << endl;
        p = b->lendstatus();
        cout << "Lent to" << ((p) ? p->name() : "no one") << endl;
    }
    if (d)
    {
        cout << "Found DVD:" << endl;
        cout << "Title: " << d->pTitle << endl;
        cout << "Director: " << d->pDirector << endl;
        p = d->lendstatus();
        cout << "Lent to" << ((p) ? p->name() : "no one") << endl;
    }
    cout << "==============================" << endl;
    
}

void runloop::storeBook()
{
    string title,author;
	cout << "Please enter the books title:" << endl;
    cin >> title; cin.clear();
    cout << "Please enter the books author:" << endl;
    cin >> author;
    if (title.empty() || author.empty())
    {
        cout << "Please enter nonempty titles and authors" << endl;
        return;
    }
    Book newBook(title,author); mpdb->storeBook(std::move(newBook));
    
}

void runloop::storeDVD()
{
    string title,director; unsigned dvds = 1;
	cout << "Please enter the DVDs title:" << endl;
    cin >> title; cin.clear();
    cout << "Please enter the DVDs director:" << endl;
    cin >> director; cin.clear();
    if (title.empty() || director.empty())
    {
        cout << "Please enter nonempty titles and directors" << endl;
        return;
    }
    cout << "How much acutal DVDs does the box contain?" << endl;
    cin >> dvds;
    DVD newDVD(title,director,dvds); mpdb->storeDVD(std::move(newDVD));
}

void runloop::deleteBook()
{
    Book *b = askForBook();
    if (b)
        mpdb->deleteBook(b);
}

void runloop::deleteDVD()
{
	DVD *d = askForDVD();
    if (d) {
        mpdb->deleteDVD(d);
    }
}

