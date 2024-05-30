// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "patienttable.h"
#include "qabstractitemmodel.h"
#include <algorithm>
#include <cstdlib>

patientTable::patientTable(QWidget *parent):QTableView(parent),
  proxy_model(new QSortFilterProxyModel(this))
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    filterColumn =  reg.value("filterColumn").toInt();

    loadingIsFinished = false;
    connect(&watcher,&QFutureWatcher<QStandardItemModel*>::finished, this, &patientTable::updatePatientsCompleted,Qt::QueuedConnection);
    connect(&initWatcher,&QFutureWatcher<QStandardItemModel*>::finished, this,&patientTable::setMyModel,Qt::QueuedConnection);
    connect (this,&patientTable::loadSelectedPatient,this,&patientTable::activated,Qt::QueuedConnection);

    proxy_model->setFilterKeyColumn(filterColumn);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);

    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSortCaseSensitivity(Qt::CaseInsensitive);
    viewport()->installEventFilter(this);
}


void patientTable::setFilterByName()
{
    if(loadingIsFinished)
        proxy_model->setFilterKeyColumn(1);
    filterColumn = 1;
}

void patientTable::setFilterByID()
{
    if(loadingIsFinished)
        proxy_model->setFilterKeyColumn(0);
    filterColumn = 0;
}

void patientTable::setFiletrByMobile()
{
    if(loadingIsFinished)
        proxy_model->setFilterKeyColumn(2);
    filterColumn = 2;
}

void patientTable::updatePatients()
{
    if(modelFuture.isRunning())
        return;

    proxy_model->setSourceModel(nullptr);
#if QT_VERSION >= 0x060000
    modelFuture = QtConcurrent::run(&sqlBase::getPatientsTableModel,sqlbase);
#else
    modelFuture = QtConcurrent::run(sqlbase,&sqlBase::getPatientsTableModel);
#endif

    watcher.setFuture(modelFuture);
}

bool patientTable::eventFilter(QObject *o, QEvent *e)
{
    int _ID,row;
    bool deceased;
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
    if ( (o == this->viewport() ) && ( e->type() == QEvent::MouseButtonDblClick ) && ( mouseEvent->buttons() == Qt::MiddleButton ||
                                                                                     ( mouseEvent->button() == Qt::LeftButton && keyEvent->modifiers() == Qt::ShiftModifier)) )
    {
        QModelIndex cell =  selectionModel()->currentIndex();
        row = cell.row();
        _ID = proxy_model->data(cell.sibling(row,0)).toInt();
        if ( !cell.isValid() || _ID == 0 )
            return QObject::eventFilter(o,e);
        deceased = sqlbase->getDeceasedList().contains(QString::number(_ID));
        sqlbase->toggleDeceased(_ID,(deceased)? 0:1,row);
        clearSelection();
    }
    return QObject::eventFilter(o,e);
}

//QModelIndexList patientTable::getSortedMatchedListOfIndexes(const int &row)
//{
//    auto start = proxy_model->index(0,0);
//    auto matchingString = QStringLiteral("%1").arg(row+1, 5, 10, QLatin1Char('0'));

//    auto indexes = proxy_model->match(start,Qt::MatchExactly,matchingString);

//    if (indexes.count() > 1)
//        std::sort(indexes.begin(),indexes.end(),
//              [](const QModelIndex &a, const QModelIndex &b)
//                {
//                    return a.row() > b.row();
//                });

//    return indexes;
//}

void patientTable::keyPressEvent(QKeyEvent *ke)
{
    if ( ( ke->key() == Qt::Key_Up ) && ( currentIndex().row() == 0  ))
        emit focusFilterBox();
    QTableView::keyPressEvent(ke);
}

void patientTable::updatePatientsCompleted()
{
    proxy_model->setSourceModel(model);
    hideColumn(2);
    mSelectRow(ID-1);
    this->setColumnWidth(0,sizeHintForColumn(0));
    repaint();
}

void patientTable::setMyModel()
{
    model = initModelFuture.result();
    model->setHorizontalHeaderLabels( QStringList() << "ID" << "Name " );  
    proxy_model->setSourceModel(model);

    setModel(proxy_model);

    emit setFilter(filterColumn);
    emit modelLoadingFinished();
}

void patientTable::tweaksAfterModelLoadingIsFinished()
{
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->horizontalHeader()->setSectionHidden(2,true);

  this->horizontalHeader()->setStretchLastSection(true);
  this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeMode::ResizeToContents);
  this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeMode::Stretch);

  this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  this->setSelectionMode(QAbstractItemView::SingleSelection);
  this->setSelectionBehavior(QAbstractItemView::SelectRows );
  this->hideColumn(2);
  this->mSelectRow(0);
  loadingIsFinished = true;
}

void patientTable::loadPatient()
{
    if ( currentIndex().row() == -1 )
        return;

    if ( proxy_model->rowCount() > 0 )
        emit loadSelectedPatient(currentIndex());
}

void patientTable::setPatientIcon(bool b,int row)
{
    QModelIndex cell = selectionModel()->currentIndex().sibling(row,1);
    if (b)
        proxy_model->setData(cell,QIcon(":/Graphics/ionicons/android-star.png"),Qt::DecorationRole);
    else
        proxy_model->setData(selectionModel()->currentIndex().sibling(row,1),QIcon(),Qt::DecorationRole);
}

void patientTable::setID(int id)
{
    ID=id;
}

int patientTable::getID()
{
    return ID;
}

int patientTable::getSelectedPatientID(const QModelIndex *index)
{
    return proxy_model->data(index->sibling(index->row(),0)).toInt();
}

void patientTable::FilterPatients(QString filter)
{
    proxy_model->setFilterWildcard(filter);
}


void patientTable::setConnection(QString conname)
{
    connectionName = conname;
    sqlbase = new sqlBase(this,connectionName,false);
    sqlbase->createPatientItemModel();
    //qRegisterMetaType<QVector<int> >("QVector<int>");
    connect (sqlbase,SIGNAL(patientIconSet(bool,int)),this,SLOT(setPatientIcon(bool,int)));
    connect(this,&patientTable::modelLoadingFinished,this,&patientTable::tweaksAfterModelLoadingIsFinished,Qt::QueuedConnection);
#if QT_VERSION >= 0x060000
    initModelFuture = QtConcurrent::run(&sqlBase::getPatientsTableModel,sqlbase);
#else
    initModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getPatientsTableModel);
#endif

    initWatcher.setFuture(initModelFuture);
}

void patientTable::closeDatabase()
{
    clearSelection();
    delete proxy_model;
    delete model;
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase(connectionName);
}

void patientTable::reOpenDatabase()
{
    setConnection(connectionName);
}
//
//int mSelectRowCompare(const void* a, const void* b)
//{
//    const int* x = (int*) a;
//    const int* y = (int*) b;

//    if (*x < *y)
//        return 1;
//    else if (*x > *y)
//        return -1;

//    return 0;
//}
//std::qsort(&indexes,indexes.size(),sizeof(decltype(indexes)::value_type),mSelectRowCompare);


#define DISABLESORTEDSELECT 0
void patientTable::mSelectRow(int row)
{
#if DISABLESORTEDSELECT
    selectRow(row);
#else
    if (this->horizontalHeader()->sortIndicatorOrder() == Qt::SortOrder::AscendingOrder
            && proxy_model->sortColumn() == 0){
        selectRow(row);
    }else if(proxy_model != nullptr){
        auto str = QStringLiteral("%1").arg(row+1, 5, 10, QLatin1Char('0'));
        for(int _row=0; _row < proxy_model->rowCount(); _row++){
            if(proxy_model->index(_row,0).isValid() &&
                    proxy_model->index(_row,0).data(Qt::DisplayRole).toString() == str){
                selectRow(_row);
                return;
            }
        }
    }
#endif
}

patientTable::~patientTable()
{
    modelFuture.waitForFinished();
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    reg.setValue("filterColumn",filterColumn);
    emit setFilter(filterColumn);
    delete model;
    delete proxy_model;
    sqlbase->optimize();
    delete sqlbase;
}

