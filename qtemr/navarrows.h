// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef NAVARROWS_H
#define NAVARROWS_H

#include <QObject>

#include <QToolButton>
#include <QMouseEvent>


class navArrows : public QToolButton
{
    Q_OBJECT
public:
    explicit navArrows(QWidget *parent=nullptr);

public slots:

private slots:

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void rightButtonClicked();
    void leftButtonClicked();
};

#endif // NAVARROWS_H
