#include "text_style_editor_widget.h"
#include "ui_text_style_editor_widget.h"

text_style_editor_widget::text_style_editor_widget(QWidget *parent) :
    StyleEditorWidget(parent),
    ui(new Ui::text_style_editor_widget)
{
    ui->setupUi(this);
    ui->color_normal_button->m_connect(this,ui->color_normal_text);
    ui->color_hover_button->m_connect(this,ui->color_hover_text);
    ui->color_focus_button->m_connect(this,ui->color_focus_text);
    ui->color_disabled_button->m_connect(this,ui->color_disabled_text);
    ui->color_warning_button->m_connect(this,ui->color_warning_text);
    ui->color_error_button->m_connect(this,ui->color_error_text);
}

text_style_editor_widget::~text_style_editor_widget()
{
    delete ui;
}

mStyler::Text text_style_editor_widget::getStyle()
{
    mStyler::Text text;
    text.color_normal = ui->color_normal_text->text();
    text.color_hover = ui->color_hover_text->text();
    text.color_focus = ui->color_focus_text->text();
    text.color_disabled = ui->color_disabled_text->text();
    text.color_warning = ui->color_warning_text->text();
    text.color_error = ui->color_error_text->text();
    return text;
}

void text_style_editor_widget::putStyle(const mStyler::Text &text)
{
    ui->color_normal_text->setText(text.color_normal);
    ui->color_hover_text->setText(text.color_hover);
    ui->color_focus_text->setText(text.color_focus);
    ui->color_disabled_text->setText(text.color_disabled);
    ui->color_warning_text->setText(text.color_warning);
    ui->color_error_text->setText(text.color_error);
}
