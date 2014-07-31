//
//  MediaPersonDB.h
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 29.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#ifndef MK_MediaPersonDB
#define MK_MediaPersonDB

#include <iostream>
#include <list>
#include <utility>
#include "Book.h"
#include "DVD.h"
#include "Person.h"

class MediaPersonDB
{
private:
    std::list<Book*> books;
    std::list<DVD*> dvds;
    std::list<Person*> persons;
public:
    void storeBook(Book &&mediaToStore)
    {
        books.push_back(&mediaToStore); //To-Think: list as <Book> and std::move(mediaToStore) calls implicit copy contructor
    }
    void storeDVD(DVD &&dvdToStore)
    {
        dvds.push_back(&dvdToStore);
    }
    void storePerson(Person &&personToStore)
    {
        persons.push_back(&personToStore);
    }
    Book* getBookByTitle(const std::string &title) const
    {
        for (auto candidate : books)
        {
            if (candidate->pTitle == title)
                return candidate;
        }
        return nullptr;
    }
    Book* getBookByAuthor(const std::string &author) const
    {
        for (auto candidate : books)
        {
            if (candidate->pAuthor == author)
                return candidate;
        }
        return nullptr;
    }
    DVD* getDVDByTitle(const std::string &title) const
    {
        for (auto candidate : dvds)
        {
            if (candidate->pTitle == title)
                return candidate;
        }
        return nullptr;
    }
    DVD* getDVDByDirector(const std::string &director) const
    {
        for (auto candidate : dvds)
        {
            if (candidate->pDirector == director)
                return candidate;
        }
        return nullptr;
    }
    Person* getPersonByName(const std::string &name) const
    {
        for (auto candidate : persons)
        {
            if (candidate->name() == name)
                return candidate;
        }
        return nullptr;
    }
    std::list<Person*> getPersonList()
    {
        return persons;
    }
    std::list<Book*> getBookList()
    {
        return books;
    }
    std::list<DVD*> getDVDList()
    {
        return dvds;
    }
    void deleteBook(Book* toDelete)
    {
        for (auto b : books)
        {
            if (*b == *toDelete)
            {
                Person *p = b->lendstatus();
                if (p) {
                    p->giveback(*b);
                }
                books.remove(b);
                break; //Must break, must not continue c++11 for each after modifiying
            }
        }
    }
    void deleteDVD(DVD* toDelete)
    {
        for (auto d : dvds)
        {
            if (*d == *toDelete)
            {
                Person *p = d->lendstatus();
                if (p) {
                    p->giveback(*d);
                }
                dvds.remove(d);
                break; //Must break, must not continue c++11 for each after modifiying
            }
        }
    }
    bool deletePerson(Person *toDelete)
    {
        if (toDelete->lentMedia().empty()) {
            persons.remove(toDelete);
            return true;
        }
        return false;
    }
};

#endif /* defined(MK_MediaPersonDB) */
