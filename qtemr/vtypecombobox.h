#ifndef VTYPECOMBOBOX_H
#define VTYPECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <settingsclass.h>
class vTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit vTypeComboBox(QWidget *parent=nullptr);
    void fillContent(int maxFollow);
public slots:
    void goUp();
    void goDown();
};

#endif // VTYPECOMBOBOX_H
