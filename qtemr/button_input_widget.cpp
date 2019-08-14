#include "button_input_widget.h"
#include "ui_button_input_widget.h"

button_input_widget::button_input_widget(QWidget *parent) :
    StyleEditorWidget(parent),
    ui(new Ui::button_input_widget)
{
    ui->setupUi(this);
    ui->color_normal_button->m_connect(this,ui->color_normal_text);
    ui->color_hover_button->m_connect(this,ui->color_hover_text);
    ui->color_focus_button->m_connect(this,ui->color_focus_text);
    ui->color_disabled_button->m_connect(this,ui->color_disabled_text);
    ui->color_warning_button->m_connect(this,ui->color_warning_text);
    ui->color_error_button->m_connect(this,ui->color_error_text);
    ui->border_color_normal_button->m_connect(this,ui->border_color_normal_text);
    ui->border_color_hover_button->m_connect(this,ui->border_color_hover_text);
    ui->border_color_focus_button->m_connect(this,ui->border_color_focus_text);
    ui->border_color_diabled_button->m_connect(this,ui->border_color_diabled_text);
}

button_input_widget::~button_input_widget()
{
    delete ui;
}

mStyler::Element button_input_widget::getStyle()
{
    mStyler::Element element;
    element.color_normal = ui->color_normal_text->text();
    element.color_hover = ui->color_hover_text->text();
    element.color_focus = ui->color_focus_text->text();
    element.color_disabled = ui->color_disabled_text->text();
    element.color_warning = ui->color_warning_text->text();
    element.color_error = ui->color_error_text->text();
    element.border_color_normal = ui->border_color_normal_text->text();
    element.border_color_hover = ui->border_color_hover_text->text();
    element.border_color_focus = ui->border_color_focus_text->text();
    element.border_color_disabled = ui->border_color_diabled_text->text();
    element.border_width = ui->border_width->value();
    element.border_radius = ui->border_radius->value();
    return element;
}

void button_input_widget::putStyle(const mStyler::Element &element)
{
    ui->color_normal_text->setText(element.color_normal);
    ui->color_hover_text->setText(element.color_hover);
    ui->color_focus_text->setText(element.color_focus);
    ui->color_disabled_text->setText(element.color_disabled);
    ui->color_warning_text->setText(element.color_warning);
    ui->color_error_text->setText(element.color_error);
    ui->border_color_normal_text->setText(element.border_color_normal);
    ui->border_color_hover_text->setText(element.border_color_hover);
    ui->border_color_focus_text->setText(element.border_color_focus);
    ui->border_color_diabled_text->setText(element.border_color_disabled);
    ui->border_width->setValue(element.border_width);
    ui->border_radius->setValue(element.border_radius);
}
