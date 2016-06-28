#include <QtTest/QtTest>

#include "../src/person.h"
#include "../src/book.h"
#include "../src/dvd.h"

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

    };
};

QTEST_MAIN(core_logic_tests)

#include "core_logic_tests.moc"