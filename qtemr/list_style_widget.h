#ifndef LIST_STYLE_WIDGET_H
#define LIST_STYLE_WIDGET_H

#include "styleeditorwidget.h"
#include "mstyler.h"
namespace Ui {
class List_style_widget;
}

class List_style_widget : public StyleEditorWidget
{
    Q_OBJECT

public:
    explicit List_style_widget(QWidget *parent = nullptr);
    ~List_style_widget();
    mStyler::List getStyle();
    void putStyle(const mStyler::List &list);

private:
    Ui::List_style_widget *ui;
};

#endif // LIST_STYLE_WIDGET_H
