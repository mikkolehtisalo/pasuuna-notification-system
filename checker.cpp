#include "checker.h"
#include "message.h"
#include "ui_message.h"
#include "settings.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QSsl>
#include <QSslError>
#include <QList>
#include <QFile>
#include <QByteArray>
#include <QSslCipher>
#include <QSslSocket>
#include <QSettings>

Checker::Checker() {

    Settings se;

    this->previousMessage = "";
    this->isWorking = false;
    this->accessUrl = QUrl(se.getString("accessUrl"));

    accessManager = new QNetworkAccessManager(this);

    // Signal for finishing network access
    connect(accessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    // SSL/TLS configuration
    this->sslConfiguration = new QSslConfiguration;
    sslConfiguration->setProtocol(QSsl::SecureProtocols);                // QT 5.0.1: TlsV1SslV3

    // CA Certs
    QList<QSslCertificate> certs = QSslCertificate::fromPath(QString(se.getString("certificateFile")), QSsl::Pem);
    sslConfiguration->setPeerVerifyMode(QSslSocket::VerifyPeer);         // Default behaviour for clients
    sslConfiguration->setCaCertificates(certs);

    // Ciphers
    QList<QSslCipher> ciphers;
    QStringList cipherList = se.getStringList("cipherList");
    foreach (QString cipherName, cipherList) {
        QSslCipher cipher = QSslCipher(cipherName,QSsl::SecureProtocols);
        qDebug() << "Instantiated" << cipherName << ":" << cipher.isNull();
        if (!cipher.isNull()) {
            ciphers.append(cipher);
        }
    }
    sslConfiguration->setCiphers(ciphers);

}

Checker::~Checker() {
    disconnect(accessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    delete this->sslConfiguration;
    delete this->accessManager;
}

void Checker::check() {
    // Will actually check only if no previous operation is in progress
    if (this->isWorking==false) {
        this->isWorking=true;
        // Init the request with parameters
        QNetworkRequest request(this->accessUrl);
        request.setSslConfiguration(*this->sslConfiguration);

        // Check the resource
        QNetworkReply* reply = this->accessManager->get(request);
        qDebug() << "Reply object:" << reply;
    }
}

void Checker::replyFinished(QNetworkReply *reply) {
    if (QNetworkReply::NoError == reply->error()) {
        qDebug() << "Connection used cipher:" << reply->sslConfiguration().sessionCipher();

        QString message= QString::fromUtf8(reply->readAll());
        qDebug() << "Message from server: \n==================\n" << message << "\n==================\n";

        if (message.length()>50 && previousMessage!=message) {
            Message *dialog = new Message;
            dialog->setMessage(message);
            dialog->show();
            dialog->raise();
            dialog->activateWindow();
            previousMessage = message;
        }
    } else {
        qDebug() << "Error:" << reply->errorString();
    }

    reply->close();
    reply->deleteLater();
    this->isWorking=false;
}

