#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QString>
#include <QStringList>

class Settings
{
public:
    Settings();
    ~Settings();
    QString getString(const QString key);
    int getInt(const QString key);
    QStringList getStringList(const QString key);
private:
    QSettings *settings;
};

#endif // SETTINGS_H
