#include "list_style_widget.h"
#include "ui_list_style_widget.h"

List_style_widget::List_style_widget(QWidget *parent) :
    StyleEditorWidget(parent),
    ui(new Ui::List_style_widget)
{
    ui->setupUi(this);
    ui->selected_item_color_button->m_connect(this,ui->selected_item_color_text);
    ui->toolbutton_background_color_button->m_connect(this,ui->toolbutton_background_color_text);
    ui->messagebox_text_color_button->m_connect(this,ui->messagebox_text_color_text);
    ui->messagebox_background_color_button->m_connect(this,ui->messagebox_background_color_text);
}

List_style_widget::~List_style_widget()
{
    delete ui;
}

mStyler::List List_style_widget::getStyle()
{
    mStyler::List list;
    list.selected_item_color = ui->selected_item_color_text->text();
    list.selected_item_text_color = ui->selected_item_text_color_text->text();
    list.messagebox_background_color = ui->messagebox_background_color_text->text();
    list.toolbutton_color_normal = ui->toolbutton_background_color_text->text();
    list.messagebox_text_color = ui->messagebox_text_color_text->text();
    list.enable3D = ui->enable3D->isChecked();
    return list;
}

void List_style_widget::putStyle(const mStyler::List &list)
{
    ui->selected_item_color_text->setText(list.selected_item_color);
    ui->selected_item_text_color_text->setText(list.selected_item_text_color);
    ui->messagebox_background_color_text->setText(list.messagebox_background_color);
    ui->toolbutton_background_color_text->setText(list.toolbutton_color_normal);
    ui->messagebox_text_color_text->setText(list.messagebox_text_color);
    ui->enable3D->setChecked(list.enable3D);
}
