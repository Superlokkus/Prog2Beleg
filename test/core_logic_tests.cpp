#include <QtTest/QtTest>

#include "../src/person.h"

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
};

QTEST_MAIN(core_logic_tests)

#include "core_logic_tests.moc"