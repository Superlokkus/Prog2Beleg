/*! @file main.cpp
 *
 * */

#include <QtGui/QApplication>
#include <QtGui>
#include <QDockWidget>

#include "library_qt_adapters.h"

class library_widget : public QMainWindow {
Q_OBJECT

public:
    library_widget()
            : QMainWindow() {
        this->lib = std::make_shared<library>();
        current_model = std::make_shared<library_person_view>(lib);
        lib->register_person(person{1, L"Markus", L"Klemm"});
        lib->register_person(person{2, L"Fred", L"Feuerstein"});
        lib->register_medium(std::make_shared<book>(1, L"1984", L"George Orwell", L"555-3232"));
        lib->register_medium(std::make_shared<dvd>(2, L"Alien", L"Ridley Scott"));

        auto toolbar = new QToolBar;
        this->addToolBar(toolbar);

        auto person_action = toolbar->addAction(QString::fromStdWString(L"Personen"));
        auto book_action = toolbar->addAction(QString::fromStdWString(L"Bücher"));
        auto dvd_action = toolbar->addAction(QString::fromStdWString(L"DVDs"));
        auto lent_mediums_action = toolbar->addAction(QString::fromStdWString(L"Ausgeliehene Medien"));

        connect(person_action, SIGNAL(triggered()), this, SLOT(show_persons()));
        connect(book_action, SIGNAL(triggered()), this, SLOT(show_books()));
        connect(dvd_action, SIGNAL(triggered()), this, SLOT(show_dvds()));
        //connect(lent_mediums_action, SIGNAL(triggered()), this, SLOT(show_books()));//TODO

        central_table = new QTableView(this);
        central_table->setModel(current_model.get());


        this->setCentralWidget(central_table);

        this->menuBar()->addMenu(QString::fromStdWString(L"Bibliothek laden"));
        this->menuBar()->addMenu(QString::fromStdWString(L"Bibliothek sichern"));
    }

public slots:

    void show_books() {
        this->current_model = std::make_shared<library_book_view>(lib);
        central_table->setModel(current_model.get());
    }

    void show_persons() {
        this->current_model = std::make_shared<library_person_view>(lib);
        central_table->setModel(current_model.get());
    }

    void show_dvds() {
        this->current_model = std::make_shared<library_dvd_view>(lib);
        central_table->setModel(current_model.get());
    }

private:
    QTableView *central_table;
    std::shared_ptr<library> lib;
    std::shared_ptr<QAbstractTableModel> current_model;
};

int main(int argc, char *argv[]) {
    QApplication this_application(argc, argv);

    library_widget *window = new library_widget;

    window->show();

    return this_application.exec();
}

#include "main.moc"