// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
