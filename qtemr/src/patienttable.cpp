// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "patienttable.h"


patientTable::patientTable(QWidget *parent):QTableView(parent)
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    filterColumn =  reg.value("filterColumn").toInt();
    loadingIsFinished = false;
    connect(&watcher, SIGNAL(finished()), this, SLOT(updatePatientsCompleted()));
    connect(&initWatcher, SIGNAL(finished()), this, SLOT(setMyModel()));
    connect (this,SIGNAL(loadSelectedPatient(QModelIndex)),this,SIGNAL(activated(QModelIndex)));
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

    modelFuture = QtConcurrent::run(sqlbase,&sqlBase::getPatientsTableModel);
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
        emit clearSelection();
    }
    return QObject::eventFilter(o,e);
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
    selectRow(ID-1);
    this->setColumnWidth(0,sizeHintForColumn(0));
    emit repaint();
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
    selectRow(0);
    emit setFilter(filterColumn);
    emit modelLoadingFinished();
}

void patientTable::tweaksAfterModelLoadingIsFinished()
{
    hideColumn(2);
    loadingIsFinished = true;
    this->horizontalHeader()->setMinimumWidth(55);
    this->setColumnWidth(0,55);
    emit repaint();
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
    connect(this,SIGNAL(modelLoadingFinished()),this,SLOT(tweaksAfterModelLoadingIsFinished()));
    initModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getPatientsTableModel);
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

patientTable::~patientTable()
{
    modelFuture.waitForFinished();
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    reg.setValue("filterColumn",filterColumn);
    setFilter(filterColumn);
    delete model;
    delete proxy_model;
    sqlbase->optimize();
    delete sqlbase;
}

