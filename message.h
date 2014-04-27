#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDialog>
#include <QString>

namespace Ui {
class Message;
}

class Message : public QDialog
{
    Q_OBJECT
    
public:
    explicit Message(QWidget *parent = 0);
    ~Message();
    void setMessage(const QString message);
    
private:
    Ui::Message *ui;
};

#endif // MESSAGE_H
