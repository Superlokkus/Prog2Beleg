/*! @file library_qt_adapters.h
 * */

#ifndef PROG2BELEG_LIBRARY_QT_ADAPTERS_H
#define PROG2BELEG_LIBRARY_QT_ADAPTERS_H

#include <memory>
#include <iterator>

#include <QAbstractTableModel>
#include "library.h"

class library_person_view : public QAbstractTableModel {
public:
    library_person_view() = delete;

    library_person_view(std::shared_ptr<library> l) :
            QAbstractTableModel(), library_(l) { }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return this->library_->all_persons().size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        auto persons = library_->all_persons();
        if (persons.size() < index.row()) {
            return {};
        }
        auto person = persons.cbegin();
        std::advance(person, index.row());
        if (index.column() == 0) {
            return QVariant{QString::fromStdWString(person->get()->name)};
        } else if (index.column() == 1) {
            return QVariant{QString::fromStdWString(person->get()->surname)};
        }
        return {};

    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 2;
    }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
                case 0:
                    return QVariant{QString::fromStdWString(L"Vorname")};
                    break;
                case 1:
                    return QVariant{QString::fromStdWString(L"Nachname")};
                    break;
                default:
                    break;
            }
        }

        return QVariant{};
    }


private:
    std::shared_ptr<library> library_;
};

class library_book_view : public QAbstractTableModel {
public:
    library_book_view() = delete;

    library_book_view(std::shared_ptr<library> l) :
            QAbstractTableModel(), library_(l) { }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return this->library_->all_books().size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        auto books = library_->all_books();
        if (books.size() < index.row()) {
            return {};
        }
        auto book = books.cbegin();
        std::advance(book, index.row());
        if (index.column() == 0) {
            return QVariant{QString::fromStdWString(book->get()->title)};
        } else if (index.column() == 1) {
            return QVariant{QString::fromStdWString(book->get()->author)};
        } else if (index.column() == 2) {
            return QVariant{QString::fromStdWString(book->get()->isbn)};
        }
        return {};

    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 3;
    }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
                case 0:
                    return QVariant{QString::fromStdWString(L"Titel")};
                    break;
                case 1:
                    return QVariant{QString::fromStdWString(L"Autor")};
                    break;
                case 2:
                    return QVariant{QString::fromStdWString(L"ISBN")};
                    break;
                default:
                    break;
            }
        }

        return QVariant{};
    }


private:
    std::shared_ptr<library> library_;
};

class library_dvd_view : public QAbstractTableModel {
public:
    library_dvd_view() = delete;

    library_dvd_view(std::shared_ptr<library> l) :
            QAbstractTableModel(), library_(l) { }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return this->library_->all_dvds().size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        auto dvds = library_->all_dvds();
        if (dvds.size() < index.row()) {
            return {};
        }
        auto dvd = dvds.cbegin();
        std::advance(dvd, index.row());
        if (index.column() == 0) {
            return QVariant{QString::fromStdWString(dvd->get()->title)};
        } else if (index.column() == 1) {
            return QVariant{QString::fromStdWString(dvd->get()->director)};
        }
        return {};

    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 2;
    }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
                case 0:
                    return QVariant{QString::fromStdWString(L"Titel")};
                    break;
                case 1:
                    return QVariant{QString::fromStdWString(L"Regisseur")};
                    break;
                default:
                    break;
            }
        }

        return QVariant{};
    }


private:
    std::shared_ptr<library> library_;
};



#endif //PROG2BELEG_LIBRARY_QT_ADAPTERS_H
