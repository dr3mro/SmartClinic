#include "conditionsedit.h"
#include "ui_conditionsedit.h"

conditionsEdit::conditionsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conditionsEdit)
{
    ui->setupUi(this);
    sqlbase = new sqlBase(this,"conditions",false);
    model = sqlbase->getConditionsModel(model);
    proxy_model = new CheckableSortFilterProxyModel(this);
    proxy_model->setSourceModel(model);
    ui->tableView->setModel(proxy_model);
    ui->tableView->hideColumn(0);
    ui->tableView->setColumnWidth(1,20);
    ui->buttonAdd->setEnabled(false);
    ui->lineEdit->setFocus(Qt::OtherFocusReason);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

conditionsEdit::~conditionsEdit()
{
    delete ui;
    delete proxy_model;
    delete model;
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("conditions");
    emit reload();
}

void conditionsEdit::show()
{
    QDialog::show();
    wm.centerOnScreen(this);
}

void conditionsEdit::on_buttonAdd_clicked()
{
    int _id = getModelLength();
    QString name = ui->lineEdit->text().simplified();
    addCondition(name,_id);
}

void conditionsEdit::addCondition(QString name, int _id)
{
    sqlbase->addCondition(name,_id);
    ui->lineEdit->clear();
    model->select();
}

void conditionsEdit::on_lineEdit_textChanged(const QString &arg1)
{
    int condLen = arg1.length();
    ui->buttonAdd->setEnabled( condLen > 1 );
}

int conditionsEdit::getModelLength()
{
    return proxy_model->rowCount();
}

void conditionsEdit::on_lineEdit_returnPressed()
{
    int _id = getModelLength();
    QString name = ui->lineEdit->text().simplified();
    addCondition(name,_id);
}
