#include "message.h"
#include "ui_message.h"
#include "settings.h"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QVariant>

Message::Message(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Message)
{
    Settings se;
    ui->setupUi(this);

    // Setting the window title and the header on the message form
    QString windowTitle = se.getString("windowTitle");
    ui->label_3->setText(windowTitle);
    ui->label_4->setText(windowTitle);
    this->setWindowTitle(windowTitle);

    // Setting the logo
    ui->label_2->setPixmap(QPixmap(se.getString("logoFile")));

    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

Message::~Message()
{
    delete ui;
}

void Message::setMessage(const QString message) {
    ui->textEdit->setText(message);
}

