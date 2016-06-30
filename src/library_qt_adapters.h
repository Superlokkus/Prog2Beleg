/*! @file library_qt_adapters.h
 * */

#ifndef PROG2BELEG_LIBRARY_QT_ADAPTERS_H
#define PROG2BELEG_LIBRARY_QT_ADAPTERS_H

#include <memory>

#include <QAbstractListModel>
#include "library.h"

class library_person_view : public QAbstractListModel {
public:
    library_person_view() = delete;

    library_person_view(std::shared_ptr<library> l) :
            QAbstractListModel(), library_(l) { }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return this->library_->all_persons().size();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole) {
            return {};
        }
        if (section == 0) {
            return {};
        }
        return {};
        //TODO
    }

private:
    std::shared_ptr<library> library_;
};


#endif //PROG2BELEG_LIBRARY_QT_ADAPTERS_H
