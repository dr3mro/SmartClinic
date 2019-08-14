#ifndef MFONTCOMBOBOX_H
#define MFONTCOMBOBOX_H

#include <QObject>
#include <QWidget>
#include <QFontComboBox>


class mFontComboBox : public QFontComboBox
{
    Q_OBJECT
public:
    explicit mFontComboBox(QWidget *parent=nullptr);
};

#endif // MFONTCOMBOBOX_H
