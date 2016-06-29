#include <QtTest/QtTest>

#include "../src/person.h"
#include "../src/book.h"
#include "../src/dvd.h"
#include "../src/library.h"
#include <memory>
#include <algorithm>

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

    };
};

QTEST_MAIN(core_logic_tests)

#include "core_logic_tests.moc"