// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef RICHTEXTEDITOR_H
#define RICHTEXTEDITOR_H

#include <QWidget>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include "colorpicker.h"
#include "msettings.h"

namespace Ui {
class richTextEditor;
}

class richTextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit richTextEditor(QWidget* parent= nullptr);
    void syncFontPoint(QString font,
                       int point,
                       bool bold,
                       bool italic,
                       bool underLine,
                       bool strike,
                       bool highlight,
                       bool alignLeft,
                       bool alignCenter,
                       bool alignRight,
                       bool upper);
    ~richTextEditor();

private slots:
    void setBackgroundColor(QColor color);
    void setForegroundColor(QColor color);
    void resetFont();
    void fadeout();
    void decreaseOpacity();
    void noFadeOut();
    void reGainFocus();
    void searchGoogle();

public slots:

private:
    Ui::richTextEditor *ui;
    colorPicker *cp1;
    colorPicker *cp2;
    QTimer *timeout;
    QTimer *fade;
    int x_cord;
    int y_cord;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *o, QEvent *e);

signals:
    void setFGcolor(QColor);
    void setBGcolor(QColor);
    void insertChar(QString);
    void deleteText();
    void setPointPlusOne();
    void setPointMinusOne();
    void redFlagHighLight();
    void greenFlagHighLight();
    void blueFlagHighLight();
    QString getSelectedText();
    void clearSelection();

};

#endif // RICHTEXTEDITOR_H
