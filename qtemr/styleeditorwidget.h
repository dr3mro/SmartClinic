// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
