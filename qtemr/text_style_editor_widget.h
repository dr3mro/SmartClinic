#ifndef TEXT_STYLE_EDITOR_WIDGET_H
#define TEXT_STYLE_EDITOR_WIDGET_H

#include "styleeditorwidget.h"
#include "mstyler.h"

namespace Ui {
class text_style_editor_widget;
}

class text_style_editor_widget : public StyleEditorWidget
{
    Q_OBJECT

public:
    explicit text_style_editor_widget(QWidget *parent = nullptr);
    ~text_style_editor_widget();
    mStyler::Text getStyle();
    void putStyle(const mStyler::Text &text);

private:
    Ui::text_style_editor_widget *ui;
};

#endif // TEXT_STYLE_EDITOR_WIDGET_H
