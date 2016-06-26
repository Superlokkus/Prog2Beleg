/*! @file main.cpp
 *
 * */

#include <QtGui/QApplication>
#include <QDeclarativeView>


int main(int argc, char* argv[]) {
    QApplication this_application(argc,argv);

    QDeclarativeView view ;
    view.setSource(QUrl::fromLocalFile("main_window.qml"));
    view.show();

    QString foo = {"foof"};
    foo.toStdWString();

    return this_application.exec();
}