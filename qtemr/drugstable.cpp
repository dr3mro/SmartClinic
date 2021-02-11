// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "drugstable.h"

drugsTable::drugsTable(QWidget *parent):zTableView(parent)
{
    setSortColumn(sortCol);
    createDrugsModel();
    createDrugsTableConMenu();
    tweakDrugsTable();
    exConName = QString("qt_sql_extra_drugsTable_%1_%2_%3")
            .arg(this->objectName())
            .arg(qrand())
            .arg(qrand());
    coConName = QString("qt_sql_core_drugsTable_%1_%2_%3")
            .arg(this->objectName())
            .arg(qrand())
            .arg(qrand());

    sqlextra = new sqlExtra(this,exConName,false);
    sqlcore = new sqlCore(this,coConName);
    lo_setDose = new QGridLayout(this);
    le_setDose = new genericLineEdit(this);
    le_setDose->setObjectName("le_setDose");
    altDrugs = new showAltDrugs(nullptr);
    genericSearch = new genericOnlineSearch(parent);
    findModel = new QStandardItemModel(altDrugs);

    lo_setDose->addWidget(&selectedDrugLabel,0,0);
    lo_setDose->addWidget(le_setDose,1,0);
    w_setDose.setLayout(lo_setDose);
    w_setDose.setWindowFlags(Qt::Popup);
    le_setDose->setClearButtonEnabled(true);
    le_setDose->setTextMargins(3,0,3,0);
    le_setDose->setContentsMargins(0,0,0,0);
    le_setDose->setPlaceholderText("enter drug dose here.");
    lo_setDose->setContentsMargins(0,0,0,0);
    lo_setDose->setSpacing(0);
    w_setDose.setContentsMargins(0,0,0,0);
    QString ss_s = "QLabel"
                   "{"
                   "background-color: SteelBlue;"
                   "color: White;"
                   "padding: 1 px;"
                   "}"
                   ""
                   "QLineEdit"
                   "{"
                   "background-color: white;"
                   "border:3px solid black;"
                   "}";
    w_setDose.setStyleSheet(ss_s);

    QAction *okDose = le_setDose->addAction(QIcon(":/ionicons/check"),
                                            QLineEdit::ActionPosition::TrailingPosition);

    okDose->setToolTip("Set this as dose.");

    setToolTip("<ul>"
               "<li>Shift + up or down arrows moves selected drug up or down.</li>"
               "<li>Right mouse button click shows context menu.</li>"
               "<li>Middle mouse button double click or (Shift + Left) or Space bar key to toggle item.</li>"
               "<li>Left mouse button click or Enter key to set selected drug dose.</li>"
               "</ul>");

    connect (le_setDose,SIGNAL(returnPressed()),this,SLOT(setDose()),Qt::QueuedConnection);
    connect (okDose,SIGNAL(triggered(bool)),le_setDose,SIGNAL(returnPressed()),Qt::QueuedConnection);

    connect (&selectedDrugLabel,SIGNAL(leftMouseButtonClicked()),&w_setDose,SLOT(close()));
    connect (&selectedDrugLabel,SIGNAL(rightMouseButtonClicked()),&w_setDose,SLOT(close()),Qt::QueuedConnection);
    connect (&selectedDrugLabel,SIGNAL(rightMouseButtonClicked()),this,SLOT(showContextMenu()),Qt::QueuedConnection);

    worker = new wm_drugModelLoader;
    worker->setDrugsModel(drugsModel);
    connect (&watcher,SIGNAL(finished()),this,SLOT(drugsModelLoaded()));

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(drugTableItemChanged()),this,SLOT(drugsTableSort()));
    connect(this,SIGNAL(drugTableItemChanged()),this,SLOT(calculateRxCosts()));
    connect(this ,SIGNAL(customContextMenuRequested(const QPoint)),this,SLOT(showContextMenu(const QPoint)));
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
    connect(le_setDose,SIGNAL(removeItemFromCompleter(QString,QString)),this,SLOT(removeItemFromCompleter(QString,QString)));
    connect(this,SIGNAL(setFindDrugsModel(QStandardItemModel*)),altDrugs,SLOT(setModel(QStandardItemModel*)));
    connect(this,SIGNAL(setFindDrugsLabel(QString)),altDrugs,SLOT(setLabel(QString)));
    connect(altDrugs,SIGNAL(replaceDrug(QString)),this,SLOT(replaceDrug(QString)));

    coreDrugs = sqlcore->getCoreDrugList();
    viewport()->installEventFilter(this);
}

bool drugsTable::addDrug2DrugList(QString newDrug)
{
    if ( newDrug.simplified().isEmpty())
        return false;

    bool isDruginAutoComplete = isTradeNameinAutocomplete(newDrug);

    if ( !isDruginAutoComplete && !(newDrug.right(1)== QString("*")) )
    {

        if ( insertUnknownDrugName != newDrug )
            insertUnknownDrugCounter=0;

        if ( insertUnknownDrugCounter == 0)
        {
            popUpMessage("Warning","The item you are trying to add is unknown! press ENTER again to confirm. ");
            insertUnknownDrugCounter+=1;
            insertUnknownDrugName=newDrug;
            return false;
        }
        else if( insertUnknownDrugCounter>0)
        {
            insertUnknownDrugCounter=0;
            popUpMessage("Warning","The Unknown drug has been added.");
        }

    }

    int druglength = drugsModel->rowCount();

    for ( int i = 0 ; i < druglength ; i++)
    {
        QString drug =  drugsModel->item(i,0)->text(); //  ui->drugList->item(i)->text();

        if ( drug.toUpper().append("*") == newDrug.toUpper() )
        {
            drugsModel->item(i,5)->setText("0");
            emit drugTableItemChanged();
            return true;
        }
        else if ( ( drug.toUpper() == newDrug.toUpper() ) && (drugsModel->item(i,5)->text() == "0") )
        {
            drugsModel->item(i,5)->setText("1");
            emit drugTableItemChanged();
            return true;
        }
        else if ( drug.toUpper() == newDrug.toUpper() && (drugsModel->item(i,5)->text() == "1") )
        {
            popUpMessage("Warning","The item you are trying to add to this Drug List already exists!");
            return true;
        }
    }

    QString state;
    if ( newDrug.endsWith("*"))
    {
        state = QString::number(0);
        newDrug = newDrug.remove("*");
    }
    else
    {
        state = QString::number(1);
    }
    QStandardItem *tn_item = new QStandardItem;
    QStandardItem *gn_item = new QStandardItem;
    QStandardItem *ds_item = new QStandardItem;
    QStandardItem *rd_item = new QStandardItem;
    QStandardItem *sd_item = new QStandardItem;
    QStandardItem *st_item = new QStandardItem;
    QStandardItem *fm_item = new QStandardItem;
    QStandardItem *ps_item = new QStandardItem;

    QList<QStandardItem * > newRow;

    newRow.clear();
    newRow.append(tn_item);
    newRow.append(gn_item);
    newRow.append(ds_item);
    newRow.append(rd_item);
    newRow.append(sd_item);
    newRow.append(st_item);
    newRow.append(fm_item);
    newRow.append(ps_item);

    tn_item->setText(newDrug);
    gn_item->setText(sqlcore->getDrugDetail(newDrug,"GENERICNAME"));
    ds_item->setText(sqlextra->getDefaultDrugDose(newDrug));
    fm_item->setText(sqlcore->getDrugDetail(newDrug,"FORM"));
    rd_item->setText(QString::number(QDate::currentDate().toJulianDay()));
    st_item->setText(state);
    ps_item->setText(sqlcore->getDrugDetail(newDrug,"PRICE"));

    drugsModel->insertRow(drugsModel->getPrintableDrugsCount(),newRow);
    tweakDrugsTable();
    sqlextra->addToAutoComplete("drugs",newDrug);

    genDrugTableToolTip();
    emit drugTableItemChanged();
    emit drugsHasBeenAltered(true);
    return true;
}

void drugsTable::addDrug2DrugListByStringList(QStringList stringList)
{
    QStandardItem *tn_item = new QStandardItem;
    QStandardItem *gn_item = new QStandardItem;
    QStandardItem *ds_item = new QStandardItem;
    QStandardItem *rd_item = new QStandardItem;
    QStandardItem *sd_item = new QStandardItem;
    QStandardItem *st_item = new QStandardItem;
    QStandardItem *fm_item = new QStandardItem;
    QStandardItem *ps_item = new QStandardItem;

    QList<QStandardItem * > newRow;
    newRow.clear();
    newRow.append(tn_item);
    newRow.append(gn_item);
    newRow.append(ds_item);
    newRow.append(rd_item);
    newRow.append(sd_item);
    newRow.append(st_item);
    newRow.append(fm_item);
    newRow.append(ps_item);


    tn_item->setText(stringList.at(0));
    gn_item->setText(stringList.at(1));
    ds_item->setText(stringList.at(2));
    rd_item->setText(stringList.at(3));
    sd_item->setText(stringList.at(4));
    st_item->setText(stringList.at(5));
    fm_item->setText(stringList.at(6));
    ps_item->setText(stringList.at(7));

    drugsModel->appendRow(newRow);
    tweakDrugsTable();
    drugTableItemChanged();
    emit drugsHasBeenAltered(true);
}

void drugsTable::removeCurrentSelectedDrugFromList()
{
    int currentRow = currentIndex().row();
    drugsModel->removeRow(currentRow);
    emit drugsHasBeenAltered(true);
}

void drugsTable::DrugSyncWithVisit(QList<QStringList> array, bool sync)
{
    if ( ! sync )
        drugsModel->clear();
    int vDrugs_rows =  array.size();
    int mDrugs_rows =  drugsModel->rowCount();
    QString tradeName_m,tradeName_v;
    QStringList vDrugList;
    int a_size = array.size();
    int drugindex = -1;
    bool drugIsThere =false;
    if ( mDrugs_rows == 0 )
    {
        for( int a =0 ; a < a_size ; a++)
        {
            addDrug2DrugListByStringList(array.at(a));
            emit drugTableItemChanged();
            tweakDrugsTable();
        }
        emit saveDrugs();
        return;
    }
    for ( int v = 0 ; v < vDrugs_rows ; v++)
    {
        vDrugList = array.at(v);
        tradeName_v = vDrugList.at(0).split(" ").at(0);

        for ( int m = mDrugs_rows -1 ; m >= 0 ; --m)
        {
            tradeName_m = drugsModel->item(m,0)->text().simplified().split(" ").at(0);
            if ( (tradeName_m == tradeName_v ) )
            {
                drugIsThere = true;
                drugindex = m;
                break;
            }
            else
            {
                drugIsThere = false;
            }

        }

        if ( drugIsThere )
        {
            for ( int x = 0 ; x < 8 ; x++ )
            {
                drugsModel->item(drugindex,x)->setText(vDrugList.at(x));
            }
        }
        else
        {
            addDrug2DrugListByStringList(vDrugList);
            emit drugTableItemChanged();
            tweakDrugsTable();
        }
    }
    emit drugTableItemChanged();
    emit saveDrugs();
}

void drugsTable::clearDrugs()
{
    int reply = showMessageBox("Are you sure that you want to remove all drugs from list?");
    if(reply == QMessageBox::Yes)
        clear();
}

void drugsTable::clear()
{
    drugsModel->removeRows(0,drugsModel->rowCount());
    drugsModel->clear();
    reset();
    setModel(drugsModel);
    emit drugTableItemChanged();
    emit drugsHasBeenAltered(true);
}

void drugsTable::clearInactiveDrugs()
{
    int reply = showMessageBox("Are you sure that you want to remove stopped drugs from list?");
    if(reply == QMessageBox::No)
        return;

    int rows = drugsModel->rowCount();
    int state;
    for (int row=0;row<rows;row++)
    {
        state = drugsModel->item(row,5)->text().toInt();
        if ( state == 0 )
        {
            drugsModel->removeRow(row);
            rows--;
            row--;
        }
    }
    setModel(drugsModel);
    emit drugTableItemChanged();
    emit drugsHasBeenAltered(true);

}

void drugsTable::replaceDrug(QString newDrug)
{
    QModelIndex cell = selectionModel()->currentIndex();
    QString drug = cell.sibling(cell.row(),0).data(Qt::DisplayRole).toString();
    int druglength = drugsModel->rowCount();

    for ( int i = 0 ; i < druglength ; i++)
    {
        if ( drug.toUpper() == newDrug.toUpper() && (drugsModel->item(i,5)->text() == "1") )
        {
            popUpMessage("Warning","The item you are trying to add to this Drug List already exists!");
            return;
        }
    }

    QString state = QString::number(1);

    QStandardItem *tn_item = new QStandardItem;
    QStandardItem *gn_item = new QStandardItem;
    QStandardItem *ds_item = new QStandardItem;
    QStandardItem *rd_item = new QStandardItem;
    QStandardItem *sd_item = new QStandardItem;
    QStandardItem *st_item = new QStandardItem;
    QStandardItem *fm_item = new QStandardItem;
    QStandardItem *ps_item = new QStandardItem;

    QList<QStandardItem * > newRow;

    newRow.clear();
    newRow.append(tn_item);
    newRow.append(gn_item);
    newRow.append(ds_item);
    newRow.append(rd_item);
    newRow.append(sd_item);
    newRow.append(st_item);
    newRow.append(fm_item);
    newRow.append(ps_item);

    tn_item->setText(newDrug);
    gn_item->setText(sqlcore->getDrugDetail(newDrug,"GENERICNAME"));
    ds_item->setText(sqlextra->getDefaultDrugDose(newDrug));
    fm_item->setText(sqlcore->getDrugDetail(newDrug,"FORM"));
    rd_item->setText(QString::number(QDate::currentDate().toJulianDay()));
    st_item->setText(state);
    ps_item->setText(sqlcore->getDrugDetail(newDrug,"PRICE"));
    int row = selectionModel()->currentIndex().row();
    drugsModel->removeRow(row);
    drugsModel->insertRow(row,newRow);
    selectRow(row);
    tweakDrugsTable();
    genDrugTableToolTip();
    emit drugTableItemChanged();
    emit drugsHasBeenAltered(true);

}

DrugsItemModel *drugsTable::getDrugsModel()
{
    return drugsModel;
}

bool drugsTable::isWorking()
{
    return working;
}

void drugsTable::loadPatientDrugsModel(int ID, int julianDate,bool syncLoader)
{
    working = true;
    drugsModel->blockSignals(true);
    drugsSyncLoadingOperation = syncLoader;
    worker->setIDJulianDate(ID,julianDate);
    future = QtConcurrent::run(worker,&wm_drugModelLoader::Work);
    watcher.setFuture(future);
}
drugsTable::~drugsTable()
{
    delete drugsModel;
    delete findModel;
    delete worker;
    sqlextra->optimize();
    delete sqlextra;
    sqlcore->optimize();
    delete sqlcore;
    delete altDrugs;
    delete genericSearch;
    QSqlDatabase::removeDatabase(exConName);
    QSqlDatabase::removeDatabase(coConName);
    delete lo_setDose;
    delete le_setDose;
    delete a_stop;
    delete a_resume;
    delete a_setDose;
    delete a_clearDefaultDose;
    delete a_checkPrice;
    delete a_genericInfo;
    delete a_rAutoComp;
    delete a_aAutoComp;
    delete a_clear;
    delete a_delete;
    delete a_clearInactive;
    delete a_copy2pWin;
    delete a_stopAll;
    delete a_resumeAll;
    delete a_ShowAltDrugsSameTrade;
    delete a_ShowAltDrugsSameGeneric;
    delete a_ShowAltDrugsSameIndication;
    delete a_ShowAltDrugsSameGroup;
    delete cpDrugsMenu;
    delete a_updateAll2PWin;
    delete a_cp4rmPWin;
    delete a_overWrite2pWin;
    delete a_cp4rmLastVisit;
    delete altDrugsMenu;
    delete m_drugs;
}

void drugsTable::createDrugsModel()
{
    drugsModel = new DrugsItemModel(this);
    drugsModel->setSortRole(Qt::AscendingOrder);
    setModel(drugsModel);
}

void drugsTable::createDrugsTableConMenu()
{
    m_drugs = new QMenu(this);
    altDrugsMenu  = new QMenu(m_drugs);
    altDrugsMenu->setTitle("&Find alternative drug");
    altDrugsMenu->setIcon(QIcon(":/Graphics/search"));

    a_resume = new QAction("&Start",m_drugs);
    a_resume->setIcon(QIcon(":/ionicons/play"));

    a_stop = new QAction("&Stop",m_drugs);
    a_stop->setIcon(QIcon(":/ionicons/pause"));

    a_setDose = new QAction("&Set dose",m_drugs);
    a_setDose->setIcon(QIcon(":/ionicons/setDose"));

    a_clearDefaultDose = new QAction("&Clear standard dose",m_drugs);
    a_clearDefaultDose->setIcon(QIcon(":/ionicons/reDose"));

    a_checkPrice = new QAction("&Update drug's price",m_drugs);
    a_checkPrice->setIcon(QIcon(":/ionicons/price"));

    a_genericInfo = new QAction("&Search drug online",m_drugs);
    a_genericInfo->setIcon(QIcon(":/ionicons/earth"));

    a_rAutoComp = new QAction("&Remove from autocompleter",m_drugs);
    a_rAutoComp->setIcon(QIcon(":/ionicons/rm"));

    a_aAutoComp = new QAction("&Add to autocompleter",m_drugs);
    a_aAutoComp->setIcon(QIcon(":/ionicons/add"));


    a_delete = new QAction("&Delete selected drug",m_drugs);
    a_delete->setIcon(QIcon(":/Graphics/ex"));

    a_clear = new QAction("&Delete all drugs",m_drugs);
    a_clear->setIcon(QIcon(":/Graphics/delete"));

    a_clearInactive = new QAction("&Delete inactive drugs",m_drugs);
    a_clearInactive->setIcon(QIcon(":/ionicons/clr"));

    a_stopAll = new QAction("&Stop all Drugs",m_drugs);
    a_stopAll->setIcon(QIcon(":/ionicons/stopAll"));
    a_stopAll->setObjectName("stopAll");

    a_resumeAll = new QAction("&Resume all Drugs",m_drugs);
    a_resumeAll->setIcon(QIcon(":/ionicons/resumeAll"));
    a_resumeAll->setObjectName("resumeAll");

    //


    cpDrugsMenu  = new QMenu(m_drugs);
    cpDrugsMenu->setTitle("&Sync drugs tool");
    cpDrugsMenu->setIcon(QIcon(":/Graphics/beaker"));

    a_copy2pWin = new QAction("&Copy selected item into Patient's Drugs",m_drugs);
    a_copy2pWin->setIcon(QIcon(":/Graphics/copy"));

    a_updateAll2PWin = new QAction("&Update Patient's Drugs from this list.",m_drugs);
    a_updateAll2PWin->setIcon(QIcon(":/Graphics/copy"));
    a_updateAll2PWin->setObjectName("update_drugs");

    a_cp4rmPWin = new QAction("&Fill this list with pateint's drugs.",m_drugs);
    a_cp4rmPWin->setIcon(QIcon(":/Graphics/copy"));

    a_cp4rmLastVisit = new QAction("&Fill this list with last visit's drugs.",m_drugs);
    a_cp4rmLastVisit->setIcon(QIcon(":/Graphics/copy"));

    a_overWrite2pWin = new QAction("&Overwrite all in Patient's Drugs with this list.",m_drugs);
    a_overWrite2pWin->setIcon(QIcon(":/Graphics/copy"));
    a_overWrite2pWin->setObjectName("overwrite_drugs");

    //
    a_ShowAltDrugsSameTrade = new QAction("&With same trade name",altDrugsMenu);
    a_ShowAltDrugsSameTrade->setIcon(QIcon(":/Graphics/beaker"));

    a_ShowAltDrugsSameGeneric = new QAction("&With same generic name",altDrugsMenu);
    a_ShowAltDrugsSameGeneric->setIcon(QIcon(":/Graphics/beaker"));

    a_ShowAltDrugsSameIndication = new QAction("&With same indication",altDrugsMenu);
    a_ShowAltDrugsSameIndication->setIcon(QIcon(":/Graphics/beaker"));

    a_ShowAltDrugsSameGroup = new QAction("&With same Drug Group",altDrugsMenu);
    a_ShowAltDrugsSameGroup->setIcon(QIcon(":/Graphics/beaker"));



    QList<QAction*> actionList1;
    QList<QAction*> actionList2;
    QList<QAction*> actionList3;
    QList<QAction*> actionList4;

    actionList1 << a_resume << a_stop << a_setDose << a_clearDefaultDose << a_checkPrice << a_genericInfo;
    actionList2 <<  a_aAutoComp << a_rAutoComp << a_delete << a_stopAll << a_resumeAll << a_clear << a_clearInactive;
    actionList3 << a_ShowAltDrugsSameTrade << a_ShowAltDrugsSameGeneric << a_ShowAltDrugsSameIndication << a_ShowAltDrugsSameGroup;
    actionList4 << a_copy2pWin << a_updateAll2PWin << a_cp4rmPWin << a_cp4rmLastVisit << a_overWrite2pWin ;
    altDrugsMenu->addActions(actionList3);
    cpDrugsMenu->addActions(actionList4);

    m_drugs->addActions(actionList1);
    m_drugs->addMenu(altDrugsMenu);
    m_drugs->addActions(actionList2);
    m_drugs->addMenu(cpDrugsMenu);

    actionList1.clear();
    actionList2.clear();
    actionList3.clear();

    connect (a_setDose,SIGNAL(triggered()),this,SLOT(show_setDose()));
    connect (a_resume,SIGNAL(triggered()),this,SLOT(resume_drug()));
    connect (a_stop,SIGNAL(triggered()),this,SLOT(stop_drug()));
    connect (a_clearDefaultDose,SIGNAL(triggered()),this,SLOT(clearDefaultDose()));
    connect (a_checkPrice,SIGNAL(triggered()),this,SLOT(checkPrice()));
    connect (a_genericInfo,SIGNAL(triggered()),this,SLOT(searchGenricNameOnline()));
    connect (a_aAutoComp,SIGNAL(triggered()),this,SLOT(addToAutoComplete()));
    connect (a_rAutoComp,SIGNAL(triggered()),this,SLOT(removeFromAutoComplete()));
    connect (a_delete,SIGNAL(triggered()),this,SLOT(removeCurrentSelectedDrugFromList()));
    connect (a_clear,SIGNAL(triggered()),this,SLOT(clearDrugs()));
    connect (a_clearInactive,SIGNAL(triggered()),this,SLOT(clearInactiveDrugs()));
    connect (a_copy2pWin,SIGNAL(triggered()),this,SLOT(copy2pDrugsList()));

    connect (a_updateAll2PWin,SIGNAL(triggered()),this,SLOT(Sync2Patient()));
    connect (a_cp4rmPWin,SIGNAL(triggered()),this,SIGNAL(SyncToVisit()));
    connect (a_cp4rmLastVisit,SIGNAL(triggered()),this,SIGNAL(SyncLastVisit()));
    connect (a_overWrite2pWin,SIGNAL(triggered()),this,SLOT(Sync2Patient()));

    connect (a_stopAll,SIGNAL(triggered()),this,SLOT(toggleAllDrugs()));
    connect (a_resumeAll,SIGNAL(triggered()),this,SLOT(toggleAllDrugs()));

    connect (a_ShowAltDrugsSameTrade,SIGNAL(triggered()),this,SLOT(findSameTradename()));
    connect (a_ShowAltDrugsSameGeneric,SIGNAL(triggered()),this,SLOT(findSameGeneric()));
    connect (a_ShowAltDrugsSameIndication,SIGNAL(triggered()),this,SLOT(findSameIndication()));
    connect (a_ShowAltDrugsSameGroup,SIGNAL(triggered()),this,SLOT(findSameGroup()));

}

void drugsTable::tweakDrugsTable()
{
    this->horizontalHeader()->setHidden(true);
    this->verticalHeader()->setHidden(true);
    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);
    this->hideColumn(4);
    this->hideColumn(5);
    this->hideColumn(6);
    this->hideColumn(7);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows );
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->horizontalHeader()->setStretchLastSection(true);
}

void drugsTable::genDrugTableToolTip()
{
    if ( drugsModel->rowCount() == 0)
    {
        return;
    }
    QString genericLabel;
    QString tradeName;
    QString genericName;
    QString dose;
    int current;
    QString startDate;
    QString stopDate;
    QString tTip;
    QString price;
    QString category;
    QString expander;
    QString date;
    QString dateLabel;
    QString currentTag;
    bool isExpander = false;
    for ( int t = 0 ; t < drugsModel->rowCount() ; t++ )
    {
        genericLabel = "Generic Name";
        tradeName = drugsModel->item(t,0)->text();
        genericName = drugsModel->item(t,1)->text();
        dose = "<x dir=RTL >" + drugsModel->item(t,2)->text() + "</x>";
        startDate = drugsModel->item(t,3)->text();
        stopDate = drugsModel->item(t,4)->text();
        current = drugsModel->item(t,5)->text().toInt();
        price = drugsModel->item(t,7)->text();
        category = sqlcore->getDrugDetail(tradeName,"CATEGORY");
        expander = sqlextra->getExpand(tradeName);

        QLocale locale(QLocale::English , QLocale::UnitedStates );
        date = (current)? locale.toString(QDate::fromJulianDay(startDate.toInt()),"dd/MM/yyyy"):locale.toString(QDate::fromJulianDay(stopDate.toInt()),"dd/MM/yyyy");
        dateLabel = (current)? "Start Date   ":"Stop Date   ";
        currentTag = (current)? "Yes":"No";

        if ( category.isEmpty())
            category = "UNKNOWN";

        if (price.isEmpty())
            price = "UNKNOWN";

        if (genericName.isEmpty())
            genericName = "UNKNOWN";

        if (expander.isEmpty())
        {
            isExpander= false;
        }
        else
        {
            genericName = expander;
            genericLabel = "Exapnded to";
            isExpander=true;
        }

        QString tooltip_template;
        if ( !isExpander )
        {
            tooltip_template =
                    QString(   "<table>"
                               "<tr>"
                               "<td><b> %6 </td><td>:</td> </b><td> %1 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Dose         </td><td>:</td> </b><td dir=RTL align=\"left\"> %2 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Current      </td><td>:</td> </b><td> %8 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> %7   </td><td>:</td> </b><td> %3 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Price        </td><td>:</td> </b><td> %4 Le.</td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Category     </td><td>:</td> </b><td><p align=\"left\"> %5.</p></td>"
                               "</tr>"
                               "</table>");
            tTip = QString (tooltip_template)
                    .arg(genericName)
                    .arg(dose)
                    .arg(date)
                    .arg(price)
                    .arg(category)
                    .arg(genericLabel)
                    .arg(dateLabel)
                    .arg(currentTag);


        }
        else
        {
            tooltip_template =
                    QString(   "<table>"
                               "<tr>"
                               "<td><b> %4 </td><td>:</td> </b><td> %1 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Dose         </td><td>:</td> </b><td dir=RTL> %2 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> Current      </td><td>:</td> </b><td> %6 </td>"
                               "</tr>"
                               "<tr>"
                               "<td><b> %5   </td><td>:</td> </b><td> %3 </td>"
                               "</tr>"
                               "</table>");
            tTip = QString (tooltip_template)
                    .arg(genericName)
                    .arg(dose)
                    .arg(date)
                    .arg(genericLabel)
                    .arg(dateLabel)
                    .arg(currentTag);
        }


        drugsModel->item(t,0)->setToolTip(tTip);
    }
}

bool drugsTable::isThereInactiveDrugs()
{
    return drugsModel->isThereInactiveDrugs();
}

bool drugsTable::isThereActiveDrugs()
{
    return drugsModel->isThereActiveDrugs();
}

bool drugsTable::isTradeNameinAutocomplete(QString tradeName)
{
    QStringList autoComplete = sqlextra->getAutoCompleteList("drugs");
    if (autoComplete.contains(tradeName,Qt::CaseInsensitive))
        return true;
    else
        return false;
}

bool drugsTable::isPriceEqual(int row,QString tradeName)
{
    double indexPrice = sqlcore->getDrugDetail(tradeName,"PRICE").toDouble();
    double savedPrice = drugsModel->item(row,7)->text().toDouble();
    return ( dataHelper::doubleEqual(indexPrice,savedPrice));
}

int drugsTable::showMessageBox(QString message)
{
    myMessageBox msgbox;
    return msgbox.question(this,"Alert!",message,QMessageBox::Yes,QMessageBox::No);
}

bool drugsTable::eventFilter(QObject *o, QEvent *e)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (e);
    QKeyEvent *keyEvent = static_cast<QKeyEvent *> (e);

    bool isShift = keyEvent->modifiers().testFlag(Qt::KeyboardModifier::ShiftModifier);

    QModelIndex cell =  indexAt(viewport()->mapFromGlobal(QCursor::pos()));

    if ( !cell.isValid() || isReadOnly )
        return zTableView::eventFilter(o,e);

    int drugStatus = drugsModel->item(cell.row(),5)->text().toInt();

    if ( o == this->viewport() && e->type() == QEvent::MouseButtonDblClick)
    {
        if ( mouseEvent->button() == Qt::LeftButton && !isShift)
        {
            selectRow(cell.row());
            show_setDose();
        }
        else if ( ( mouseEvent->button() == Qt::LeftButton && isShift) ||
                  (mouseEvent->button() == Qt::MiddleButton) )
        {
            switch (drugStatus){
            case 1:
                stop_drug();
                break;
            case 0:
                resume_drug();
                break;
            }
        }
    }

    return zTableView::eventFilter(o,e);

}

void drugsTable::keyPressEvent(QKeyEvent *keyEvent)
{
    if ( !isReadOnly && keyEvent->key() ==  Qt::Key_Return  )
        show_setDose();
    else if (!isReadOnly && keyEvent->key() ==  Qt::Key_Space)
    {
        QModelIndex cell =  selectionModel()->currentIndex();
        if ( cell.isValid() && drugsModel->item(cell.row(),5)->text().toInt() == 1 )
        {
            stop_drug();
        }
        else if ( cell.isValid() && drugsModel->item(cell.row(),5)->text().toInt() == 0 )
        {
            resume_drug();
        }
    }

    zTableView::keyPressEvent(keyEvent);
}
void drugsTable::showContextMenu(const QPoint &pos)
{
    QModelIndex cell = selectionModel()->currentIndex();
    bool no_drugs = (drugsModel->rowCount() == 0);
    bool null_selected;
    QString tradeName="";
    QString genericName="";
    bool canFetchDrugInfo=false;

    bool doesHavePatientDrugs = doeshaveDrugsInPatient();
    bool doesLastVisitHasDrugs = doesHaveDrugsInLastVisit();

    if ( !cell.isValid() )
    {
        null_selected = true;
        canFetchDrugInfo = false;
    }
    else
    {
        tradeName = drugsModel->item(cell.row(),0)->text();
        genericName = drugsModel->item(cell.row(),1)->text();
        canFetchDrugInfo = !( genericName.isEmpty() || genericName == "Unknown");
        null_selected = false;
    }

    QString overwrite_label = "&Overwrite all in Patient's Drugs with this list.";
    QString copy_label = "&Copy all item into Patient's Drugs.";
    QString a_overWrite2pWin_action_label;

    if ( doesHavePatientDrugs )
         a_overWrite2pWin_action_label = overwrite_label;
    else
         a_overWrite2pWin_action_label = copy_label;

    a_overWrite2pWin->setText(a_overWrite2pWin_action_label);

    a_genericInfo->setVisible(canFetchDrugInfo && !null_selected);
    a_ShowAltDrugsSameGeneric->setVisible(canFetchDrugInfo && !null_selected);
    a_ShowAltDrugsSameTrade->setVisible(canFetchDrugInfo && !null_selected);

    a_clearInactive->setVisible(isThereInactiveDrugs()&&!isReadOnly&&!no_drugs);
    a_aAutoComp->setVisible(!isTradeNameinAutocomplete(tradeName)&&!isReadOnly&&!null_selected);
    a_rAutoComp->setVisible(isTradeNameinAutocomplete(tradeName)&&!isReadOnly&&!null_selected);
    a_setDose->setVisible(!isReadOnly&&!null_selected);
    a_clearDefaultDose->setVisible(!isReadOnly&&sqlextra->isDefaultDoseExists(tradeName)&&!null_selected);
    a_clear->setVisible(!isReadOnly&&!no_drugs);
    a_delete->setVisible(!isReadOnly&&!null_selected);

    a_stopAll->setVisible( isThereActiveDrugs() && !isReadOnly && !no_drugs);
    a_resumeAll->setVisible( isThereInactiveDrugs() && !isReadOnly && !no_drugs);

    a_copy2pWin->setVisible((objectName()=="vDrugsTable") && !null_selected);
    a_updateAll2PWin->setVisible((objectName()=="vDrugsTable") && !no_drugs && doesHavePatientDrugs);
    a_cp4rmPWin->setVisible((objectName()=="vDrugsTable") && no_drugs && doesHavePatientDrugs && !isReadOnly);
    a_cp4rmLastVisit->setVisible((objectName()=="vDrugsTable") && no_drugs && doesLastVisitHasDrugs && !isReadOnly);
    a_overWrite2pWin->setVisible((objectName()=="vDrugsTable") &&!no_drugs);

    cpDrugsMenu->menuAction()->setVisible(!cpDrugsMenu->isEmpty());

    if ( !null_selected && coreDrugs.contains(tradeName))
    {
        a_checkPrice->setVisible(!isReadOnly &&!isPriceEqual(cell.row(),tradeName));
        altDrugsMenu->menuAction()->setVisible(!isReadOnly);
    }
    else
    {
        a_checkPrice->setVisible(false);
        altDrugsMenu->menuAction()->setVisible(false);
    }


    if ( null_selected || no_drugs)
    {
        a_resume->setVisible(false);
        a_stop->setVisible(false);
    }
    else if (drugsModel->item(cell.row(),5)->text().toInt() == 1 )
    {
        a_resume->setVisible(false);
        a_stop->setVisible(!isReadOnly);
    }
    else if (drugsModel->item(cell.row(),5)->text().toInt() == 0 )
    {
        a_resume->setVisible(!isReadOnly);
        a_stop->setVisible(false);
    }

    m_drugs->popup(this->viewport()->mapToGlobal(pos));
}

void drugsTable::showContextMenu()
{
    showContextMenu(this->mapFromGlobal(QCursor::pos()));
}

void drugsTable::clearDefaultDose()
{
    QModelIndex cell =  this->selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    sqlextra->deleteDefaultDrugDose(tradeName);
}

void drugsTable::checkPrice()
{
    QModelIndex cell =  this->selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    double price = sqlcore->getDrugDetail(tradeName,"PRICE").toDouble();
    drugsModel->item(cell.row(),7)->setText(QString::number(price));
    genDrugTableToolTip();
}

void drugsTable::drugsModelLoaded()
{
    drugsModel = future.result();
    setModel(drugsModel);
    drugsModel->blockSignals(false);
    emit drugTableItemChanged();
    emit loadCompleted();
    emit drugsHasBeenAltered(drugsSyncLoadingOperation);
    working = false;
}

void drugsTable::removeFromAutoComplete()
{
    QString tradeName = getSelectedDrugTradeName();
    int reply = showMessageBox(QString("This will remove <%1> from your autocomplete list, Are you sure?").arg(tradeName));

    if(reply == QMessageBox::No)
        return;

    if (sqlextra->removeFromAutoComplete("drugs",tradeName))
    {
        popUpMessage("Message",QString("<%1> item was removed from drugs auto complete list.").arg(tradeName));
        sqlextra->deleteDefaultDrugDose(tradeName);
        emit reloadDrugsLineAutoComplete();
    }
}

void drugsTable::addToAutoComplete()
{
    QString tradeName = getSelectedDrugTradeName();
    if (sqlextra->addToAutoComplete("drugs",tradeName,true))
    {
        popUpMessage("Message",QString("<%1> item was added to drugs auto complete list.").arg(tradeName));
        emit reloadDrugsLineAutoComplete();
    }
}

void drugsTable::setDose()
{
    QString newDose = le_setDose->text().simplified();
    QModelIndex cell =  this->selectionModel()->currentIndex();
    drugsModel->item(cell.row(),2)->setText(newDose);
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    genDrugTableToolTip();

    if ( !sqlextra->isDefaultDoseExists(tradeName))
        sqlextra->addDefaultDrugDose(tradeName,newDose);

    QStringList Doses = le_setDose->autoCompleteStringList;
    if ( !Doses.contains(newDose,Qt::CaseInsensitive) )
        sqlextra->addToAutoComplete("doses",newDose);

    le_setDose->clear();
    w_setDose.hide();
    emit drugsHasBeenAltered(true);
}


void drugsTable::show_setDose()
{
    QModelIndex cell =  this->selectionModel()->currentIndex();
    if(!cell.isValid())
        return;

    bool active = cell.sibling(cell.row(),5).data(Qt::DisplayRole).toBool();

    QPoint pos = this->mapToGlobal(QPoint(this->columnViewportPosition(this->currentIndex().column())+2,
                                          this->rowViewportPosition(this->currentIndex().row())+2));
    le_setDose->mSetCompleter("doses");
    QString savedDose = drugsModel->item(cell.row(),2)->text();
    QString drugsName = drugsModel->item(cell.row(),0)->text();

    QFont font;
    font.setBold(active);
    font.setItalic(!active);


    selectedDrugLabel.setText(drugsName);
    selectedDrugLabel.setFont(font);
    le_setDose->setText(savedDose);

    w_setDose.resize(viewport()->width(),24);
    le_setDose->setFocus(Qt::OtherFocusReason);
    w_setDose.move(pos);

    w_setDose.show();
}

void drugsTable::resume_drug()
{

    QModelIndex cell =  this->selectionModel()->currentIndex();
    drugsModel->item(cell.row(),3)->setText(QString::number(QDate::currentDate().toJulianDay()));
    drugsModel->item(cell.row(),5)->setText(QString::number(1));
    QList<QStandardItem*> item = drugsModel->takeRow(cell.row());
    tableModel->insertRow(drugsModel->getPrintableDrugsCount(),item);
    emit drugTableItemChanged();
    genDrugTableToolTip();
    emit drugsHasBeenAltered(true);
    selectRow(cell.row());
}

void drugsTable::stop_drug()
{
    QModelIndex cell =  this->selectionModel()->currentIndex();
    drugsModel->item(cell.row(),4)->setText(QString::number(QDate::currentDate().toJulianDay()));
    drugsModel->item(cell.row(),5)->setText(QString::number(0));
    QList<QStandardItem*> item = drugsModel->takeRow(cell.row());
    tableModel->insertRow(drugsModel->getPrintableDrugsCount(),item);
    emit drugTableItemChanged();
    genDrugTableToolTip();
    emit drugsHasBeenAltered(true);
    selectRow(cell.row());
}

void drugsTable::drugsTableSort()
{
    QFont aFont,iFont;
    iFont.setItalic(true);
    iFont.setBold(false);
    aFont.setItalic(false);
    aFont.setBold(true);
    drugsModel->sort(5,Qt::DescendingOrder);
    for ( int row =0 ; row < drugsModel->rowCount() ; row++)
    {
        if ( drugsModel->item(row,5)->text().toInt() == 0)
        {
            drugsModel->setData(drugsModel->index(row,0),QVariant(QBrush(Qt::lightGray)), Qt::ForegroundRole);
            drugsModel->item(row,0)->setFont(iFont);


        }
        else
        {
            drugsModel->setData(drugsModel->index(row,0),QVariant(QBrush(Qt::black)), Qt::ForegroundRole);
            drugsModel->item(row,0)->setFont(aFont);
        }
    }
    genDrugTableToolTip();
    tweakDrugsTable();
    emit drugsHasBeenAltered(true);
}

void drugsTable::removeItemFromCompleter(QString item, QString tableName)
{
    sqlextra->removeFromAutoComplete(tableName,item);
}

void drugsTable::findSameTradename()
{
    QModelIndex cell = selectionModel()->currentIndex();
    QString rawTradeName = drugsModel->item(cell.row(),0)->text();
    QString tradeName = QString(rawTradeName.split(QRegExp("(\\d+(\\.\\d+)?)")).first()).simplified();

    //    if (tradeName.split(" ").count() > 1 )
    //    {
    //        QString first = tradeName.split(" ").at(0);
    //        QString second = tradeName.split(" ").at(1);
    //        tradeName = (first.length() > second.length())? first:second;
    //    }

    QStringList tradeNames = QStringList() << tradeName;
    findAltDrug("TRADENAME",tradeNames);
    setFindDrugsLabel(QString("Viewing drugs Similar to trade's name : <b>[%1]</b>").arg(tradeName));
    altDrugs->setSelectedDrugName(tradeName);
}

void drugsTable::findSameGeneric()
{
    QModelIndex cell = selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    QStringList rawGenericNames = drugsModel->item(cell.row(),1)->text().split("+");
    QStringList genericNames;

    foreach(QString gName,rawGenericNames)
    {
        QStringList tempString = gName.simplified().split(" ");
        tempString.removeLast();
        genericNames << tempString.join(" ").simplified();
    }

    findAltDrug("GENERICNAME",genericNames);
    setFindDrugsLabel(QString("Viewing drugs Similar to <b>[%1]</b> generic's name : <b>[%2]</b>").arg(tradeName).arg(genericNames.join(", ")));
    altDrugs->setSelectedDrugName(tradeName);
}

void drugsTable::findSameIndication()
{
    QModelIndex cell = selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    QString category = sqlcore->getDrugDetail(tradeName,"CATEGORY");
    if ( category.length() < 2)
    {
        popUpMessage("Error","Item Not Found!");
        return;
    }
    QString indication = category.split(":").at(0);
    QStringList indications = QStringList() << indication.simplified();
    findAltDrug("CATEGORY",indications);
    setFindDrugsLabel(QString("Viewing drugs Similar to <b>[%1]</b> indication : <b>[%2]</b>").arg(tradeName).arg(indications.join(", ")));
    altDrugs->setSelectedDrugName(tradeName);
}

void drugsTable::findSameGroup()
{
    QModelIndex cell = selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    QString category = sqlcore->getDrugDetail(tradeName,"CATEGORY");
    if ( category.length() < 2)
    {
        popUpMessage("Error","Item Not Found!");
        return;
    }
    QString indication = category.split(":").at(1);
    QStringList indications = QStringList() << indication.simplified();
    findAltDrug("CATEGORY",indications);
    setFindDrugsLabel(QString("Viewing drugs Similar to <b>[%1]</b> drug's group : <b>(%2)</b>").arg(tradeName).arg(indications.join(", ")));
    altDrugs->setSelectedDrugName(tradeName);
}

void drugsTable::searchGenricNameOnline()
{

    QModelIndex cell = selectionModel()->currentIndex();
    QString tradeName = drugsModel->item(cell.row(),0)->text();
    QStringList rawGenericNames = drugsModel->item(cell.row(),1)->text().split("+");
    QStringList genericNames;
    foreach(QString gName,rawGenericNames)
    {
        QStringList tempString = gName.simplified().split(" ");
        tempString.removeLast();
        genericNames << tempString.join(" ").simplified();
    }
    genericSearch->setTradeName(tradeName);
    genericSearch->setModel(genericNames);
    //genericSearch->move(mapToGlobal(pos()));
    genericSearch->show();
}

void drugsTable::copy2pDrugsList()
{
    int r = currentIndex().row();
    QList<QStringList> array;
    QStringList list;
    for ( int c = 0 ; c < 8 ; c++)
    {
        list << drugsModel->item(r,c)->text().simplified();
    }
    array.append(list);
    list.clear();
    emit syncDrugs(array,true);
}

void drugsTable::toggleAllDrugs()
{
    int rows = drugsModel->rowCount();
    int state = 0;
    QString caller = sender()->objectName();

    if (caller == "resumeAll")
        state = 1;
    else if (caller == "stopAll")
        state = 0;

    int reply = showMessageBox(QString("Are you sure that you want to %1 all drugs from list?").
                               arg((state==0)? "stop":"resume"));

    if(reply == QMessageBox::No)
        return;

    for (int row=0;row<rows;row++)
    {
        drugsModel->item(row,4)->setText(QString::number(QDate::currentDate().toJulianDay()));
        drugsModel->item(row,5)->setText(QString::number(state));
    }

    emit drugTableItemChanged();
    genDrugTableToolTip();
    emit drugsHasBeenAltered(true);
}

void drugsTable::calculateRxCosts()
{
    int rows = drugsModel->rowCount();
    int state;

    bool percision=true;

    double cost = 0;
    double itemPrice = 0;


    for (int row=0;row<rows;row++)
    {

        state = drugsModel->item(row,5)->text().toInt();
        itemPrice = drugsModel->item(row,7)->text().toDouble();

        if (state == 1)
        {
            cost += itemPrice;
            if (itemPrice == (double) 0)
                percision = false;
        }
    }
    emit showRxCost(cost,percision);
}

void drugsTable::Sync2Patient()
{
    bool sync=false;
    QString caller = sender()->objectName();

    if (caller == "update_drugs")
        sync = true;
    else if (caller == "overwrite_drugs")
        sync = false;

    SyncToPatient(sync);
}

QString drugsTable::getSelectedDrugTradeName()
{
    QModelIndex cell =  this->selectionModel()->currentIndex();
    return drugsModel->item(cell.row(),0)->text();
}

void drugsTable::findAltDrug(QString col, QStringList filters)
{
    altDrugs->show();
    findModel = sqlcore->getFindDrugsModel(findModel,col,filters);
    setFindDrugsModel(findModel);
}
