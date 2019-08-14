#include "patientnamelineedit.h"

patientNameLineEdit::patientNameLineEdit(QWidget *parent):mLineEdit(parent)
{
    Worker = new wm_patientnamesCompleterLoader;
    connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));
    connect (parent->window(),SIGNAL(reloadCompleter()),this,SLOT(createCompleter()));
    connect (parent->window(),SIGNAL(loadCompleters()),this,SLOT(loadCompleter()));
}

patientNameLineEdit::~patientNameLineEdit()
{
    watcher.waitForFinished();
    delete Worker;
}

void patientNameLineEdit::loadCompleter()
{
    char delimterNone[] = "";
    delimeter = *delimterNone;
    tableName = "patientNames";
    createCompleter();
}

void patientNameLineEdit::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
        mcompleter->popup()->hide();
        break;
    default:
        break;
    }
    QLineEdit::keyPressEvent(e);
}

void patientNameLineEdit::createCompleter()
{
    future = QtConcurrent::run(Worker,&wm_patientnamesCompleterLoader::Work);
    watcher.setFuture(future);
}
