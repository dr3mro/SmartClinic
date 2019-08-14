#ifndef XCOMBOBOX_H
#define XCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <datahelper.h>

class xComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit xComboBox(QWidget*parent=nullptr);
    void setUserSpeciality(int us);
    void setComboName(QString cn);
public slots:
    void makeReadWrite(bool rw);
private:
    QString comboName;
    int userSpeciality;
};
#endif // XCOMBOBOX_H
