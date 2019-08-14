#ifndef SETDOSEDRUGNAMEWIDGET_H
#define SETDOSEDRUGNAMEWIDGET_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>


class setDoseDrugNameWidget : public QLabel
{
    Q_OBJECT
public:
    explicit setDoseDrugNameWidget(QWidget *parent = nullptr);

signals:
    void leftMouseButtonClicked();
    void rightMouseButtonClicked();

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // SETDOSEDRUGNAMEWIDGET_H
