#ifndef CHECKER_H
#define CHECKER_H

#include <QObject>
#include <QNetworkReply>
#include <QSslError>
#include <QList>
#include "checker.h"
#include <QNetworkAccessManager>

class Checker : public QObject
{
    Q_OBJECT
public:
    Checker();
    ~Checker();
public slots:
    void check();
    void replyFinished(QNetworkReply *reply);
private:
    QString previousMessage;
    QNetworkAccessManager *accessManager;
    QSslConfiguration* sslConfiguration;
    bool isWorking;
    QUrl accessUrl;
};

#endif // CHECKER_H
