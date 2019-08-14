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
