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

private:
    std::shared_ptr<library> library_;
};


#endif //PROG2BELEG_LIBRARY_QT_ADAPTERS_H
