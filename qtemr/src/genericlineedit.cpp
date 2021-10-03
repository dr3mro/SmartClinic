// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "genericlineedit.h"

genericLineEdit::genericLineEdit(QWidget *parent):mLineEdit(parent),
      worker(new wm_CompleterLoader)
{
    if (windowName!= "" )
    {
        connect (parent->window(),SIGNAL(loadCompleters()),this,SLOT(loadCompleter()));

        if ( windowName != "favouriteDrugsEditor" )
        {
            connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));
            connect (parent->window(),SIGNAL(reloadCompleter()),this,SLOT(mUpdateCompleter()));
        }

    }
    if (windowName == "visitsBox")
    {
        connect (parent->window(),SIGNAL(onVisitBoxClose()),this,SLOT(clear()),Qt::QueuedConnection);
        connect (this,SIGNAL(reportCompleterPopUpVisibility(bool)),parent->window(),SLOT(isCompleterPopupVisible(bool)));
        connect (this,SIGNAL(isAutoCompleteByWord()),parent->window(),SLOT(isCompleteByWord()));
    }
    if ( (windowName == "MainWindow") || (windowName == "visitsBox") )
    {
        connect(parent->window(),SIGNAL(updateTextFont()),this,SLOT(setDefaultFont()));
        connect (this,SIGNAL(removeItemFromCompleter(QString,QString)),parent->window(),SLOT(removeItemFromCompleter(QString,QString)));
        connect (parent->window(),SIGNAL(insertUniqueItem(QString,QString)),this,SLOT(addUniqueItem2Model(QString,QString)),Qt::QueuedConnection);
    }
}

genericLineEdit::~genericLineEdit()
{
    delete worker;
}

void genericLineEdit::mSetCompleter(QString table, char deli[])
{
    delimeter = *deli;
    tableName = table;
    createCompleter();
}

void genericLineEdit::setTableDeli(QString table, char deli[])
{
    delimeter = *deli;
    tableName = table;
}

void genericLineEdit::mUpdateCompleter()
{
    QStringList ignoredObjects = QStringList()  << "allergyLine"
                                                << "drugLine"
                                                << "opAdLine"
                                                << "investigationsLine"
                                                << "patientName";


    if ( !ignoredObjects.contains(objectName()))
        createCompleter();
}


void genericLineEdit::createCompleter()
{
    worker->setTable(tableName);
#if QT_VERSION >= 0x060000
    future = QtConcurrent::run(&wm_CompleterLoader::Work,worker);
#else
    future = QtConcurrent::run(worker,&wm_CompleterLoader::Work);
#endif
    watcher.setFuture(future);
}

void genericLineEdit::loadCompleter()
{
    char delimterNone[] = "";
    char delimterSpace[] = " ";
    bool autocompleteByWord = isAutoCompleteByWord();

    if (objectName() == "patientName")
    {
       return;
    }
    else if (objectName() == "allergyLine")
    {
            delimeter = *delimterNone;
            tableName = "allergies";
    }
    else if (objectName() == "patientResidence")
    {
            delimeter = *delimterNone;
            tableName = "places";
    }
    else if (objectName() == "patientPlaceBirth")
    {
            delimeter = *delimterNone;
            tableName = "placeOfBirth";
    }
    else if (objectName() == "patientOccupation")
    {
            delimeter = *delimterNone;
            tableName = "jobs";
    }
    else if (objectName() == "opAdLine")
    {
            delimeter = *delimterNone;
            tableName = "surgeries";
    }
    else if (objectName() == "le_setDose")
    {
        delimeter = *delimterNone;
        tableName = "doses";
    }
    else if (objectName() == "dose")
    {
        delimeter = *delimterNone;
        tableName = "doses";
    }
    else if (objectName() == "placeOfBirth")
    {
        delimeter = *delimterNone;
        tableName = "placeOfBirth";
    }
    else if (objectName() == "tradeName")
    {
        delimeter = *delimterNone;
        tableName = "drugs";
    }
    else if (objectName() == "drugLine")
    {
        return;
    }
    else if (objectName() == "investigationsLine")
    {
        delimeter = *delimterNone;
        tableName = "investigations";
    }
    else if (objectName() == "presentation")
    {
        delimeter = (autocompleteByWord)? *delimterSpace:*delimterNone;
        tableName = "complaints";
    }
    else if (objectName() == "Diagnosis")
    {
        delimeter = (autocompleteByWord)? *delimterSpace:*delimterNone;
        tableName = "diagnoses";
    }
    else if (objectName() == "shortcut")
    {
        delimeter = *delimterNone;
        tableName = "expander";
    }
    else if (objectName() == "operation")
    {
        delimeter = *delimterNone;
        tableName = "surgeries";
    }
    createCompleter();
}
