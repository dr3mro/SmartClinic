// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
