// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "visitslist.h"

visitsList::visitsList(QWidget *parent): QComboBox(parent)
{
    installEventFilter(this);
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
    worker = new wm_visitListLoader;
    connect(&watcher,SIGNAL(finished()),this,SLOT(insertVisits()));
    setIconSize(QSize(22,22));
    setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _view = (QListView *)this->view();
    _view->setLayoutMode(QListView::Batched);
    _view->setBatchSize(10);
    _view->setAlternatingRowColors(false);
    setEditable(false);
//    lineEdit()->setReadOnly(true);
//    lineEdit()->setAlignment(Qt::AlignCenter);
}


void visitsList::populateWithVisitList(const int &_ID)
{
    this->ID = _ID;
    worker->setID(_ID);
    future = QtConcurrent::run(worker,&wm_visitListLoader::Work);
    watcher.setFuture(future);
}


void visitsList::makeReadWrite(bool b)
{
    isReadOnly = !b;
}

void visitsList::stopLoading()
{
    _stopLoadingNow=true;
}

void visitsList::setMaxFollows(int mxf)
{
    maxFollows=mxf;
}

QDate visitsList::getParentVisitDate(int index)
{
    for(int x = index; x< list.length();x++)
    {
        if ( (list.at(x).visitType == 0) || (list.at(x).visitType == 5) ){
            return QDate::fromJulianDay(list.at(x).julianDay);
        }
    }
    return QDate::fromJulianDay(list.at(index).julianDay);
}

void visitsList::setVisitIcon(int type, QIcon icon)
{
    setItemIcon(currentIndex(),icon);
    if (list.length()!=0)
        list[currentIndex()].visitType = type;
}

void visitsList::addDetails()
{

    int i=0;
    foreach (sqlBase::visitItem item, list)
    {
        if(!_stopLoadingNow){
            setItemIcon(i,visitTypes.getVisitTypesByAlgoIndex(item.visitType).icon);
            setItemData(i,item.Diagnosis,Qt::ToolTipRole);
            setItemData(i,visitTypes.getVisitTypesByAlgoIndex(item.visitType).color,Qt::BackgroundRole);
            //setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
//            qApp->processEvents();
            i++;
        }
    }
    //_view->blockSignals(false);
    //_view->setUpdatesEnabled(true);

    emit loadCompleted();
}

visitsList::~visitsList()
{
    delete worker;
}

void visitsList::insertVisits()
{
    //_view->setUpdatesEnabled(false);
    //_view->blockSignals(true);
    clear();
    //QElapsedTimer t;
    list = watcher.result();
    QStringList vStrings;
    //t.start();
    for (sqlBase::visitItem &item: list)
    {
        vStrings.append(item.visitDateTime);
        //qApp->processEvents();
    }
    addItems(vStrings);
    //mDebug() <<t.elapsed();
    setCurrentIndex(0);
    _stopLoadingNow=false;
    QTimer::singleShot(250,this,&visitsList::addDetails);
}

bool visitsList::eventFilter(QObject *o, QEvent *e)
{
    if ( e->type() != QEvent::MouseButtonPress)
        return QComboBox::eventFilter(o,e);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (e);

    bool onlyVisit = count()==1;

    if ((mouseEvent->button() == Qt::LeftButton) && !onlyVisit && !isReadOnly && (o == this)  )
    {
        emit saveVisit();
        return false;
    }
    return QComboBox::eventFilter(o,e);
}



void visitsList::wheelEvent(QWheelEvent *e)
{
    e->ignore();
}
