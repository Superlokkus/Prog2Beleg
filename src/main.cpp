/*! @file main.cpp
 *
 * */

#include<QtGui/QApplication>
#include <QtGui>

#include "library_qt_adapters.h"

int main(int argc, char* argv[]) {
    QApplication this_application(argc,argv);
    auto lib = std::make_shared<library>();
    library_person_view lib_person_model(lib);
    lib->register_person(person{1, L"Markus", L"Klemm"});
    lib->register_person(person{2, L"Fred", L"Feuerstein"});

    QMainWindow *window = new QMainWindow;
    //window->setBaseSize(600,800);


    QTableView *central_table = new QTableView(window);
    central_table->setModel(&lib_person_model);

    window->setCentralWidget(central_table);

    window->show();

    return this_application.exec();
}