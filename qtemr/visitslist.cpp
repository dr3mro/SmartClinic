#include "visitslist.h"

visitsList::visitsList(QWidget *parent): QComboBox(parent)
{
    this->installEventFilter(this);
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
    worker = new wm_visitListLoader;
    connect(&watcher,SIGNAL(finished()),this,SLOT(insertVisits()));
    setIconSize(QSize(22,22));
}


void visitsList::populateWithVisitList(int ID)
{
    this->ID = ID;
    worker->setID(ID);
    future = QtConcurrent::run(worker,&wm_visitListLoader::Work);
    watcher.setFuture(future);
}


void visitsList::makeReadWrite(bool b)
{
    isReadOnly = !b;
}

void visitsList::setMaxFollows(int mxf)
{
    maxFollows=mxf;
}

visitsList::~visitsList()
{
    delete worker;
}

void visitsList::insertVisits()
{
    clear();
    int i=0;
    QVector<sqlBase::visitItem> list = watcher.result();
    foreach (sqlBase::visitItem item, list)
    {
        addItem(getVisitIcon(item.visitType),item.visitDateTime);
        setItemData(i,item.Diagnosis,Qt::ToolTipRole);
        i++;
    }

    setCurrentIndex(0);
    emit loadCompleted();
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

QIcon visitsList::getVisitIcon(int visitType) const
{
    if( visitType == 0 )
         return QIcon(":/Graphics/newvisit");
    else if ( visitType <= maxFollows )
        return QIcon(":/Graphics/fvisit");
    else if ( visitType > maxFollows )
        return QIcon(":/Graphics/free");
    else
        return QIcon();
}


void visitsList::wheelEvent(QWheelEvent *e)
{
    e->ignore();
}

