/*! @file main.cpp
 *
 * */

#include <QtGui/QApplication>
#include <QtGui>
#include <QDockWidget>
#include <string>

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

        auto lend_action = toolbar->addAction(QString::fromStdWString(L"Leihe aus"));
        auto give_back_action = toolbar->addAction(QString::fromStdWString(L"Gib zurück"));

        connect(person_action, SIGNAL(triggered()), this, SLOT(show_persons()));
        connect(book_action, SIGNAL(triggered()), this, SLOT(show_books()));
        connect(dvd_action, SIGNAL(triggered()), this, SLOT(show_dvds()));
        //connect(lent_mediums_action, SIGNAL(triggered()), this, SLOT(show_books()));//TODO

        central_table = new QTableView(this);
        central_table->setModel(current_model.get());


        this->setCentralWidget(central_table);

        auto bib_menu = this->menuBar()->addMenu(QString::fromStdWString(L"Bibliothek"));
        auto load_lib_action = bib_menu->addAction(QString::fromStdWString(L"Bibliothek laden"));
        auto save_lib_action = bib_menu->addAction(QString::fromStdWString(L"Bibliothek sichern"));

        auto add_menu = this->menuBar()->addMenu(QString::fromStdWString(L"Hinzufügen"));
        auto add_person_action = add_menu->addAction(QString::fromStdWString(L"Person"));
        auto add_book_action = add_menu->addAction(QString::fromStdWString(L"Buch"));
        auto add_dvd_action = add_menu->addAction(QString::fromStdWString(L"DVD"));

        auto delete_menu = this->menuBar()->addMenu(QString::fromStdWString(L"Lösche"));
        auto delete_person_action = delete_menu->addAction(QString::fromStdWString(L"Person"));
        auto delete_book_action = delete_menu->addAction(QString::fromStdWString(L"Buch"));
        auto delete_dvd_action = delete_menu->addAction(QString::fromStdWString(L"DVD"));

        connect(add_person_action, SIGNAL(triggered()), this, SLOT(add_person()));
        connect(add_book_action, SIGNAL(triggered()), this, SLOT(add_book()));
        connect(add_dvd_action, SIGNAL(triggered()), this, SLOT(add_dvd()));
        connect(delete_book_action, SIGNAL(triggered()), this, SLOT(delete_book()));
        connect(delete_dvd_action, SIGNAL(triggered()), this, SLOT(delete_dvd()));
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

    void add_book() {
        bool ok = false;
        QString title = QInputDialog::getText(this, QString::fromStdWString(L"Buch hinzufügen"),
                                              QString::fromStdWString(L"Titel:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        QString author = QInputDialog::getText(this, QString::fromStdWString(L"Buch hinzufügen"),
                                               QString::fromStdWString(L"Autor:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        QString isbn = QInputDialog::getText(this, QString::fromStdWString(L"Buch hinzufügen"),
                                             QString::fromStdWString(L"Optional ISBN:"), QLineEdit::Normal, {}, &ok);
        this->lib->register_medium(std::make_shared<book>(medium::get_next_id(), title.toStdWString(),
                                                          author.toStdWString(), isbn.toStdWString()));
        //Signal layoutchanged and before abouttochange
    }

    void add_dvd() {
        bool ok = false;
        QString title = QInputDialog::getText(this, QString::fromStdWString(L"DVD hinzufügen"),
                                              QString::fromStdWString(L"Titel:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        QString director = QInputDialog::getText(this, QString::fromStdWString(L"DVD hinzufügen"),
                                                 QString::fromStdWString(L"Regisseur:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        this->lib->register_medium(std::make_shared<dvd>(medium::get_next_id(), title.toStdWString(),
                                                         director.toStdWString()));


    }

    void add_person() {
        bool ok = false;
        int id = QInputDialog::getInt(this, QString::fromStdWString(L"Person hinzufügen"),
                                      QString::fromStdWString(L"ID:"), 42, 0, 255, 1, &ok);
        if (!ok) {
            return;
        }
        QString name = QInputDialog::getText(this, QString::fromStdWString(L"Person hinzufügen"),
                                             QString::fromStdWString(L"Vorname:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        QString surname = QInputDialog::getText(this, QString::fromStdWString(L"Person hinzufügen"),
                                                QString::fromStdWString(L"Nachname:"), QLineEdit::Normal, {}, &ok);
        if (!ok) {
            return;
        }
        this->lib->register_person(std::make_shared<person>(id, name.toStdWString(),
                                                            surname.toStdWString()));
    }

    void delete_book() {
        QStringList items_by_string;
        auto books = this->lib->all_books();
        for (auto book : books) {
            items_by_string.append(
                    QString::fromStdWString(std::to_wstring(book->get_id()) + L" " + book->get_description()));
        }
        bool ok;
        QString item = QInputDialog::getItem(this, QString::fromStdWString(L"Lösche Buch"),
                                             QString::fromStdWString(L"Buch: "), items_by_string, 0, false, &ok);
        if (!ok) {
            return;
        }
        int i = items_by_string.indexOf(item);
        auto book = books.begin();
        if (i > -1 && i < books.size()) {
            std::advance(book, i);
            this->lib->erase_medium(*book);
        }
    }

    void delete_dvd() {
        QStringList items_by_string;
        auto dvds = this->lib->all_dvds();
        for (auto dvd : dvds) {
            items_by_string.append(
                    QString::fromStdWString(std::to_wstring(dvd->get_id()) + L" " + dvd->get_description()));
        }
        bool ok;
        QString item = QInputDialog::getItem(this, QString::fromStdWString(L"Lösche DVD"),
                                             QString::fromStdWString(L"DVD: "), items_by_string, 0, false, &ok);
        if (!ok) {
            return;
        }
        int i = items_by_string.indexOf(item);
        auto dvd = dvds.begin();
        if (i > -1 && i < dvds.size()) {
            std::advance(dvd, i);
            this->lib->erase_medium(*dvd);
        }
    }

//    void delete_medium() {
//        QStringList items_by_string;
//        auto mediums = this->lib->all_mediums();
//        for (auto medium : mediums) {
//            items_by_string.append(
//                    QString::fromStdWString(std::to_wstring(medium->get_id()) + L" " + medium->get_description()));
//        }
//        bool ok;
//        QString item = QInputDialog::getItem(this, QString::fromStdWString(L"Lösche Medium"),
//                                             QString::fromStdWString(L"Medium: "), items_by_string, 0, false, &ok);
//        if (!ok) {
//            return;
//        }
//        int i = items_by_string.indexOf(item);
//        auto medium = mediums.begin();
//        if (i > -1 && i < mediums.size()) {
//            std::advance(medium, i);
//            this->lib->erase_medium(*medium);
//        }
// }
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