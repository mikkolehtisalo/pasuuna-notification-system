#include "settings.h"
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QDebug>

Settings::Settings()
{
    settings = new QSettings("pasuuna.ini", QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
}

Settings::~Settings() {
    delete settings;
}

QString Settings::getString(const QString key) {
    QString result = settings->value(key).toString();
    qDebug() << "Settings::getString" << key << result;
    return result;
}

int Settings::getInt(const QString key) {
    int result = settings->value(key).toInt();
    qDebug() << "Settings::getInt" << key << result;
    return result;
}

QStringList Settings::getStringList(const QString key) {
    QStringList result = settings->value(key).toStringList();
    qDebug() << "Settings::getStringList" << key << result;
    return result;
}
