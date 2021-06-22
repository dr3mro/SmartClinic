#include "expandeasyeditor.h"
#include "ui_expandeasyeditor.h"

ExpandEasyEditor::ExpandEasyEditor(QString &expandShortcut, QString &expandContents, bool &save , QWidget *parent) :
    QDialog(parent),
    m_ExpandShortcut(expandShortcut),
    m_ExpandContents(expandContents),
    m_Save(save),
    ui(new Ui::ExpandEasyEditor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));
    ui->expanderShortcutView->setText(m_ExpandShortcut);
    ui->expanderContents->setText(m_ExpandContents);
    connect(ui->btn_save,&QPushButton::clicked,this,&ExpandEasyEditor::save);
    connect(ui->btn_cancel,&QPushButton::clicked,this,&ExpandEasyEditor::close);
}

ExpandEasyEditor::~ExpandEasyEditor()
{
    delete ui;
}

void ExpandEasyEditor::save()
{
    m_Save = true;
    m_ExpandContents = ui->expanderContents->toHtml();
    close();
}
