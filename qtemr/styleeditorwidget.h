#ifndef STYLEEDITORWIDGET_H
#define STYLEEDITORWIDGET_H

#include <QObject>
#include <QWidget>
#include <QColorDialog>

#include "m_scolorbutton.h"

class StyleEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StyleEditorWidget(QWidget *parent = nullptr);

signals:

public slots:
    void buttonSetColor();
private:
    QColorDialog dialog;
};

#endif // STYLEEDITORWIDGET_H
