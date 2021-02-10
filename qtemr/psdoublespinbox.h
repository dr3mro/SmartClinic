// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PSDOUBLESPINBOX_H
#define PSDOUBLESPINBOX_H

#include <QObject>
#include <QDoubleSpinBox>

class psDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit psDoubleSpinBox(QWidget *parent=nullptr);
private slots:
    void onValueChanged();
signals:
    void refreshView();
};

#endif // PSDOUBLESPINBOX_H
