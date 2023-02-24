// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "patienttable.h"
#include "qabstractitemmodel.h"
#include <algorithm>
#include <cstdlib>

patientTable::patientTable(QWidget *parent):QTableView(parent)
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    filterColumn =  reg.value("filterColumn").toInt();

    loadingIsFinished = false;
    connect(&watcher,&QFutureWatcher<QStandardItemModel*>::finished, this, &patientTable::updatePatientsCompleted,Qt::QueuedConnection);
    connect(&initWatcher,&QFutureWatcher<QStandardItemModel*>::finished, this,&patientTable::setMyModel,Qt::QueuedConnection);
    connect (this,&patientTable::loadSelectedPatient,this,&patientTable::activated,Qt::QueuedConnection);
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

QModelIndexList patientTable::getSortedMatchedListOfIndexes(const int &row)
{
    auto start = proxy_model->index(0,0);
    auto matchingString = QStringLiteral("%1").arg(row+1, 5, 10, QLatin1Char('0'));

    auto indexes = proxy_model->match(start,Qt::MatchExactly,matchingString);

    if (indexes.count() > 1)
        std::sort(indexes.begin(),indexes.end(),
              [](const QModelIndex &a, const QModelIndex &b)
                {
                    return a.row() > b.row();
                });

    return indexes;
}

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

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->horizontalHeader()->setStretchLastSection( true );
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Interactive);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);

    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows );

    proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setFilterKeyColumn(filterColumn);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSortCaseSensitivity(Qt::CaseInsensitive);

    setModel(proxy_model);
    mSelectRow(0);
    emit setFilter(filterColumn);
    emit modelLoadingFinished();
}

void patientTable::tweaksAfterModelLoadingIsFinished()
{
    hideColumn(2);
    loadingIsFinished = true;
    this->horizontalHeader()->setMinimumWidth(55);
    this->setColumnWidth(0,55);
    repaint();
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


#define ENABLESORTEDSELECT
void patientTable::mSelectRow(int row)
{
#ifdef ENABLESORTEDSELECT
    selectRow(row);
#else

    int _resultedRow = 0;

    if(row > 0){
        auto sortedMatchedListOfIndexes = this->getSortedMatchedListOfIndexes(row);

        if(!sortedMatchedListOfIndexes.isEmpty())
            _resultedRow = sortedMatchedListOfIndexes.constFirst().row();
    }

    selectRow(_resultedRow);
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

