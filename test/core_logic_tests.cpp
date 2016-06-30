#include <QtTest/QtTest>

#include "../src/person.h"
#include "../src/book.h"
#include "../src/dvd.h"
#include "../src/library.h"
#include "../src/library_file.h"
#include <fstream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <QFile>
#include <QTemporaryFile>

class core_logic_tests : public QObject {
Q_OBJECT

private slots:

    void person_operators() {
        person p42(42, L"Mark", L"surter");
        person p0(0, L"Cathleen", L"Whatever");
        person p0_almost(0, L"NotCathleen", L"Either");
        QVERIFY((p0 == p0_almost));
        QVERIFY(p0 < p42);
        QVERIFY(!(p42 < p0));
        QVERIFY(!(p0 < p0));
    }

    void mediums_tests() {
        book b1(1, L"1984", L"George Orwell");
        book b2(2, L"Sophies Welt", L"Jostein Gaarder");
        dvd d3(3, L"Alien", L"Ridley Scott");
        QVERIFY(b1 < b2);
        QVERIFY(!(b1 < b1));
        QVERIFY(b2 < d3);
        QVERIFY(!(d3 < b2));
        QVERIFY(b1 == b1);
        QVERIFY(d3 == d3);
        QVERIFY(!(d3 == b2));
        QVERIFY(d3.get_description() == std::wstring(L"Ridley Scott: Alien"));
    }

    void library_test() {
        auto b1 = std::make_shared<book>(1, L"1984", L"George Orwell");
        auto b2 = std::make_shared<book>(2, L"Sophies Welt", L"Jostein Gaarder");
        auto d3 = std::make_shared<dvd>(3, L"Alien", L"Ridley Scott");
        auto p42 = std::make_shared<person>(42, L"Mark", L"surter");
        auto p0 = std::make_shared<person>(0, L"Cathleen", L"Whatever");
        person p1_local(1, L"NotCathleen", L"Either");

        library lib;
        lib.register_person(p0);
        lib.register_person(p42);
        lib.register_person(p1_local);
        lib.register_medium(b1);
        lib.register_medium(b2);
        lib.register_medium(d3);

        auto persons = lib.all_persons();
        auto p1_it = std::find_if(persons.begin(),persons.end(),
                                  [p1_local](const std::shared_ptr<person>& p)->bool{
                                     return p->get_id() == p1_local.get_id();
                                  });
        QVERIFY(p1_it != persons.end());
        auto p1 = *p1_it;
        QVERIFY(*p1 == p1_local);

        QVERIFY(lib.lend_medium(b1,p1));
        QVERIFY(!lib.lend_medium(b1,p0));
        QVERIFY(lib.lend_medium(d3,p1));
        QVERIFY(!lib.lend_medium(d3, p42));

        auto p1s_mediums = lib.lent_mediums(p1);
        size_t p1s_mediums_element_count = 0;
        for (auto i = p1s_mediums.cbegin(); i != p1s_mediums.cend(); ++i, ++p1s_mediums_element_count);
        QVERIFY(p1s_mediums_element_count == 2);
        QVERIFY(p1s_mediums.find(b1) != p1s_mediums.end());
        QVERIFY(p1s_mediums.find(d3) != p1s_mediums.end() && p1s_mediums.find(d3)->get()->get_id() == d3->get_id());

        QVERIFY(lib.lent_to_person(b2) == std::shared_ptr<person>{});
        lib.give_back(b1);
        QVERIFY(lib.lend_medium(b1, p0));
        QVERIFY(lib.lent_to_person(b1) == p0);

        QVERIFY(!lib.erase_person(p0));
        lib.give_back(b1);
        QVERIFY(lib.erase_person(p0));
        QVERIFY(lib.lend_medium(b1, p42));
        QVERIFY(lib.lent_to_person(b1) == p42);
        persons = lib.all_persons();
        QVERIFY(persons.find(p0) == persons.end());
        lib.erase_medium(b1);
        auto mediums = lib.all_mediums();
        QVERIFY(mediums.find(b1) == mediums.end());
        auto p42_mediums = lib.lent_mediums(p42);
        QVERIFY(p42_mediums.find(b1) == p42_mediums.end());

    };

    void library_file_test() {
        const std::string temp_file_name_1 = std::tmpnam(NULL);
        //auto fstream_lib = library_file<std::fstream>{std::fstream{temp_file_name_1}};
        //QTemporaryFile qfile;
        //auto qfile_lib = library_file<QFile&>{qfile};

    }
};

QTEST_MAIN(core_logic_tests)

#include "core_logic_tests.moc"