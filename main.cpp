#include <QtGui/QApplication>
#include <QDeclarativeView>


int main(int argc, char* argv[]) {
    QApplication this_application(argc,argv);

    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl::fromLocalFile("main_window.qml"));
    view->show();

    return this_application.exec();
}