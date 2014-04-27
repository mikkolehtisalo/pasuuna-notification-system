#include "checker.h"
#include "settings.h"
#include <QTimer>
#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    Settings se;
    QApplication app(argc, argv);
    QTimer *timer = new QTimer;
    Checker c;
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(check()));
    timer->start(se.getInt("checkInterval"));
    app.setQuitOnLastWindowClosed(false);
    return app.exec();
}
