#include "searchwidget.h"
#include "ui_searchwidget.h"

searchWidget::searchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchWidget)
{
    ui->setupUi(this);
    validator.setRegExp(QRegExp("^\\S(.*\\S)?$"));
    ui->filterLineEdit->setValidator(&validator);

    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    setFilter(reg.value("filterColumn").toInt());
    isFuzzySearchEnabled = reg.value("enableFuzzySearch").toBool();
    ui->fuzzyCheckBox->setChecked(isFuzzySearchEnabled);

    ui->PatientListTableView->setConnection();
    ui->filtersWidget->hide();
    ui->PatientListTableView->hideColumn(2);

//    qRegisterMetaType<QList<QPersistentModelIndex> >("QList<QPersistentModelIndex>");
//    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");

    connect(this,SIGNAL(loadPatient()),ui->PatientListTableView,SLOT(loadPatient()));
    connect(this,SIGNAL(updatePatients()),ui->PatientListTableView,SLOT(updatePatients()));
    connect(ui->filterLineEdit,SIGNAL(focusPatientTable()),this,SLOT(focusList()));
    connect(ui->PatientListTableView,SIGNAL(focusFilterBox()),this,SLOT(focusFilter()));
    connect(ui->PatientListTableView,SIGNAL(setFilter(int)),this,SLOT(setFilter(int)));

}

void searchWidget::selectRow(int row)
{
    ui->PatientListTableView->selectRow(row);
}

void searchWidget::clearFilter()
{
    ui->filterLineEdit->clear();
}

void searchWidget::focusFilter()
{
    ui->filterLineEdit->setFocus(Qt::OtherFocusReason);
    int row = ui->PatientListTableView->currentIndex().row();
    ui->PatientListTableView->selectRow((row >=0)? row:0 );
}

void searchWidget::focusList()
{
    ui->PatientListTableView->setFocus(Qt::OtherFocusReason);
    int row = ui->PatientListTableView->currentIndex().row();
    ui->PatientListTableView->selectRow((row >=0)? row:0 );
}

void searchWidget::setID(int ID)
{
    ui->PatientListTableView->setID(ID);
}

void searchWidget::closeDatabase()
{
    ui->PatientListTableView->closeDatabase();
}

void searchWidget::reConnectDatabase()
{
    ui->PatientListTableView->reOpenDatabase();
    //ui->PatientListTableView->setConnection();
}

void searchWidget::toggleListHeader(bool visible)
{
    ui->PatientListTableView->horizontalHeader()->setVisible(visible);
}

void searchWidget::updatePatientList()
{
    ui->PatientListTableView->updatePatients();
}

searchWidget::~searchWidget()
{
    delete ui;
}

void searchWidget::setFilter(int fc_)
{
    switch (fc_) {
    case 0:
        ui->filterByIDRadio->setChecked(true);
        break;
    case 1:
        ui->filterByNameRadio->setChecked(true);
        break;
    case 2:
        ui->filterByMobileRadio->setChecked(true);
        break;
    default:
        break;
    }
}

void searchWidget::showHideFilters(bool checked)
{
    filtersVisibility=checked;
    ui->filtersWidget->setVisible(checked);
}

void searchWidget::on_filterLineEdit_textChanged(const QString &arg1)
{
    // Create a copy of static string
    QString str = arg1;

    // replace ؟ with ? to fix arabic search
    str.replace(QString("؟"),QString("?"));
    if(!filtersVisibility)
    {
        // create a regexp of numbers
        QRegExp re("\\d*");

        // check if str is a phone number
        if (re.exactMatch(str) && ( str.startsWith("0",Qt::CaseInsensitive) || str.startsWith("+",Qt::CaseInsensitive)))
        {
            ui->PatientListTableView->setFiletrByMobile();
            ui->PatientListTableView->sortByColumn(0,Qt::AscendingOrder);
        }
        // check if str is ID
        else if ( re.exactMatch(str))
        {
            ui->PatientListTableView->setFilterByID();
            ui->PatientListTableView->sortByColumn(0,Qt::AscendingOrder);
        }
        // if not then it should be a name
        else
        {
            ui->PatientListTableView->setFilterByName();
            ui->PatientListTableView->sortByColumn(1,Qt::AscendingOrder);
        }
        //setFilter
    }
    // enable fuzzy search

    if(isFuzzySearchEnabled)
    {
        str.replace(" ","*");
        str.replace(QRegExp("[آ|أ|إ|ا]"),"[آ,أ,إ,ا]");
        str.replace(QRegExp("[ه|ة]"),"[ه,ة]");
        str.replace(QRegExp("[ى|ي]"),"[ى,ي]");
        str.replace(QRegExp("بو"),"[بو,بو ]");
        str.replace(QRegExp("عبد"),"[عبد,عبد ]");
        //str.replace(QRegExp("[ؤ|و]"),"[ؤ,و]");
    }


    ui->PatientListTableView->FilterPatients(str);
    ui->PatientListTableView->selectRow(0);
}

void searchWidget::on_filterByNameRadio_toggled(bool checked)
{
    if ( checked )
        ui->PatientListTableView->setFilterByName();
    filterToggled();
}

void searchWidget::on_filterByIDRadio_toggled(bool checked)
{
    if ( checked )
        ui->PatientListTableView->setFilterByID();
    filterToggled();
}

void searchWidget::on_filterByMobileRadio_toggled(bool checked)
{
    if ( checked )
        ui->PatientListTableView->setFiletrByMobile();
    filterToggled();
}

void searchWidget::filterToggled()
{
    ui->filterLineEdit->setFocus(Qt::OtherFocusReason);
    int row = ui->PatientListTableView->currentIndex().row();
    ui->PatientListTableView->selectRow((row >=0)? row:0 );
}

void searchWidget::on_filterLineEdit_returnPressed()
{
    if (ui->filterLineEdit->text().length() > 0 )
    {
        emit loadPatient();
        emit closePatientList();
    }
}

void searchWidget::on_PatientListTableView_activated(const QModelIndex &index)
{
    int ID = ui->PatientListTableView->getSelectedPatientID(&index);
    emit loadPatient(ID);
    emit closePatientList();
}

void searchWidget::on_fuzzyCheckBox_clicked(bool checked)
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    isFuzzySearchEnabled = checked;
    reg.setValue("enableFuzzySearch",isFuzzySearchEnabled);
    on_filterLineEdit_textChanged(ui->filterLineEdit->text());
}
