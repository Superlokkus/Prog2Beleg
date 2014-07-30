//
//  MediaPersonDB.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef __Prog2BelegMedienverwaltung__MediaPersonDB__
#define __Prog2BelegMedienverwaltung__MediaPersonDB__

#include <iostream>
#include <list>
#include "Book.h"
#include "DVD.h"
#include "Person.h"

class MediaPersonDB
{
private:
    std::list<Book> books;
    std::list<DVD> dvds;
    std::list<Person> persons;
public:
    void storeBook(Book &&mediaToStore);
    void storeDVD(DVD &&dvdToStore);
    void storePerson(Person &&personToStore);
    Book* getBookByTitle(const std::string &title) const;
    Book* getBookByAuthor(const std::string &author) const;
    DVD* getDVDByTitle(const std::string &title) const;
    DVD* getDVDByDirector(const std::string &director) const;
    Person* getPersonByName(const std::string &name) const;
    
};

#endif /* defined(__Prog2BelegMedienverwaltung__MediaPersonDB__) */
