#include "sqlbase.h"

sqlBase::sqlBase(QObject *parent, QString connectionName, bool createTables) : msql(parent)
{
    //exConName = QString("qt_sql_extra_base_%1").arg(connectionName);
    QString path = QString("%1/data/patients.db").arg(QDir::currentPath());
    if ( ! createConnection(connectionName,path) )
    {
        mDebug() << "Failed to connect to patient database";
    }
    else if (createTables)
    {
        db.transaction();
        createPatientTable();
        createVisitsTable();
        createPatientDrugsTable();
        createSiblingsTable();
        createInvstTable();
        createPWtable();
        createSurgeryTable();
        createMetadataTable();
        createDeceasedTable();
        createVisitsPriceTable();
        createConditionsTable();
        insertDefaultConditions();
        createConditionsPatientTable();
        createAgendaView();
        createMyRegisterView();
        createEddView();
        createPerinatalTable();
        createDevelopmentTable();
        createObGynTable();
        createIndexes();
        db.commit();
    }

    crypto.setKey(0x0e3ec4f4dcb9b02f);

    if (!dataHelper::doubleEqual(getDatabaseVersion(),static_cast<double>(dbVersion)))
        upgradeDatabase();

    encryptionEnabled=isEncryptionEnabled();
    //sqlextra = new sqlExtra(this,exConName,createTables);
}

QStandardItemModel *sqlBase::getPatientsTableModel()
{
    encryptionEnabled=isEncryptionEnabled();
    QStringList deceasedList = getDeceasedList();
    query->clear();

    if ( ! query->exec("SELECT ID,Name,mobile,Age,Gender,Residence,maritalStatus,occupation FROM patients") )
    {
        mDebug() << query->lastError().text();
        query->finish();
    }
    else {
        int todayJulian = static_cast<int>(QDate::currentDate().toJulianDay());
        int row,ID;
        patientInfo info;
        QString toolTip;
        patientTableModel->blockSignals(true);
        patientTableModel->removeRows(0,patientTableModel->rowCount());

        while (query->next())
        {
            row = query->value(0).toInt() -1 ;
            ID  = query->value(0).toInt();
            QStandardItem *id_Item = new QStandardItem();
            id_Item->setData(QVariant(ID), Qt::DisplayRole);
            info.Name = getHumanizedName(query->value(1).toString());
            info.Mobile = query->value(2).toString();
            QStandardItem *name_Item = new QStandardItem(info.Name);
            QStandardItem *mobile_Item = new QStandardItem(info.Mobile);

            if ( deceasedList.contains(QString::number(ID)))
                name_Item->setData(QIcon(":/Graphics/redSkull"),Qt::DecorationRole);

            info.Age = getAge(todayJulian - query->value(3).toInt());

            info.Gender = query->value(4).toString();
            info.Residence = query->value(5).toString();
            info.MaritalStatus = query->value(6).toString();
            info.Occupation = query->value(7).toString();

            patientTableModel->setItem(row,0,id_Item);
            patientTableModel->setItem(row,1,name_Item);
            patientTableModel->setItem(row,2,mobile_Item);

            toolTip = getPatientTooltip(info);
            patientTableModel->item(row,0)->setToolTip(toolTip);
            patientTableModel->item(row,1)->setToolTip(toolTip);
        }
        query->finish();
    }
    return patientTableModel;
}

bool sqlBase::addPatient2myDataBase(Patient patient)
{
    QString sqlPhrase = createPatientInsertPreparePhrase();
    bool b = bindAndExecPatientSqlQuery(sqlPhrase,patient);
    return b;
}

bool sqlBase::addVisit2myDataBase(Visit visit)
{
    QString sqlPhrase = createVisitInsertPreparePhrase();
    return bindAndExecVisitSqlQuery(sqlPhrase,visit);
}

bool sqlBase::addSurgicalNote(int ID,QString surgeryID ,int julianDate, QString opName, QString opReport)
{
    return bindAndExecSurgicalNoteQuery(createSurgicalNotesPrepareInsertPhrase(),ID,surgeryID,julianDate,opName,opReport);
}

bool sqlBase::addInvestigation(int ID,int visitDate, QString invName, QString invPath, int invDate, QString invTime, int invState, double price, QString invResults)
{
    query->clear();
    //db.transaction();
    bool p = query->prepare( "INSERT INTO investigations  "
                             "(ID, "
                             "NAME, "
                             "VISITDATE, "
                             "PATH, "
                             "INVDATE, "
                             "INVTIME, "
                             "INVSTATE, "
                             "PRICE, "
                             "RESULTS) "
                             "VALUES("
                             ":ID, "
                             ":NAME, "
                             ":VISITDATE, "
                             ":PATH, "
                             ":INVDATE, "
                             ":INVTIME, "
                             ":INVSTATE, "
                             ":PRICE, "
                             ":RESULTS)");

    if (!p)
    {
        mDebug() << " FAILED TO ADD INVESTIGATION" << query->lastError().text();
    }

    query->bindValue(":ID",ID);
    query->bindValue(":NAME",invName);
    query->bindValue(":VISITDATE",visitDate);
    query->bindValue(":PATH",invPath);
    query->bindValue(":INVDATE",invDate);
    query->bindValue(":INVTIME",invTime);
    query->bindValue(":INVSTATE",invState);
    query->bindValue(":PRICE",price);
    query->bindValue(":RESULTS",invResults);

    bool e = query->exec();
    if ( !e )
    {
        mDebug() << "Failed to exec insert investigations" << query->lastError().text();
    }
    query->finish();

    if (!e || !p)
    {
        //db.rollback();
        mDebug() << "Failed to Save investigations";
        return false;
    }
    else
    {
        //db.commit();
        return true;
    }

}

bool sqlBase::isVisitExists(int ID, QString visitDateTime)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM visits where ID=%1 AND  visitDateTime='%2')").arg(ID).arg(visitDateTime);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isPatientExists(int ID)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM patients where ID=%1)").arg(ID);

    return bool(sqlExec(sqlCmd).toInt());
}

sqlBase::ServiceState sqlBase::isServiceExistsInThisVisit(int ID, int visitDate, QString ServiceName)
{
    QString sqlCmd = QString("SELECT PRICE FROM investigations "
                             "WHERE ID=%1 AND "
                             "NAME=\"%2\" AND "
                             "VISITDATE=%3 AND INVSTATE=2")
            .arg(ID)
            .arg(ServiceName)
            .arg(visitDate);
    sqlBase::ServiceState serviceState;
    double price =  sqlExec(sqlCmd).toDouble();
    serviceState.price = price;
    if (dataHelper::doubleEqual(price,0))
        serviceState.state = false;
    else
        serviceState.state = true;
    return serviceState;
}

sqlBase::Attended sqlBase::isFollowVisitAttended(int ID, int julianDate)
{
    QString sql = QString("SELECT visitTime,visitType FROM visits WHERE ID=%1 AND visitJulianDate=%2")
            .arg(ID)
            .arg(julianDate);

    Attended attended;
    attended.clear();

    query->clear();
    if (!query->exec(sql))
    {
        mDebug() << sql << query->lastError().text();
        return attended;
    }
    else if (!query->first())
    {
        return attended;
    }
    else
    {
        int time = query->value(0).toInt();
        attended.time = QTime::fromMSecsSinceStartOfDay(time*1000);
        attended.state = (time > 0) ? true:false;
        attended.visitType = query->value(1).toInt();
    }
    query->finish();
    return attended;
}

bool sqlBase::isPatientNameUsed(QString name)
{
    encryptionEnabled=isEncryptionEnabled();

    QString sqlPhrase = QString("SELECT ID,Name FROM patients");

    QList<QPair<QString,QString> > list = sqlExecPair(sqlPhrase);
    QPair<QString,QString> pair;

    foreach (pair, list)
    {
        QString _name = pair.second;

        if (getHumanizedName(_name) == name)
        {
            return true;
        }
    }

    return false;
}


bool sqlBase::updatePatient(int ID, Patient patient)
{
    QString sqlPhrase = createPatientUpdatePreparePhrase(ID);
    bool b = bindAndExecPatientSqlQuery(sqlPhrase,patient);
    return b;
}

bool sqlBase::updateVisit(int ID, QString visitDateTime, Visit visit)
{
    QString sqlPhrase = createVisitUpdatePreparePhrase(ID,visitDateTime);
    bool b = bindAndExecVisitSqlQuery(sqlPhrase,visit);
    return b;
}

bool sqlBase::savePatient(int ID, Patient patient)
{
    bool save = false;
    if ( patient.age.toInt() <= 2415020 ) // julian day of jan 1st 1900
        patient.age = QString::number(QDate::currentDate().toJulianDay());

    if ( isPatientExists(ID))
    {
        save = updatePatient(ID, patient);
    }
    else
    {
        save= addPatient2myDataBase(patient);
    }
    return save;
}

bool sqlBase::saveVisit(int ID, QString visitDateTime, Visit visit, double Price)
{
    bool save = false;

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QDateTime dt = locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd");

    if ( isVisitExists(ID,visitDateTime) )
    {
        save = updateVisit(ID, visitDateTime,visit);
        if (save)
            updateVisitPrice(ID,static_cast<int>(dt.date().toJulianDay()),dt.time().msecsSinceStartOfDay()/1000,Price);
    }
    else
    {
        save = addVisit2myDataBase(visit);
        if (save)
            setVisitPrice(ID,static_cast<int>(dt.date().toJulianDay()),dt.time().msecsSinceStartOfDay()/1000,Price);
    }
    return save;
}

bool sqlBase::savePatientData(Patient& patient,
                              DrugsItemModel *drugsModel,
                              QStandardItemModel *siblings,
                              QList<QPair<QString,int> > conditions,
                              development develop,
                              perinatal pnatal,
                              obGyn og)
{
    db.transaction();
    bool p = savePatient(patient.ID,patient);
    bool d = saveDrugs(patient.ID,0,drugsModel);
    bool s = saveSiblings(patient.ID,siblings);
    bool c = savePatientConditions(patient.ID,conditions);
    bool dv = saveDevelopment(develop);
    bool pn = savePerinatal(pnatal);
    bool o = saveObGyn(og);
    if ( !p || !d || !s || !c || !dv || !pn || !o)
    {
        db.rollback();
        return false;
    }
    db.commit();

    return true;
}

bool sqlBase::saveVisitData(sqlBase::visitData vdata)
{
    db.transaction();
    bool v = saveVisit(vdata.ID,vdata.visitDateTime,vdata.visit,vdata.visitPrice);
    bool d = saveDrugs(vdata.ID,vdata.visitDate,vdata.drugsModel);
    bool i = saveInvestigationsModel(vdata.ID,vdata.visitDate,vdata.invModel);
    if ( !v || !d || !i )
    {
        db.rollback();
        return false;
    }
    db.commit();
    return true;
}

DrugsItemModel *sqlBase::readDrugs(int ID, int visitDate,DrugsItemModel *drugsModel)
{
    //    drugsLoaded = true;
    drugsModel->clear();
    QStandardItem *item1,*item2,*item3,*item4,*item5,*item6,*item7,*item8;
    int x =0;
    query->clear();
    query->exec(QString("select * from drugs where id=%1 and visitdate=%2").arg(ID).arg(visitDate));
    while (query->next())
    {
        item1 = new QStandardItem( query->value(0).toString() );
        item2 = new QStandardItem( query->value(1).toString() );
        item3 = new QStandardItem( query->value(2).toString() );
        item4 = new QStandardItem( query->value(3).toString() );
        item5 = new QStandardItem( query->value(4).toString() );
        item6 = new QStandardItem( query->value(5).toString() );
        item7 = new QStandardItem( query->value(6).toString() );
        item8 = new QStandardItem( query->value(7).toString() );
        drugsModel->setItem(x,0,item1);
        drugsModel->setItem(x,1,item2);
        drugsModel->setItem(x,2,item3);
        drugsModel->setItem(x,3,item4);
        drugsModel->setItem(x,4,item5);
        drugsModel->setItem(x,5,item6);
        drugsModel->setItem(x,6,item7);
        drugsModel->setItem(x,7,item8);
        x+=1;
    }
    query->finish();
    return drugsModel;
}

QStandardItemModel *sqlBase::readSiblings(int ID, QStandardItemModel *model)
{
    QStandardItem *item1,*item2,*item3,*item4,*item5,*item6;
    model->removeRows(0,model->rowCount());
    int x =0;
    query->clear();
    query->exec(QString("select * from siblings where id=%1").arg(ID));
    while (query->next())
    {


        item1 = new QStandardItem( query->value(1).toString() );
        item2 = new QStandardItem( query->value(2).toString() );
        item3 = new QStandardItem( query->value(3).toString() );
        item4 = new QStandardItem( query->value(4).toString() );
        item5 = new QStandardItem( query->value(5).toString() );
        item6 = new QStandardItem( query->value(6).toString() );

        model->setItem(x,0,item1);
        model->setItem(x,1,item2);
        model->setItem(x,2,item3);
        model->setItem(x,3,item4);
        model->setItem(x,4,item5);
        model->setItem(x,5,item6);
        x+=1;
    }
    query->finish();
    return model;
}

QStandardItemModel *sqlBase::readSurgNotes(int ID, QStandardItemModel *model)
{
    QStandardItem *item0,*item1,*item2,*item3,*item4;
    model->removeRows(0,model->rowCount());
    QStringList labels = QStringList() << "OPID" << "ID" << "DATE" << "Operation" << "Report";
    model->setHorizontalHeaderLabels(labels);
    int x =0;
    query->clear();

    query->exec(QString("select * from surgicalNotes where id=%1").arg(ID));
    while (query->next())
    {

        item0 = new QStandardItem( query->value(0).toString() );
        item1 = new QStandardItem( query->value(1).toString() );
        item2 = new QStandardItem( QDate::fromJulianDay(query->value(2).toInt()).toString("dd/MM/yyyy") );
        item3 = new QStandardItem( query->value(3).toString() );
        item4 = new QStandardItem( query->value(4).toString() );

        model->setItem(x,0,item0);
        model->setItem(x,1,item1);
        model->setItem(x,2,item2);
        model->setItem(x,3,item3);
        model->setItem(x,4,item4);

        x+=1;
    }
    query->finish();
    return model;
}

bool sqlBase::saveDrugs(int ID, int visitDate, DrugsItemModel *model)
{
    QString tradeName,genericName,dose,form,price;
    int startDate,stopDate,state;
    bool b = false;

    QString deletePhrase =
            QString("DELETE FROM drugs WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(visitDate);
    //db.transaction();
    queryExec(deletePhrase);
    query->clear();
    int row_count = model->rowCount();
    if ( row_count == 0 )
        return true;

    for (int i = 0 ; i < row_count ; i++)
    {
        tradeName =  model->item(i,0)->text();
        genericName = model->item(i,1)->text();
        dose = model->item(i,2)->text();
        startDate = model->item(i,3)->text().toInt();
        stopDate = model->item(i,4)->text().toInt();
        state = model->item(i,5)->text().toInt();
        form = model->item(i,6)->text();
        price = model->item(i,7)->text();
        QString preparePhrase = QString("INSERT INTO "
                                        "drugs (ID,VISITDATE,STATE,STARTDATE,STOPDATE,TRADENAME,GENERICNAME,FORM,DOSE,PRICE) "
                                        "VALUES (:ID,:VISITDATE,:STATE,:STARTDATE,:STOPDATE,:TRADENAME,:GENERICNAME,:FORM,:DOSE,:PRICE) ");
        //

        query->prepare(preparePhrase);
        //
        query->bindValue(":ID" ,ID);
        query->bindValue(":VISITDATE",visitDate);
        query->bindValue(":STATE",state);
        query->bindValue(":STARTDATE",startDate);
        query->bindValue(":STOPDATE",stopDate);
        query->bindValue(":TRADENAME",tradeName);
        query->bindValue(":GENERICNAME",genericName);
        query->bindValue(":FORM",form);
        query->bindValue(":DOSE",dose);
        query->bindValue(":PRICE",price);

        b = query->exec();
        if ( !b )
        {
            mDebug() << "patient Query bind and Exec: " << query->lastError().text();
            query->finish();
            //db.rollback();
            return b;
        }
    }

    query->finish();
    //db.commit();

    return b;

}

bool sqlBase::saveSiblings(int ID, QStandardItemModel *model)
{
    QString dateOfBirth,Gender,TypeOfDelivery,PlaceOfBirth,Complications,term;

    bool b = false;

    QString deletePhrase =
            QString("DELETE FROM siblings WHERE ID=%1").arg(ID);
    //db.transaction();
    queryExec(deletePhrase);

    int row_count = model->rowCount();
    if ( row_count == 0 )
        return true;

    for (int i = 0 ; i < row_count ; i++)
    {
        dateOfBirth =  model->item(i,0)->text();
        TypeOfDelivery = model->item(i,1)->text();
        Gender = model->item(i,2)->text();
        PlaceOfBirth = model->item(i,3)->text();
        Complications = model->item(i,4)->text();
        term = model->item(i,5)->text();

        QString preparePhrase = QString("INSERT INTO "
                                        "siblings (ID,DOB,TypeOfDelivery,GENDER,PLACEOFBIRTH,COMPLICATIONS,TERM)"
                                        "VALUES(:ID,:DOB,:TypeOfDelivery,:GENDER,:PLACEOFBIRTH,:COMPLICATIONS,:TERM)");
        query->clear();
        query->prepare(preparePhrase);
        query->bindValue(":ID" ,ID);
        query->bindValue(":DOB",dateOfBirth);
        query->bindValue(":TypeOfDelivery",TypeOfDelivery);
        query->bindValue(":GENDER",Gender);
        query->bindValue(":PLACEOFBIRTH",PlaceOfBirth);
        query->bindValue(":COMPLICATIONS",Complications);
        query->bindValue(":TERM",term);

        b = query->exec();
        if ( !b )
        {
            mDebug() << "sibling Query bind and Exec: " << query->lastError().text();
            query->finish();
            //db.rollback();
            return b;
        }
    }

    query->finish();
    //db.commit();
    return b;
}

bool sqlBase::updateSurgicalNote(int ID ,QString surgeryID, int julianDate, QString opName, QString opReport)
{
    return bindAndExecSurgicalNoteQuery(createSurgicalNotesPrepareUpdatePhrase(ID,surgeryID),ID,surgeryID,julianDate,opName,opReport);
}

bool sqlBase::setVisitPrice(int ID, int visitDate, int visitTime, double price)
{
    QString query = QString("INSERT INTO visitPrices(ID,visitDate,visitTime,price) VALUES (%1,%2,%3,%4)")
            .arg(ID)
            .arg(visitDate)
            .arg(visitTime)
            .arg(price);
    return queryExec(query);
}

bool sqlBase::updateVisitPrice(int ID, int visitDate, int visitTime, double price)
{
    QString query = QString("UPDATE visitPrices SET price=%1 WHERE ID=%2 AND visitDate=%3 AND visitTime=%4")
            .arg(price)
            .arg(ID)
            .arg(visitDate)
            .arg(visitTime);
    return queryExec(query);
}

bool sqlBase::deleteVisitPrice(int ID, int visitDate, int visitTime)
{
    QString query = QString("DELETE FROM visitPrices WHERE ID=%1 AND visitDate=%2 AND visitTime=%3")
            .arg(ID)
            .arg(visitDate)
            .arg(visitTime);
    return queryExec(query);
}

sqlBase::Patient sqlBase::getPatientData(int ID)
{
    encryptionEnabled=isEncryptionEnabled();
    query->clear();
    bool q = query->exec(QString("SELECT * FROM patients WHERE ID=%1").arg(ID));
    if (!q)
    {
        mDebug() << "Failed to load patient" << query->lastError().text();
    }

    while (query->next())
    {
        patient.ID = query->value(QString("ID")).toInt();
        //patient.name = crypto.decryptToString(query->value(1).toString());
        patient.name = getHumanizedName(query->value(QString("Name")).toString());
        patient.dateTime = query->value(QString("dateTime")).toString();
        patient.age = query->value(QString("Age")).toString();
        patient.gender = query->value(QString("Gender")).toString();
        patient.residence = query->value(QString("Residence")).toString();
        patient.maritalStatus = query->value(QString("maritalStatus")).toString();
        patient.birthPlace = query->value(QString("birthPlace")).toString();
        patient.occupation = query->value(QString("occupation")).toString();
        patient.smoker = query->value(QString("smoker")).toString();
        patient.cigarretsPerDay = query->value(QString("cigarretsPerDay")).toString();
        patient.smokingYears = query->value(QString("smokingYears")).toString();
        patient.mobile = query->value(QString("mobile")).toString();
        patient.alcohol = query->value(QString("alcohol")).toString();

        patient.pastHistory = query->value(QString("pastHistory")).toString();
        patient.familyHistory = query->value(QString("familyHistory")).toString();
        patient.notes = query->value(QString("notes")).toString();
        patient.allergy = query->value(QString("allergy")).toString();
        patient.operations = query->value(QString("operations")).toString();
        patient.ABO = query->value(QString("ABO")).toInt();
    }

    if ( patient.age.toInt() <= 2415020 ) // julian day of jan 1st 1900
        patient.age = QString::number(QDate::currentDate().toJulianDay());

    query->finish();
    return patient;
}

sqlBase::mPatient sqlBase::getmPatientData(int ID)
{
    encryptionEnabled=isEncryptionEnabled();
    query->clear();

    bool q = query->exec(QString("SELECT * FROM patients WHERE ID=%1").arg(ID));
    if (!q)
    {
        mDebug() << "Failed to load patient" << query->lastError().text();
    }

    while (query->next())
    {
        mpatient.ID = query->value(0).toInt();
        //mpatient.name = crypto.decryptToString(query->value(1).toString());
        mpatient.name = getHumanizedName(query->value(1).toString());
        mpatient.dateTime = query->value(2).toString();
        mpatient.age = query->value(3).toString();
        mpatient.gender = query->value(4).toString();
        mpatient.residence = query->value(5).toString();
        mpatient.maritalStatus = query->value(6).toString();
        mpatient.birthPlace = query->value(7).toString();
        mpatient.occupation = query->value(8).toString();
        mpatient.smoker = query->value(9).toString();
        mpatient.cigarretsPerDay = query->value(10).toString();
        mpatient.smokingYears = query->value(11).toString();
        mpatient.mobile = query->value(12).toString();
        mpatient.alcohol = query->value(13).toString();
        mpatient.diabetes = query->value(14).toString();
        mpatient.hypertension = query->value(15).toString();
        mpatient.hyperlipidemia = query->value(16).toString();
        mpatient.chronicLiverDisease = query->value(17).toString();
        mpatient.chronicKidenyInjury = query->value(18).toString();
        mpatient.chronicObstructivePulmonaryDisease = query->value(19).toString();
        mpatient.peripheralVascularDisease = query->value(20).toString();
        mpatient.coronaryArteryDisease = query->value(21).toString();
        mpatient.bronchialAsthma = query->value(22).toString();
        mpatient.anemia = query->value(23).toString();
        mpatient.congestiveHeartFailure = query->value(24).toString();
        mpatient.hyperuricemia = query->value(25).toString();
        mpatient.bilharziasis = query->value(26).toString();
        mpatient.tuberculosis = query->value(27).toString();
        mpatient.pepticUlcer = query->value(28).toString();
        mpatient.IBS = query->value(29).toString();
        mpatient.pastHistory = query->value(30).toString();
        mpatient.familyHistory = query->value(31).toString();
        mpatient.notes = query->value(32).toString();
        mpatient.allergy = query->value(33).toString();
        mpatient.drugs = query->value(34).toString();
        mpatient.operations = query->value(35).toString();
        mpatient.devHead = query->value(36).toString();
        mpatient.devStand = query->value(37).toString();
        mpatient.devSit = query->value(38).toString();
        mpatient.devWalk = query->value(39).toString();
        mpatient.devCrawl = query->value(40).toString();
        mpatient.devTeeth = query->value(41).toString();
        mpatient.devMother = query->value(42).toString();
        mpatient.devlight = query->value(43).toString();
        mpatient.devSmile = query->value(44).toString();
        mpatient.devSpeech = query->value(45).toString();
        mpatient.devSound = query->value(46).toString();
        mpatient.pregLine = query->value(47).toString();
        mpatient.laborLine = query->value(48).toString();
        mpatient.NICULine = query->value(49).toString();
        mpatient.dietLine = query->value(50).toString();
        mpatient.GALine = query->value(51).toString();
        mpatient.GLine = query->value(52).toString();
        mpatient.PLine = query->value(53).toString();
        mpatient.LLine = query->value(54).toString();

        mpatient.ABO = query->value(55).toInt();
        mpatient.DMePregnancy = query->value(56).toString();
        mpatient.HTNePregnancy = query->value(57).toString();
        mpatient.AnemiaPregnancy = query->value(58).toString();
        mpatient.RheumaticFever = query->value(59).toString();
        mpatient.infertility = query->value(60).toString();
        mpatient.bloodTransfusion = query->value(61).toString();
        mpatient.varicoseVeins = query->value(62).toString();
        mpatient.CVS = query->value(63).toString();
        mpatient.MI = query->value(64).toString();
        mpatient.husband = query->value(65).toString();
        mpatient.GPA = query->value(66).toString();
        mpatient.menarche = query->value(67).toString();
        mpatient.menoPause = query->value(68).toString();
        mpatient.lastFor = query->value(69).toString();
        mpatient.every = query->value(70).toString();
        mpatient.cycle = query->value(71).toInt();
        mpatient.LMP = query->value(72).toInt();
        mpatient.FPAL = query->value(73).toString();
        mpatient.cyclePain = query->value(74).toInt();
        mpatient.DVT = query->value(75).toString();
        mpatient.NasalAllergy = query->value(76).toString();
        mpatient.CHOLECYSTITIS = query->value(77).toString();
        mpatient.OSTEOARTHERITIS = query->value(78).toString();
        mpatient.PERIPHERALNEUROPATHY = query->value(79).toString();
    }
    query->finish();
    return mpatient;
}

sqlBase::Visit sqlBase::getPatientVisitData(int ID, QString dateTimeString)
{
    query->clear();
    bool q = query->exec(QString("SELECT * FROM visits WHERE ID=%1 AND visitDateTime='%2'").arg(ID).arg(dateTimeString));

    if( !q )
    {
        mDebug() << query->lastError().text();
    }

    visit.clear();

    while (query->next())
    {
        visit.ID = query->value(0).toInt();
        visit.visitAge = query->value(1).toString();
        visit.presentation = query->value(2).toString();
        visit.presentationAnalysis = query->value(3).toString();
        visit.diagnosis = query->value(4).toString();
        visit.investigations = query->value(5).toString();
        visit.invResults = query->value(6).toString();
        visit.drugList = query->value(7).toString();
        visit.pulse = query->value(8).toString();
        visit.rr = query->value(9).toString();
        visit.temp = query->value(10).toString();
        visit.bp = query->value(11).toString();
        visit.weight = query->value(12).toString();
        visit.length = query->value(13).toString();
        visit.headCir = query->value(14).toString();
        visit.exGeneral = query->value(15).toString();
        visit.exChestHeart = query->value(16).toString();
        visit.exAbdback = query->value(17).toString();
        visit.exLL = query->value(18).toString();
        visit.visitNotes = query->value(19).toString();
        visit.visitDateTime = query->value(20).toString();
        visit.followDate = query->value(21).toString();
        visit.visitType = query->value(22).toString();
        visit.checkButtonCaseClose = query->value(23).toString();
        visit.LMPDATE = query->value(26).toInt();
        visit.ObstUS = query->value(27).toString();
        visit.Antenatal = query->value(28).toString();
        visit.pelvicExam = query->value(29).toString();

    }
    query->finish();
    return visit;

}

int sqlBase::getPatientIndexLength()
{
    int indexLength = 1;

    query->clear();

    bool q = query->exec("Select count(*) from patients");

    if ( !q )
        mDebug() << "get Index Length : " << query->lastError().text();

    while (query->next())
        indexLength = query->value(0).toInt() + 1;

    query->finish();


    return indexLength;
}

int sqlBase::getPatientIDfromName(QString patientName)
{
    encryptionEnabled=isEncryptionEnabled();

    QString _name;
    int _id;

    QString sqlPhrase = QString("SELECT ID,Name FROM patients");

    QList<QPair<QString,QString> > list = sqlExecPair(sqlPhrase);
    QPair<QString,QString> pair;

    foreach (pair, list)
    {
        _id = pair.first.toInt();
        _name = pair.second;

        if (getHumanizedName(_name) == patientName)
        {
            return _id;
        }
    }

    return 0;
}

QString sqlBase::getPatientNamefromID(int ID)
{
    QString sqlPhrase  = QString("SELECT Name FROM patients WHERE ID=%1").arg(ID);
    //return crypto.decryptToString(sqlExec(sqlPhrase));
    return sqlExec(sqlPhrase);
}

QStringList sqlBase::getPatientNameList()
{
    encryptionEnabled=isEncryptionEnabled();
    QString sqlPhrase = QString("SELECT Name FROM patients");
    return sqlExecList(sqlPhrase,true);
}


bool sortVisits(const sqlBase::visitItem& item1,const sqlBase::visitItem& item2)
{
    return item1.julianDay>item2.julianDay;
}

QVector<sqlBase::visitItem> sqlBase::getPatientVisits(int ID)
{
    query->clear();
    bool b = query->exec(
                QString("SELECT visitType,visitDateTime,diagnosis,visitJulianDate from visits WHERE ID=%1;").arg(ID));
    if(!b)
        mDebug() << "Failed getting visits List" << query->lastError().text();

    QVector<visitItem> vector;
    visitItem item;
    while(query->next())
    {
        item.visitType = query->value(0).toInt();
        item.visitDateTime = query->value(1).toString();
        item.Diagnosis = query->value(2).toString();
        item.julianDay = query->value(3).toInt();
        vector.append(item);
    }
    query->finish();
    qSort(vector.begin(),vector.end(),sortVisits);

    if(vector.isEmpty())
    {
        QLocale locale(QLocale::English , QLocale::UnitedStates );
        QDateTime dateTime = QDateTime::currentDateTime();
        item.visitDateTime = locale.toString(dateTime,"dd/MM/yyyy hh:mm AP ddd");
        item.julianDay = static_cast<int>(dateTime.date().toJulianDay());
        item.visitType = 0;
        item.Diagnosis = "";
        vector.append(item);
    }
    return vector;
}

bool sqlBase::deletePatientRecord(int ID)
{
    db.transaction();
    query->clear();
    bool p = query->exec(QString("DELETE FROM patients WHERE ID=%1").arg(ID));
    bool v = query->exec(QString("DELETE FROM visits WHERE ID=%1").arg(ID));
    bool i  = query->exec(QString("DELETE FROM investigations WHERE ID=%1").arg(ID));
    bool d  = query->exec(QString("DELETE FROM drugs WHERE ID=%1").arg(ID));
    bool s  = query->exec(QString("DELETE FROM siblings WHERE ID=%1").arg(ID));
    bool n  = query->exec(QString("DELETE FROM surgicalNotes WHERE ID=%1").arg(ID));
    bool k  = query->exec(QString("DELETE FROM deceased WHERE ID=%1").arg(ID));
    bool l  = query->exec(QString("DELETE FROM visitPrices WHERE ID=%1").arg(ID));
    bool c  = query->exec(QString("DELETE FROM conditions_patients WHERE ID=%1").arg(ID));
    bool dev  = query->exec(QString("DELETE FROM development WHERE ID=%1").arg(ID));
    bool pn  = query->exec(QString("DELETE FROM perinatal WHERE ID=%1").arg(ID));
    bool og  = query->exec(QString("DELETE FROM obgyn WHERE ID=%1").arg(ID));
    patient.clear();
    patient.name = QString("DELETED PATIENT #%1").arg(ID);
    patient.ID = ID;

    addPatient2myDataBase(patient);

    bool b = false;

    if ( p && v && d && i && s && n && k && l && c && dev && pn && og)
    {
        b = true;
        QDir d(QString("data/media/%1/").arg(ID));
        d.removeRecursively();
    }
    else
    {
        db.rollback();
    }
    query->finish();
    db.commit();
    return b;
}

bool sqlBase::copyVisit2ID(int fID, int tID, QStringList visitList)
{
    bool b= false;
    QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
    db.transaction();
    query->clear();

    foreach (QString visit, visitList)
    {
        int julianDate = static_cast<int>(locale.toDateTime(visit,"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());

        bool v1 = query->exec(QString("UPDATE visits SET ID=%1 WHERE ID=%2 AND visitJulianDate=%3").arg(tID).arg(fID).arg(julianDate));
        bool v2 = query->exec(QString("UPDATE investigations SET ID=%1 WHERE ID=%2 AND VISITDATE=%3").arg(tID).arg(fID).arg(julianDate));
        bool v3 = query->exec(QString("UPDATE drugs SET ID=%1 WHERE ID=%2 AND VISITDATE=%3").arg(tID).arg(fID).arg(julianDate));
        bool v4 = query->exec(QString("UPDATE visitPrices SET ID=%1 WHERE ID=%2 AND VISITDATE=%3").arg(tID).arg(fID).arg(julianDate));

        b=(v1 && v2 && v3 && v4);

        if (!b)
        {
            mDebug() << "ERROR COPY VISIT: ? : " << query->lastError().text();
            db.rollback();
            return b;
        }
    }

    query->finish();
    db.commit();

    return  b;

}

bool sqlBase::deletePatientVisit(int ID, int julianDate)
{
    query->clear();
    QStringList pathList =investigationsPathListForVisit(ID,julianDate);
    bool v1 = query->exec(QString("DELETE FROM visits WHERE ID=%1 AND visitJulianDate=%2").arg(ID).arg(julianDate));
    bool v2 = query->exec(QString("DELETE FROM investigations WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(julianDate));
    bool v3 = query->exec(QString("DELETE FROM drugs WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(julianDate));
    bool v4 = query->exec(QString("DELETE FROM visitPrices WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(julianDate));
    bool b=true;
    if (!v1 || !v2 || !v3 || !v4)
    {
        mDebug() << "ERROR DELETE VISIT: ? : " << query->lastError().text();
        b = false;
    }
    QString qCountPathCMD;
    int countPath;
    foreach (QString p, pathList)
    {
        qCountPathCMD = QString("SELECT COUNT(*)  FROM investigations WHERE PATH=\"%1\"").arg(p);
        countPath = sqlExec(qCountPathCMD).toInt();
        if ( countPath < 1 )
        {
            QFile f(p);
            f.remove();
        }

    }
    query->finish();
    db.commit();
    return  b;
}

bool sqlBase::deleteSugicalNote(int ID, QString surgeryID)
{
    bool b = queryExec(QString("DELETE FROM surgicalNotes WHERE ID=%1 AND surgeryID=%2").arg(ID).arg(surgeryID));
    if (!b)
    {
        mDebug() << "deleteSugicalNote" << query->lastError().text();
    }
    return b;

}

QString sqlBase::createPatientUpdatePreparePhrase(int ID)
{
    QString patientUpdatePreparePhrase =
            QString("UPDATE patients SET "
                    "ID=:ID,"
                    "Name=:Name,"
                    "dateTime=:dateTime,"
                    "Age=:Age,"
                    "Gender=:Gender,"
                    "Residence=:Residence,"
                    "maritalStatus=:maritalStatus,"
                    "birthPlace=:birthPlace,"
                    "occupation=:occupation,"
                    "smoker=:smoker,"
                    "cigarretsPerDay=:cigarretsPerDay,"
                    "smokingYears=:smokingYears,"
                    "mobile=:mobile,"
                    "alcohol=:alcohol,"
                    "pastHistory=:pastHistory,"
                    "familyHistory=:familyHistory,"
                    "notes=:notes,"
                    "allergy=:allergy,"
                    "operations=:operations,"
                    "ABO=:ABO"
                    " WHERE ID=%1").arg(ID);

    return patientUpdatePreparePhrase;
}

QString sqlBase::createVisitUpdatePreparePhrase(int ID, QString visitDateTime)
{
    QString visitUpdatePreparePhrase = QString(
                "UPDATE visits SET "
                "visitAge=:visitAge,"
                "presentation=:presentation,"
                "presentationAnalysis=:presentationAnalysis,"
                "diagnosis=:diagnosis,"
                "investigations=:investigations,"
                "invResults=:invResults,"
                "drugList=:drugList,"
                "pulse=:pulse,"
                "rr=:rr,"
                "temp=:temp,"
                "bp=:bp,"
                "weight=:weight,"
                "length=:length,"
                "headCir=:headCir,"
                "LMPDATE=:LMPDATE,"
                "ObstUS=:ObstUS,"
                "exGeneral=:exGeneral,"
                "exChestHeart=:exChestHeart,"
                "exAbdback=:exAbdback,"
                "exLL=:exLL,"
                "visitNotes=:visitNotes,"
                "followDate=:followDate,"
                "visitType=:visitType,"
                "checkButtonCaseClose=:checkButtonCaseClose,"
                "Antenatal=:Antenatal,"
                "pelvicExam=:pelvicExam "
                "WHERE ID=%1 AND visitDateTime='%2'").arg(ID).arg(visitDateTime);
    return visitUpdatePreparePhrase;
}

QString sqlBase::createSurgicalNotesPrepareUpdatePhrase(int ID ,QString surgeryID)
{
    return QString("UPDATE surgicalNotes "
                   "SET "
                   "operation=:operation,"
                   "report=:report,"
                   "dateTime=:dateTime "
                   "WHERE ID=%1 AND surgeryID=%2")
            .arg(ID)
            .arg(surgeryID);
}

QString sqlBase::createPatientInsertPreparePhrase()
{
    QString patientInsertPreparePhrase=
            QString("INSERT INTO patients "
                    "(ID,"
                    "Name,"
                    "dateTime,"
                    "Age,"
                    "Gender,"
                    "Residence,"
                    "maritalStatus,"
                    "birthPlace,"
                    "occupation,"
                    "smoker,"
                    "cigarretsPerDay,"
                    "smokingYears,"
                    "mobile,"
                    "alcohol,"
                    "pastHistory,"
                    "familyHistory,"
                    "notes,"
                    "allergy,"
                    "operations,"
                    "ABO) "
                    "VALUES "
                    "(:ID,"
                    ":Name,"
                    ":dateTime,"
                    ":Age,"
                    ":Gender,"
                    ":Residence,"
                    ":maritalStatus,"
                    ":birthPlace,"
                    ":occupation,"
                    ":smoker,"
                    ":cigarretsPerDay,"
                    ":smokingYears,"
                    ":mobile,"
                    ":alcohol,"
                    ":pastHistory,"
                    ":familyHistory,"
                    ":notes,"
                    ":allergy,"
                    ":operations,"
                    ":ABO)");
    return patientInsertPreparePhrase;
}

QString sqlBase::createVisitInsertPreparePhrase()
{
    QString visitInsertPreparePhrase =
            QString(
                "INSERT INTO visits"
                "("
                "ID,"
                "visitAge,"
                "presentation,"
                "presentationAnalysis,"
                "diagnosis,"
                "investigations,"
                "invResults,"
                "drugList,"
                "pulse,"
                "rr,"
                "temp,"
                "bp,"
                "weight,"
                "length,"
                "headCir,"
                "exGeneral,"
                "exChestHeart,"
                "exAbdback,"
                "exLL,"
                "visitNotes,"
                "visitDateTime,"
                "followDate,"
                "visitType,"
                "checkButtonCaseClose,"
                "visitJulianDate,"
                "visitTime,"
                "LMPDATE,"
                "ObstUS,"
                "Antenatal,"
                "pelvicExam)"
                "VALUES"
                "("
                ":ID,"
                ":visitAge,"
                ":presentation,"
                ":presentationAnalysis,"
                ":diagnosis,"
                ":investigations,"
                ":invResults,"
                ":drugList,"
                ":pulse,"
                ":rr,"
                ":temp,"
                ":bp,"
                ":weight,"
                ":length,"
                ":headCir,"
                ":exGeneral,"
                ":exChestHeart,"
                ":exAbdback,"
                ":exLL,"
                ":visitNotes,"
                ":visitDateTime,"
                ":followDate,"
                ":visitType,"
                ":checkButtonCaseClose,"
                ":visitJulianDate,"
                ":visitTime,"
                ":LMPDATE,"
                ":ObstUS,"
                ":Antenatal,"
                ":pelvicExam)");

    return visitInsertPreparePhrase;
}

QString sqlBase::createSurgicalNotesPrepareInsertPhrase()
{
    return QString("INSERT INTO surgicalNotes "
                   "(surgeryID,ID,dateTime,operation,report)"
                   "VALUES"
                   "(:surgeryID,:ID,:dateTime,:operation,:report)");
}

bool sqlBase::bindAndExecPatientSqlQuery(QString queryPhrase, Patient patient)
{
    encryptionEnabled=isEncryptionEnabled();
    query->clear();
    int ID = patient.ID;
    query->prepare(queryPhrase);

    query->bindValue(":ID",ID);
    //query->bindValue(":Name",crypto.encryptToString(patient.name));
    query->bindValue(":Name",getComputerizedName(patient.name));
    query->bindValue(":dateTime",patient.dateTime);
    query->bindValue(":Age",patient.age);
    query->bindValue(":Gender",patient.gender);
    query->bindValue(":Residence",patient.residence);
    query->bindValue(":maritalStatus" ,patient.maritalStatus);
    query->bindValue(":birthPlace" ,patient.birthPlace);
    query->bindValue(":occupation", patient.occupation);
    query->bindValue(":smoker" ,patient.smoker);
    query->bindValue(":cigarretsPerDay" ,patient.cigarretsPerDay);
    query->bindValue(":smokingYears" ,patient.smokingYears);
    query->bindValue(":mobile" ,patient.mobile);
    query->bindValue(":alcohol" ,patient.alcohol);

    query->bindValue(":pastHistory" ,patient.pastHistory);
    query->bindValue(":familyHistory" ,patient.familyHistory);
    query->bindValue(":notes" ,patient.notes);
    query->bindValue(":allergy" ,patient.allergy);

    query->bindValue(":operations" ,patient.operations);

    query->bindValue(":ABO",patient.ABO);
    bool b = query->exec();
    query->finish();
    if ( !b  )
    {
        mDebug() << "patient Query bind and Exec: " << query->lastError().text();
        //db.rollback();
        query->finish();
        return b;
    }
    //db.commit();
    query->finish();
    return b;
}

bool sqlBase::bindAndExecVisitSqlQuery(QString queryPhrase, Visit visit)
{
    int ID = visit.ID;
    QLocale locale(QLocale::English , QLocale::UnitedStates );
    QDateTime dt = locale.toDateTime(visit.visitDateTime,"dd/MM/yyyy hh:mm AP ddd");
    int visitJulianDate = static_cast<int>(dt.date().toJulianDay());
    int visitTime = dt.time().msecsSinceStartOfDay()/1000;
    query->clear();
    //db.transaction();

    bool p = query->prepare(queryPhrase);

    if(!p)
    {
        mDebug() << "Prepare" << query->lastError().text();
    }

    query->bindValue(":ID", ID);
    query->bindValue(":visitAge",visit.visitAge);
    query->bindValue(":presentation",visit.presentation);
    query->bindValue(":presentationAnalysis",visit.presentationAnalysis);
    query->bindValue(":diagnosis",visit.diagnosis);
    query->bindValue(":investigations",visit.investigations);
    query->bindValue(":invResults",visit.invResults);
    query->bindValue(":drugList",visit.drugList);
    query->bindValue(":pulse",visit.pulse);
    query->bindValue(":rr",visit.rr);
    query->bindValue(":temp",visit.temp);
    query->bindValue(":bp",visit.bp);
    query->bindValue(":weight",visit.weight);
    query->bindValue(":length",visit.length);
    query->bindValue(":headCir",visit.headCir);
    query->bindValue(":exGeneral",visit.exGeneral);
    query->bindValue(":exChestHeart",visit.exChestHeart);
    query->bindValue(":exAbdback",visit.exAbdback);
    query->bindValue(":exLL",visit.exLL);
    query->bindValue(":visitNotes",visit.visitNotes);
    query->bindValue(":visitDateTime",visit.visitDateTime);
    query->bindValue(":followDate",visit.followDate.toInt());
    query->bindValue(":visitType",visit.visitType);
    query->bindValue(":checkButtonCaseClose",visit.checkButtonCaseClose );
    query->bindValue(":visitJulianDate",visitJulianDate);
    query->bindValue(":visitTime",visitTime);
    query->bindValue(":LMPDATE",visit.LMPDATE);
    query->bindValue(":ObstUS",visit.ObstUS);
    query->bindValue(":Antenatal",visit.Antenatal);
    query->bindValue(":pelvicExam",visit.pelvicExam);

    bool b = query->exec();
    query->finish();
    if ( !b )
    {
        mDebug() << "exec" << query->lastError().text();
    }
    //db.commit();
    return b;
}

bool sqlBase::bindAndExecSurgicalNoteQuery(QString queryPhrase,int ID,QString surgeryID ,int julianDate, QString opName, QString opReport)
{
    query->clear();
    bool p = query->prepare(queryPhrase);

    if(!p)
    {
        mDebug() << "Prepare" << query->lastError().text();
    }

    query->bindValue(":ID",ID);
    query->bindValue(":surgeryID",surgeryID);
    query->bindValue(":dateTime",julianDate);
    query->bindValue(":operation",opName);
    query->bindValue(":report",opReport);

    bool b = query->exec();
    query->finish();
    if ( !b )
    {
        mDebug() << "exec" << query->lastError().text();
    }
    return b;
}

sqlBase::~sqlBase()
{
    query->finish();
}

bool sqlBase::isEncryptionEnabled()
{
    return bool(sqlExec("SELECT version from metadata WHERE data='encryption';").toInt() );
}

void sqlBase::toggleEncryption(bool enabled)
{
    if ( sqlExec("SELECT EXISTS(SELECT 1 FROM metadata WHERE data='encryption' LIMIT 1);").toInt() )
        sqlExec(QString("UPDATE metadata SET version='%1' WHERE data='encryption'").arg(int(enabled)));
    else
        sqlExec(QString("INSERT INTO metadata (data,version) VALUES ('encryption','%1');").arg(int(enabled)));

    encryptDecryptNames(enabled);

}

bool sqlBase::deleteInvestigationMedia(const QString &path)
{
    bool mediaFileisNotUsed =
            (sqlExec(QString("SELECT COUNT(*) FROM INVESTIGATIONS WHERE PATH=\"%1\"")
                     .arg(path)).toInt() == 0 );

    QFile f(path);

    if (path.length() > 8 && f.exists() && mediaFileisNotUsed)
    {
        f.remove();
        return true;
    }
    else
    {
        return false;
    }

}

int sqlBase::getDrugsCout(int id, int date)
{
    int count = 0;

    query->clear();

    bool q = query->exec(QString("Select count(*) from drugs where id=%1 and visitdate=%2 ").arg(id).arg(date));

    if ( !q )
        mDebug() << "get Index Length : " << query->lastError().text();

    while (query->next())
        count = query->value(0).toInt();

    query->finish();

    return count;
}

bool sqlBase::createPatientTable()
{
    query->clear();
    bool b = query->exec ("CREATE TABLE IF NOT EXISTS patients"
                          "("
                          "ID  INTEGER PRIMARY KEY,"
                          "Name    varchar,"
                          "dateTime    varchar,"
                          "Age varchar,"
                          "Gender	varchar,"
                          "Residence	varchar,"
                          "maritalStatus	varchar,"
                          "birthPlace	varchar,"
                          "occupation	varchar,"
                          "smoker	varchar,"
                          "cigarretsPerDay	varchar,"
                          "smokingYears	varchar,"
                          "mobile	varchar,"
                          "alcohol varchar,"
                          "pastHistory	varchar,"
                          "familyHistory	varchar,"
                          "notes	varchar,"
                          "allergy	varchar,"
                          "operations	varchar,"
                          "ABO integer"
                          ")");


    query->finish();
    return b;
}

bool sqlBase::createVisitsTable()
{
    query->clear();
    bool b = query->exec ("CREATE TABLE IF NOT EXISTS visits"
                          "("
                          "ID INTEGER,"
                          "visitAge varchar,"
                          "presentation   varchar,"
                          "presentationAnalysis   varchar,"
                          "diagnosis   varchar,"
                          "investigations   varchar,"
                          "invResults   varchar,"
                          "drugList   varchar,"
                          "pulse   varchar,"
                          "rr   varchar,"
                          "temp   varchar,"
                          "bp   varchar,"
                          "weight   varchar,"
                          "length   varchar,"
                          "headCir   varchar,"
                          "exGeneral   varchar,"
                          "exChestHeart   varchar,"
                          "exAbdback   varchar,"
                          "exLL   varchar,"
                          "visitNotes   varchar,"
                          "visitDateTime   varchar,"
                          "followDate   integer,"
                          "visitType   varchar,"
                          "checkButtonCaseClose   varchar,"
                          "visitJulianDate integer,"
                          "visitTime integer,"
                          "LMPDATE integer,"
                          "ObstUS varchar,"
                          "Antenatal integer,"
                          "pelvicExam varchar)");

    if (!b)
    {
        mDebug() << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createPatientDrugsTable()
{
    query->clear();
    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS drugs("
             "TRADENAME   varchar,"
             "GENERICNAME   varchar,"
             "DOSE   varchar,"
             "STARTDATE   INTEGER,"
             "STOPDATE   INTEGER,"
             "STATE   INTEGER,"
             "FORM   varchar,"
             "ID INTEGER,"
             "VISITDATE INTEGER,"
             "PRICE INTEGER)");
    if (!b)
    {
        mDebug() << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createSiblingsTable()
{
    query->clear();
    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS siblings("
             "ID integer,"
             "DOB   varchar,"
             "TypeOfDelivery   varchar,"
             "GENDER   varchar,"
             "PLACEOFBIRTH   varchar,"
             "COMPLICATIONS   varchar,"
             "TERM   varchar)");
    if (!b)
    {
        mDebug() << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createInvstTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS investigations("
             "ID   int,"
             "NAME   varchar,"
             "VISITDATE   INTEGER,"
             "PATH   varchar,"
             "INVDATE   INTEGER,"
             "INVTIME   varchar,"
             "INVSTATE INTEGER,"
             "PRICE varchar,"
             "RESULTS varchar)");
    if (!b)
    {
        mDebug() << "ERROR CREATING INVESTIGATIONS TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createPWtable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS credentials("
             "userName   varchar,"
             "passwordHash   varchar)");

    if (!b)
    {
        mDebug() << "ERROR CREATING PW TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createMetadataTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS metadata("
             "data varchar,"
             "version   varchar)");

    if (!b)
    {
        mDebug() << "ERROR CREATING metadata TABLE" << query->lastError().text();
    }


    query->finish();
    return b;
}

bool sqlBase::createSurgeryTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS surgicalNotes("
             "surgeryID varchar UNIQUE,"
             "ID int,"
             "dateTime   varchar,"
             "operation   varchar,"
             "report varchar)");

    if (!b)
    {
        mDebug() << "ERROR CREATING surgicalNotes TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createDeceasedTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS deceased("
             "ID int UNIQUE,"
             "state int)");

    if (!b)
    {
        mDebug() << "ERROR CREATING deceased TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createVisitsPriceTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS visitPrices("
             "ID int,"
             "visitDate int,"
             "visitTime int,"
             "price varchar)");

    if (!b)
    {
        mDebug() << "ERROR CREATING VISIT PRICE TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createConditionsTable()
{
    query->clear();

    bool b = query->exec
            ("CREATE TABLE IF NOT EXISTS conditions("
             "_id int UNIQUE,"
             "state int,"
             "name varchar)");

    if (!b)
    {
        mDebug() << "ERROR CREATING COMMON CONDITIONS TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createConditionsPatientTable()
{
    QStringList list = sqlExecList("SELECT _id From conditions");
    QString querycmd = "CREATE TABLE IF NOT EXISTS conditions_patients(ID int UNIQUE";
    foreach (QString c, list)
    {
        querycmd.append(QString(",c%1 int").arg(c));
    }
    querycmd.append(")");
    query->clear();

    bool b = query->exec(querycmd);

    if (!b)
    {
        mDebug() << "ERROR CREATING PATIENTS CONDITIONS TABLE" << query->lastError().text();
    }

    query->finish();
    return b;
}

bool sqlBase::createPerinatalTable()
{
    bool b = queryExec("create table if not exists perinatal (ID integer primary key,pregLine varchar,laborLine varchar,NICULine varchar,dietLine varchar,GALine varchar,GLine varchar,PLine varchar,LLine varchar);");

    if (!b)
        mDebug() << "ERROR CREATING PERINATAL TABLE" << query->lastError().text();
    return b;
}

bool sqlBase::createObGynTable()
{
    bool b = queryExec("create table if not exists obgyn "
                       "(ID integer primary key,"
                       "husband  varchar,"
                       "GPA  varchar,"
                       "menarche  varchar,"
                       "menoPause  varchar,"
                       "lastFor  varchar,"
                       "every  varchar,"
                       "cycle varchar,"
                       "LMP  varchar,"
                       "FPAL varchar,"
                       "cyclePain varchar);");

    if (!b)
        mDebug() << "ERROR CREATING OBGYN TABLE" << query->lastError().text();
    return b;
}

bool sqlBase::createDevelopmentTable()
{
    query->clear();
    bool b = query->exec("CREATE TABLE IF NOT EXISTS development"
                         "("
                         "ID  INTEGER PRIMARY KEY,"
                         "devHead  varchar,"
                         "devStand      varchar,"
                         "devSit      varchar,"
                         "devWalk      varchar,"
                         "devCrawl      varchar,"
                         "devTeeth      varchar,"
                         "devMother      varchar,"
                         "devlight      varchar,"
                         "devSmile      varchar,"
                         "devSpeech      varchar,"
                         "devSound      varchar"
                         ")");

    if (!b)
    {
        mDebug() << "Failed to create development table:" << query->lastError().text();
    }
    query->finish();
    return b;

}

bool sqlBase::isUserExists(QString user)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM credentials where userName=\"%1\")").arg(user);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isConditionRowExists(int ID)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM conditions_patients where ID=%1)").arg(ID);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isDevelopmentRowExists(int ID)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM development where ID=%1)").arg(ID);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isObGynRowExists(int ID)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM obgyn where ID=%1)").arg(ID);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isPerinatalRowExists(int ID)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM perinatal where ID=%1)").arg(ID);
    return bool(sqlExec(sqlCmd).toInt());
}

bool sqlBase::isPasswordSet()
{

    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM credentials where length(passwordHash)>1)");
    return bool(sqlExec(sqlCmd).toInt());

}

bool sqlBase::updateLMP(int ID, int julianDate)
{
    QString sqlCMD = QString("UPDATE obgyn SET LMP=%1 WHERE ID=%2").arg(julianDate).arg(ID);
    return queryExec(sqlCMD);
}

//void sqlBase::fixDatabase()
//{

//    emit showProgress("Please wait while optimizing database performance...");
//    QStringList tables = db.tables(QSql::AllTables);

//    foreach (QString table, tables)
//    {
//        QApplication::processEvents();
//        queryExec(QString("VACUUM `%1`").arg(table));
//        //mDebug() << table;
//    }
//    // clean sqlextra
//    sqlextra->fixDatabase();
//    emit hideProgress();
//    QMessageBox::information(0,"Message","You have successfuly cleared patients' database from unused data that might cause slow downs, good for you!",QMessageBox::Ok);


/*
    float databaseVersion = getDatabaseVerion();
    if ( float(dbVersion) > databaseVersion )
    {
    emit showProgress();
    QString name;
    int iLength = getPatientIndexLength();
    for ( int p = 1 ; p < iLength ; p++)
    {
        QApplication::processEvents();
        name = sqlExec(QString("SELECT Name FROM patients WHERE ID=%1").arg(p));
        query->clear();
        query->prepare("UPDATE patients SET Name=:Name WHERE ID=:ID");
        query->bindValue(":Name",crypto.decryptToString(name));
        //query->bindValue(":Name",name);
        query->bindValue(":ID",p);
        query->exec();
        query->finish();
        //emit showMessage("Upgrading Database",QString("encrypting patient name %1 of %2").arg(p).arg(iLength));

    }
    emit reloadPatientList();
    emit hideProgress();//
    db.transaction();
    emit showProgress();
    queryExec("DROP VIEW agendaView");
    createAgendaView();
    if (!columnExists("cyclePain","patients"))
    {
        queryExec("ALTER TABLE patients ADD ABO");
        queryExec("ALTER TABLE patients ADD DMePregnancy");
        queryExec("ALTER TABLE patients ADD HTNePregnancy");
        queryExec("ALTER TABLE patients ADD AnemiaPregnancy");
        queryExec("ALTER TABLE patients ADD RheumaticFever");
        queryExec("ALTER TABLE patients ADD infertility");
        queryExec("ALTER TABLE patients ADD bloodTransfusion");
        queryExec("ALTER TABLE patients ADD varicoseVeins");
        queryExec("ALTER TABLE patients ADD CVS");
        queryExec("ALTER TABLE patients ADD MI");
        queryExec("ALTER TABLE patients ADD husband");
        queryExec("ALTER TABLE patients ADD GPA");
        queryExec("ALTER TABLE patients ADD menarche");
        queryExec("ALTER TABLE patients ADD menoPause");
        queryExec("ALTER TABLE patients ADD lastFor");
        queryExec("ALTER TABLE patients ADD every");
        queryExec("ALTER TABLE patients ADD cycle");
        queryExec("ALTER TABLE patients ADD LMP");
        queryExec("ALTER TABLE patients ADD FPAL");
        queryExec("ALTER TABLE patients ADD cyclePain");
    }
    if (!columnExists("pelvicExam","visits"))
    {
        queryExec("ALTER TABLE visits ADD LMPDATE");
        queryExec("ALTER TABLE visits ADD ObstUS");
        queryExec("ALTER TABLE visits ADD Antenatal");
        queryExec("ALTER TABLE visits ADD pelvicExam");

    }
    //queryExec("ALTER TABLE drugs ADD PRICE");


    queryExec("CREATE TEMPORARY TABLE t_DRUGS(TRADENAME,GENERICNAME,DOSE,STARTDATE,STOPDATE,STATE,FORM,ID,VISITDATE)");
    queryExec("INSERT INTO t_DRUGS SELECT * FROM drugs");
    queryExec("DROP TABLE drugs");
    queryExec("CREATE  TABLE drugs(TRADENAME,GENERICNAME,DOSE,STARTDATE,STOPDATE,STATE,FORM,PRICE,ID,VISITDATE)");
    queryExec("INSERT INTO drugs (TRADENAME,GENERICNAME,DOSE,STARTDATE,STOPDATE,STATE,FORM,ID,VISITDATE) SELECT TRADENAME,GENERICNAME,DOSE,STARTDATE,STOPDATE,STATE,FORM,ID,VISITDATE FROM t_DRUGS");
    queryExec("DROP TABLE t_DRUGS");

    sqlextra->createTable("placeOfBirth");
    createSurgeryTable();




    query->clear();
    QStringList tradenames;
    if ( ! query->exec("SELECT TRADENAME FROM drugs") )
    {
        mDebug() << "failed to update prices";
    }
    while (query->next())
    {
        tradenames << query->value(0).toString();
    }
    query->finish();
    sqlCore sqlcore;
    int x=0;
    foreach (QString tradename, tradenames)
    {
        queryExec(QString("UPDATE drugs SET PRICE=\"%1\" WHERE TRADENAME=\"%2\"")
                  .arg(sqlcore.getDrugDetail(tradename,"PRICE")).arg(tradename));
        QApplication::processEvents();
        mDebug() << x;
        x++;
    }


    db.commit();
    showMessage("Upgrading Database","Done!");
    setDatabaseVersion(dbVersion);
    emit hideProgress();
      */
//}

int sqlBase::getFollowUpsCountForThisDate(QDate dt,int ID)
{
    qint64 julianDate = dt.toJulianDay();
    query->clear();
    bool x = query->exec(QString("SELECT * FROM agendaView "
                                 "WHERE followDate=%1 AND checkButtonCaseClose=\"false\"")
                         .arg(julianDate));
    if ( !x )
    {
        mDebug() << "Failed to get follow up count " << query->lastError().text();
    }

    int c = 0;
    QList<int> cList;
    int _id;
    while(query->next())
    {
        _id = query->value(0).toInt();
        if (!cList.contains(_id) && ID != _id)
            c += 1;
        cList << _id;
    }
    query->finish();
    return c;
}

bool sqlBase::exportPatientListToXML(QString fileName)
{
    query->clear();
    if ( ! query->exec("SELECT ID,Name,mobile FROM patients") )
    {
        mDebug() << query->lastError().text();
        query->finish();
        return false;
    }
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return false;
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Patients");
    while (query->next())
    {
        xmlWriter.writeStartElement("patient");
        xmlWriter.writeTextElement("ID",query->value(0).toString());
        xmlWriter.writeTextElement("Name",query->value(1).toString());
        xmlWriter.writeTextElement("Mobile",query->value(2).toString());
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndDocument();
    query->finish();
    file.close();
    return true;
}

bool sqlBase::exportPatientListToXLS(QString fileName)
{
    encryptionEnabled=isEncryptionEnabled();
    query->clear();

    if ( ! query->exec("SELECT ID,Name,mobile FROM patients") )
    {
        mDebug() << query->lastError().text();
        query->finish();
        return false;
    }
    else {
        QString ID,Name,Mobile;
        excelExport excelexport;
        if(!excelexport.createXLS(fileName))
            return false;

        while (query->next())
        {
            ID = query->value(0).toString();
            Name = getHumanizedName(query->value(1).toString());
            Mobile = query->value(2).toString();
            excelexport.addRow(ID,Name,Mobile);
        }
        query->finish();
        excelexport.closeFile();
    }
    return true;
}

QStringList sqlBase::getDeceasedList()
{
    QString sqlPhrase = QString("SELECT * FROM deceased WHERE state=1;");
    return sqlExecList(sqlPhrase);
}

void sqlBase::toggleDeceased(int ID, int state,int row)
{
    QString cmd;
    bool s1 = bool(sqlExec(QString("SELECT EXISTS(SELECT * FROM deceased where ID=%1)").arg(ID)).toInt());
    if ( s1)
        cmd = QString("UPDATE deceased SET state=%1 WHERE ID=%2;").arg(state).arg(ID);
    else
        cmd = QString("INSERT INTO deceased (ID,state) VALUES (%1,%2);").arg(ID).arg(state);

    if ( !query->exec(cmd))
        mDebug() << cmd << query->lastError().text();

    bool s2 = getDeceasedList().contains(QString::number(ID));
    emit patientIconSet(s2,row);
}

bool sqlBase::createAgendaView()
{
    query->clear();
    bool x = query->exec("CREATE VIEW IF NOT EXISTS agendaView AS SELECT "
                         "visits.ID,patients.Name,visits.followDate,"
                         "visits.checkButtonCaseClose,visits.visitJulianDate,"
                         "patients.mobile,patients.Age,patients.Gender,"
                         "patients.Residence,patients.maritalStatus,patients.occupation,visits.visitType "
                         "FROM visits LEFT JOIN patients USING (ID)");
    if (!x)
    {
        mDebug() << "Failed to create agenda view ? " << query->lastError().text();
    }
    query->finish();
    return x;
}

bool sqlBase::createMyRegisterView()
{
    query->clear();
    bool x = query->exec("CREATE VIEW IF NOT EXISTS registerView AS SELECT DISTINCT "
                         "visits.ID,patients.Name,visits.visitType,"
                         "visits.visitJulianDate,visits.visitTime,"
                         "visitPrices.price,"
                         "patients.mobile,patients.Age,patients.Gender,"
                         "patients.Residence,patients.maritalStatus,patients.occupation "
                         "FROM visits "
                         "INNER JOIN patients USING(ID) "
                         "INNER JOIN visitPrices WHERE "
                         "visits.visitJulianDate = visitPrices.visitDate "
                         "AND visits.visitTime = visitPrices.visitTime "
                         "AND visitPrices.ID = patients.ID");
    if (!x)
    {
        mDebug() << "Failed to create myRegister view ? " << query->lastError().text();
    }

    query->finish();
    return x;
}

bool sqlBase::createEddView()
{
    query->clear();
    bool x = query->exec("CREATE VIEW IF NOT EXISTS EddView AS SELECT "
                         "patients.ID, patients.Name, patients.Age, patients.Gender, patients.Residence, "
                         "patients.maritalStatus, patients.occupation, patients.mobile, "
                         "visits.LMPDATE , visits.Antenatal , max(visits.visitJulianDate) , obgyn.GPA "
                         "FROM patients "
                         "LEFT JOIN obgyn USING (ID) "
                         "LEFT JOIN visits USING (ID) "
                         "GROUP BY ID ");

    if (!x)
    {
        mDebug() << "Failed to create EDD view ? " << query->lastError().text();
    }
    query->finish();
    return x;
}

bool sqlBase::columnExists(QString colName, QString table)
{
    query->clear();
    query->exec(QString("PRAGMA table_info(%1)").arg(table));
    while(query->next())
    {
        if ( query->value(1).toString() ==colName )
        {
            query->finish();
            return true;
        }
    }
    query->finish();
    return false;
}

void sqlBase::createIndexes()
{
    queryExec("CREATE INDEX if not exists index_drugs ON drugs (ID)");
    queryExec("CREATE INDEX if not exists index_investigations ON investigations (ID)");
    queryExec("CREATE INDEX if not exists index_patients ON patients (ID,Name)");
    queryExec("CREATE INDEX if not exists index_visits ON visits (ID,visitJulianDate,visitTime,followDate,checkButtonCaseClose,visitDateTime)");
    queryExec("CREATE INDEX if not exists index_visitPrices ON visitPrices (ID)");
    queryExec("CREATE INDEX if not exists index_conditions_patients ON conditions_patients (ID)");
    queryExec("CREATE INDEX if not exists index_siblings ON siblings (ID)");
    queryExec("CREATE INDEX if not exists index_surgicalNotes ON surgicalNotes (ID)");
    queryExec("CREATE INDEX if not exists index_development ON development (ID)");
    queryExec("CREATE INDEX if not exists index_perinatal ON perinatal (ID)");
}

void sqlBase::upgradeDatabase()
{
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.80)) )
    {
        if (migrateSmoking())
            setDatabaseVersion(2.81);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.81)) )
    {
        if(createPerinatalTable() && migratePerinatal())
            setDatabaseVersion(2.82);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.82)) )
    {
        if(createDevelopmentTable() && migrateDevelopment())
            setDatabaseVersion(2.83);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.83)) )
    {
        if(removePerinatalDevelopmentfromPatientsTable())
            setDatabaseVersion(2.84);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.84)) )
    {
        if(migrateObGyn())
            setDatabaseVersion(2.85);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.85)) )
    {
        if(removeObgynfromPatientsTable())
            setDatabaseVersion(2.86);
    }
    if ( dataHelper::doubleEqual(getDatabaseVersion(),double(2.86)) )
    {
        dropAllViews();
        createAllViews();
        setDatabaseVersion(2.87);
    }

}

bool sqlBase::setDatabaseVersion(double version)
{
    bool b=false;
    double currentVersion = getDatabaseVersion();
    //    mDebug() << "setDatabaseVersion" << currentVersion << version;
    if( !dataHelper::doubleEqual(currentVersion,version) )
        b =  queryExec(QString("UPDATE metadata SET version=%1 WHERE data='version'").arg(version));
    //    if(b)
    //        mDebug() << "Database version is set to : " << version;
    return b;
}

bool sqlBase::setFollowDate(int ID, QString visitDateTime, int followDate)
{
    QString query = QString("UPDATE visits SET followDate=%1 WHERE ID=%2 AND visitDateTime='%3'")
            .arg(followDate)
            .arg(ID)
            .arg(visitDateTime);
    return queryExec(query);
}

sqlBase::development sqlBase::getDevelopment(int id)
{
    development develop;
    develop.clear();
    develop.ID = id;
    query->clear();
    bool q = query->exec(QString("SELECT * FROM development WHERE ID=%1").arg(id));
    if (!q)
    {
        mDebug() << "Failed to load Development" << query->lastError().text();
    }

    while (query->next())
    {
        develop.devHead = query->value(1).toBool();
        develop.devStand = query->value(2).toBool();
        develop.devSit = query->value(3).toBool();
        develop.devWalk = query->value(4).toBool();
        develop.devCrawl = query->value(5).toBool();
        develop.devTeeth = query->value(6).toBool();
        develop.devMother = query->value(7).toBool();
        develop.devlight = query->value(8).toBool();
        develop.devSmile = query->value(9).toBool();
        develop.devSpeech = query->value(10).toBool();
        develop.devSound = query->value(11).toBool();
    }
    query->finish();
    return develop;
}

bool sqlBase::saveDevelopment(development develop)
{

    query->clear();
    if ( !isDevelopmentRowExists(develop.ID))
    {
        if ( !queryExec(QString("INSERT INTO development (ID) VALUES (%1)").arg(develop.ID)))
            return false;
    }

    QString q = QString("UPDATE development SET "
                        "ID=:ID,"
                        "devHead=:devHead,"
                        "devStand=:devStand,"
                        "devSit=:devSit,"
                        "devWalk=:devWalk,"
                        "devCrawl=:devCrawl,"
                        "devTeeth=:devTeeth,"
                        "devMother=:devMother,"
                        "devlight=:devlight,"
                        "devSmile=:devSmile,"
                        "devSpeech=:devSpeech,"
                        "devSound=:devSound"
                        " WHERE ID=%1").arg(develop.ID);

    query->prepare(q);
    query->bindValue(":ID",develop.ID);
    query->bindValue(":devHead",develop.devHead);
    query->bindValue(":devStand",develop.devStand);
    query->bindValue(":devSit",develop.devSit);
    query->bindValue(":devWalk",develop.devWalk);
    query->bindValue(":devCrawl",develop.devCrawl);
    query->bindValue(":devTeeth",develop.devTeeth);
    query->bindValue(":devMother",develop.devMother);
    query->bindValue(":devlight",develop.devlight);
    query->bindValue(":devSmile",develop.devSmile);
    query->bindValue(":devSpeech",develop.devSpeech);
    query->bindValue(":devSound",develop.devSound);
    bool b = query->exec();
    if (!b)
        mDebug() << "ERROR SAVING DEVELOPMENT" << query->lastError().text();

    query->finish();
    return b;
}

bool sqlBase::savePerinatal(sqlBase::perinatal pnatal)
{
    query->clear();
    if ( !isPerinatalRowExists(pnatal.ID))
    {
        if ( !queryExec(QString("INSERT INTO perinatal (ID) VALUES (%1)").arg(pnatal.ID)))
            return false;
    }

    QString q = QString("UPDATE perinatal SET "
                        "ID=:ID,"
                        "pregLine=:pregLine,"
                        "laborLine=:laborLine,"
                        "NICULine=:NICULine,"
                        "dietLine=:dietLine,"
                        "GALine=:GALine,"
                        "GLine=:GLine,"
                        "PLine=:PLine,"
                        "LLine=:LLine"
                        " WHERE ID=%1").arg(pnatal.ID);

    query->prepare(q);
    query->bindValue(":ID",pnatal.ID);
    query->bindValue(":pregLine",pnatal.pregLine);
    query->bindValue(":laborLine",pnatal.laborLine);
    query->bindValue(":NICULine",pnatal.NICULine);
    query->bindValue(":dietLine",pnatal.dietLine);
    query->bindValue(":GALine",pnatal.GALine);
    query->bindValue(":GLine",pnatal.GLine);
    query->bindValue(":PLine",pnatal.PLine);
    query->bindValue(":LLine",pnatal.LLine);
    bool b = query->exec();
    if (!b)
        mDebug() << "ERROR SAVING PERINATAL" << query->lastError().text();

    query->finish();
    return b;
}

sqlBase::perinatal sqlBase::getPerinatal(int id)
{
    perinatal pnatal;
    pnatal.clear();
    pnatal.ID = id;
    query->clear();
    bool q = query->exec(QString("SELECT * FROM perinatal WHERE ID=%1").arg(id));
    if (!q)
    {
        mDebug() << "Failed to load Perinatal" << query->lastError().text();
    }

    while (query->next())
    {
        pnatal.pregLine = query->value(1).toString();
        pnatal.laborLine = query->value(2).toString();
        pnatal.NICULine = query->value(3).toString();
        pnatal.dietLine = query->value(4).toString();
        pnatal.GALine = query->value(5).toString();
        pnatal.GLine = query->value(6).toString();
        pnatal.PLine = query->value(7).toString();
        pnatal.LLine = query->value(8).toString();
    }
    query->finish();
    return pnatal;
}

bool sqlBase::saveObGyn(sqlBase::obGyn og)
{
    query->clear();
    if ( !isObGynRowExists(og.ID))
    {
        if ( !queryExec(QString("INSERT INTO obgyn (ID) VALUES (%1)").arg(og.ID)))
            return false;
    }

    QString q = QString("UPDATE obgyn SET "
                        "ID=:ID,"
                        "husband=:husband,"
                        "GPA=:GPA,"
                        "menarche=:menarche,"
                        "menoPause=:menoPause,"
                        "lastFor=:lastFor,"
                        "every=:every,"
                        "cycle=:cycle,"
                        "LMP=:LMP,"
                        "FPAL=:FPAL,"
                        "cyclePain=:cyclePain"
                        " WHERE ID=%1").arg(og.ID);

    query->prepare(q);
    query->bindValue(":ID",og.ID);
    query->bindValue(":husband",og.husband);
    query->bindValue(":GPA",og.GPA);
    query->bindValue(":menarche",og.menarche);
    query->bindValue(":menoPause",og.menoPause);
    query->bindValue(":lastFor",og.lastFor);
    query->bindValue(":every",og.every);
    query->bindValue(":cycle",og.cycle);
    query->bindValue(":LMP",og.LMP);
    query->bindValue(":FPAL",og.FPAL);
    query->bindValue(":cyclePain",og.cyclePain);
    bool b = query->exec();
    if (!b)
        mDebug() << "ERROR SAVING OBGYN" << query->lastError().text();



    query->finish();
    return b;
}

sqlBase::obGyn sqlBase::getObGyn(int id)
{
    obGyn obg;
    obg.clear();
    obg.ID = id;
    query->clear();
    bool q = query->exec(QString("SELECT * FROM obgyn WHERE ID=%1").arg(id));
    if (!q)
    {
        mDebug() << "Failed to load OBGYN" << query->lastError().text();
    }

    while (query->next())
    {
        obg.husband = query->value(1).toString();
        obg.GPA = query->value(2).toString();
        obg.menarche = query->value(3).toString();
        obg.menoPause = query->value(4).toBool();
        obg.lastFor = query->value(5).toString();
        obg.every = query->value(6).toString();
        obg.cycle = query->value(7).toInt();
        obg.LMP = query->value(8).toInt();
        obg.FPAL = query->value(9).toString();
        obg.cyclePain = query->value(10).toBool();
    }
    query->finish();
    return obg;
}

double sqlBase::getDatabaseVersion()
{
    query->clear();
    double version= double(0);
    bool b =  query->exec("SELECT version FROM metadata WHERE data='version'");
    if (!b)
    {
        mDebug() << "Failed to get metadata version";
    }

    while(query->next())
    {
        version = query->value(0).toDouble();
        //        mDebug() << "vesrions is : " << version;
    }
    if ( dataHelper::doubleEqual(version,0))
    {
        bool versionExisits =
                bool(sqlExec(QString("SELECT EXISTS(SELECT version FROM metadata WHERE data='version')")).toInt());

        if(versionExisits)
            queryExec(QString("UPDATE metadata SET version='%1' WHERE data='version'").arg(dbVersion));
        else
            queryExec(QString("INSERT INTO metadata (data,version) VALUES ('version',%1)").arg(dbVersion));

        version = static_cast<double>(dbVersion);
    }
    query->finish();
    return version;
}

int sqlBase::getConditionsStatus()
{
    query->clear();
    int status=0;
    bool b =  query->exec("SELECT version FROM metadata WHERE data='conditions'");
    if (!b)
    {
        mDebug() << "Failed to get conditions status";
    }
    while(query->next())
    {
        status = query->value(0).toInt();
    }
    query->finish();
    return status;
}

QList<sqlBase::temp> sqlBase::getMigrateList()
{
    sqlBase::temp _t;
    QList<sqlBase::temp> list;
    query->clear();
    bool b = query->exec("SELECT ID,visitJulianDate,visitTime,visitType FROM visits");
    if (!b)
        mDebug() << "error migarting 1" << query->lastError().text();
    while(query->next())
    {
        _t.ID = query->value(0).toInt();
        _t.date = query->value(1).toInt();
        _t.time = query->value(2).toInt();
        _t.vType = query->value(3).toInt();
        list.append(_t);
        //mDebug() << list.length();
    }

    query->finish();
    return list;
}

//bool sqlBase::migratePrices()
//{
//    QList<sqlBase::temp> list = getMigrateList();
//    bool b = false;
//    double p=0;
//    query->clear();

//    QSettings *settings = new QSettings("settings.ini",QSettings::IniFormat);
//    double nv = settings->value("newVisitPrice").toDouble();
//    double f1 = settings->value("followVisitprice1").toDouble();
//    double f2 = settings->value("followVisitprice2").toDouble();
//    double f3 = settings->value("followVisitprice3").toDouble();
//    double f4 = settings->value("followVisitprice4").toDouble();
//    delete settings;

//    db.transaction();

//    foreach (sqlBase::temp _t, list)
//    {
//        switch(_t.vType)
//        {
//        case 0:
//            p = nv;
//            break;
//        case 1:
//            p = f1;
//            break;
//        case 2:
//            p = f2;
//            break;
//        case 3:
//            p = f3;
//            break;
//        case 4:
//            p = f4;
//            break;
//        }

//        b = query->exec(QString("INSERT INTO visitPrices (ID,visitDate,visitTime,price) VALUES (%1,%2,%3,%4)")
//                        .arg(_t.ID)
//                        .arg(_t.date)
//                        .arg(_t.time)
//                        .arg(p));
//        if (!b)
//            mDebug() << "error migarting 2" << query->lastError().text();
//    }


//    QStringList serviceList = sqlextra->getPaidServicesList();

//    foreach (QString service, serviceList)
//    {
//        query->exec(QString("update investigations set PRICE=%1 WHERE NAME=\"%2\"")
//                    .arg(sqlextra->getPaidServicePrice(service))
//                    .arg(service));
//    }

//    db.commit();
//    query->finish();
//    return b;
//}

bool sqlBase::migrateConditions()
{
    bool b = false;
    query->clear();
    db.transaction();

    int indexLength = getPatientIndexLength();
    mPatient p;

    for(int i=1;i<indexLength;i++)
    {
        p = getmPatientData(i);
        t_conditions condition;
        condition.anemia = int(dataHelper::str2bool(p.anemia));
        condition.AnemiaPregnancy = int(dataHelper::str2bool(p.AnemiaPregnancy));
        condition.bilharziasis = int(dataHelper::str2bool(p.bilharziasis));
        condition.bloodTransfusion = int(dataHelper::str2bool(p.bloodTransfusion));
        condition.bronchialAsthma = int(dataHelper::str2bool(p.bronchialAsthma));
        condition.CHOLECYSTITIS = int(dataHelper::str2bool(p.CHOLECYSTITIS));
        condition.chronicKidenyInjury = int(dataHelper::str2bool(p.chronicKidenyInjury));
        condition.chronicLiverDisease = int(dataHelper::str2bool(p.chronicLiverDisease));
        condition.chronicObstructivePulmonaryDisease = int(dataHelper::str2bool(p.chronicObstructivePulmonaryDisease));
        condition.congestiveHeartFailure = int(dataHelper::str2bool(p.congestiveHeartFailure));
        condition.coronaryArteryDisease = int(dataHelper::str2bool(p.coronaryArteryDisease));
        condition.CVS = int(dataHelper::str2bool(p.CVS));
        condition.diabetes = int(dataHelper::str2bool(p.diabetes));
        condition.DMePregnancy = int(dataHelper::str2bool(p.DMePregnancy));
        condition.DVT = int(dataHelper::str2bool(p.DVT));
        condition.HTNePregnancy = int(dataHelper::str2bool(p.HTNePregnancy));
        condition.hyperlipidemia = int(dataHelper::str2bool(p.hyperlipidemia));
        condition.hypertension = int(dataHelper::str2bool(p.hypertension));
        condition.hyperuricemia = int(dataHelper::str2bool(p.hyperuricemia));
        condition.IBS = int(dataHelper::str2bool(p.IBS));
        condition.infertility = int(dataHelper::str2bool(p.infertility));
        condition.MI = int(dataHelper::str2bool(p.MI));
        condition.NasalAllergy = int(dataHelper::str2bool(p.NasalAllergy));
        condition.OSTEOARTHERITIS = int(dataHelper::str2bool(p.OSTEOARTHERITIS));
        condition.pepticUlcer = int(dataHelper::str2bool(p.pepticUlcer));
        condition.PERIPHERALNEUROPATHY = int(dataHelper::str2bool(p.PERIPHERALNEUROPATHY));
        condition.peripheralVascularDisease = int(dataHelper::str2bool(p.peripheralVascularDisease));
        condition.RheumaticFever = int(dataHelper::str2bool(p.RheumaticFever));
        condition.tuberculosis = int(dataHelper::str2bool(p.tuberculosis));
        condition.varicoseVeins = int(dataHelper::str2bool(p.varicoseVeins));

        QString query = QString("INSERT INTO conditions_patients "
                                "(ID,"
                                "c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,"
                                "c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,"
                                "c21,c22,c23,c24,c25,c26,c27,c28,c29"
                                ") "
                                "VALUES "
                                "(%31,"
                                "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,"
                                "%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,"
                                "%21,%22,%23,%24,%25,%26,%27,%28,%29,%30)")
                .arg(condition.DMePregnancy)
                .arg(condition.diabetes)
                .arg(condition.coronaryArteryDisease)
                .arg(condition.tuberculosis)
                .arg(condition.bronchialAsthma)
                .arg(condition.HTNePregnancy)
                .arg(condition.hypertension)
                .arg(condition.congestiveHeartFailure)
                .arg(condition.bilharziasis)
                .arg(condition.chronicObstructivePulmonaryDisease)
                .arg(condition.AnemiaPregnancy)
                .arg(condition.anemia)
                .arg(condition.chronicKidenyInjury)
                .arg(condition.hyperuricemia)
                .arg(condition.pepticUlcer)
                .arg(condition.RheumaticFever)
                .arg(condition.peripheralVascularDisease)
                .arg(condition.chronicLiverDisease)
                .arg(condition.hyperlipidemia)
                .arg(condition.CVS)
                .arg(condition.infertility)
                .arg(condition.bloodTransfusion)
                .arg(condition.varicoseVeins)
                .arg(condition.IBS)
                .arg(condition.MI)
                .arg(condition.DVT)
                .arg(condition.NasalAllergy)
                .arg(condition.CHOLECYSTITIS)
                .arg(condition.OSTEOARTHERITIS)
                .arg(condition.PERIPHERALNEUROPATHY)
                .arg(i);

        queryExec(query);
    }


    QString createNeoPatientTableQuery =
            QString("CREATE TABLE IF NOT EXISTS neo_patients"
                    "("
                    "ID  INTEGER PRIMARY KEY,"
                    "Name    varchar,"
                    "dateTime    varchar,"
                    "Age varchar,"
                    "Gender	varchar,"
                    "Residence	varchar,"
                    "maritalStatus	varchar,"
                    "birthPlace	varchar,"
                    "occupation	varchar,"
                    "smoker	varchar,"
                    "cigarretsPerDay	varchar,"
                    "smokingYears	varchar,"
                    "mobile	varchar,"
                    "alcohol varchar,"
                    "pastHistory	varchar,"
                    "familyHistory	varchar,"
                    "notes	varchar,"
                    "allergy	varchar,"
                    "operations	varchar,"
                    "devHead  varchar,"
                    "devStand      varchar,"
                    "devSit      varchar,"
                    "devWalk      varchar,"
                    "devCrawl      varchar,"
                    "devTeeth      varchar,"
                    "devMother      varchar,"
                    "devlight      varchar,"
                    "devSmile      varchar,"
                    "devSpeech      varchar,"
                    "devSound      varchar,"
                    "pregLine  varchar,"
                    "laborLine  varchar,"
                    "NICULine  varchar,"
                    "dietLine  varchar,"
                    "GALine  varchar,"
                    "GLine  varchar,"
                    "PLine  varchar,"
                    "LLine  varchar,"
                    "ABO integer,"
                    "husband  varchar,"
                    "GPA  varchar,"
                    "menarche  varchar,"
                    "menoPause  varchar,"
                    "lastFor  varchar,"
                    "every  varchar,"
                    "cycle integer,"
                    "LMP  integer,"
                    "FPAL varchar,"
                    "cyclePain integer"
                    ")");
    if (queryExec(createNeoPatientTableQuery))
    {
        // copy old data

        QString copyQuery = QString("INSERT INTO neo_patients SELECT "
                                    "ID,Name,dateTime,Age,Gender,Residence,maritalStatus,"
                                    "birthPlace,occupation,smoker,cigarretsPerDay,smokingYears,"
                                    "mobile,alcohol,pastHistory,familyHistory,notes,allergy,"
                                    "operations,devHead,devStand,devSit,devWalk,devCrawl,devTeeth,"
                                    "devMother,devlight,devSmile,devSpeech,devSound,pregLine,laborLine,"
                                    "NICULine,dietLine,GALine,GLine,PLine,LLine,ABO,husband,GPA,menarche,"
                                    "menoPause,lastFor,every,cycle,LMP,FPAL,cyclePain FROM patients");
        queryExec(copyQuery);
        dropAllViews();
        queryExec("DROP TABLE IF EXISTS patients;");
        queryExec("ALTER TABLE neo_patients RENAME TO patients;");
        createAllViews();
    }
    else
    {
        db.rollback();
        return false;
    }

    db.commit();
    query->finish();
    return b;
}

bool sqlBase::migrateSmoking()
{
    QPair<int,int> pair;
    QList<QPair<int,int> > list;
    query->clear();

    bool x = query->exec("select id,smokingYears from patients");
    if(!x)
    {
        mDebug() << query->lastError().text();
        return false;
    }
    while (query->next())
    {
        pair.first = query->value(0).toInt();
        pair.second = query->value(1).toInt();
        list << pair;

    }
    query->finish();
    bool z=false;
    int thisYear = QDate::currentDate().year();


    foreach (pair, list)
    {
        z = queryExec(QString("update patients set smokingYears=%1 where id=%2")
                      .arg((pair.second==0)? 0: int(thisYear - pair.second))
                      .arg( pair.first));
        //        mDebug() << pair.first << pair.second;
        if(!z)
            return false;
    }
    mDebug() << "Database updated to V 2.81";
    return true;
}

bool sqlBase::migratePerinatal()
{
    mDebug() << "Database updated to V 2.82";
    return queryExec("INSERT INTO perinatal SELECT ID,pregLine,laborLine,NICULine,dietLine,GALine,GLine,PLine,LLine from patients");
}

bool sqlBase::migrateDevelopment()
{
    mDebug() << "Database updated to V 2.83";
    return queryExec("INSERT INTO development SELECT ID,devHead,devStand,devSit,devWalk,devCrawl,devTeeth,devMother,devlight,devSmile,devSpeech,devSound from patients");
}

bool sqlBase::migrateObGyn()
{
    mDebug() << "Database updated to V 2.85";
    return queryExec("INSERT INTO obgyn SELECT ID,husband,GPA,menarche,menoPause,lastFor,every,cycle,LMP,FPAL,cyclePain from patients");
}

bool sqlBase::removePerinatalDevelopmentfromPatientsTable()
{
    db.transaction();
    QString createNeoPatientTableQuery =
            QString("CREATE TABLE IF NOT EXISTS neo_patients"
                    "("
                    "ID  INTEGER PRIMARY KEY,"
                    "Name    varchar,"
                    "dateTime    varchar,"
                    "Age varchar,"
                    "Gender	varchar,"
                    "Residence	varchar,"
                    "maritalStatus	varchar,"
                    "birthPlace	varchar,"
                    "occupation	varchar,"
                    "smoker	varchar,"
                    "cigarretsPerDay	varchar,"
                    "smokingYears	varchar,"
                    "mobile	varchar,"
                    "alcohol varchar,"
                    "pastHistory	varchar,"
                    "familyHistory	varchar,"
                    "notes	varchar,"
                    "allergy	varchar,"
                    "operations	varchar,"
                    "ABO integer,"
                    "husband  varchar,"
                    "GPA  varchar,"
                    "menarche  varchar,"
                    "menoPause  varchar,"
                    "lastFor  varchar,"
                    "every  varchar,"
                    "cycle integer,"
                    "LMP  integer,"
                    "FPAL varchar,"
                    "cyclePain integer"
                    ")");
    if (queryExec(createNeoPatientTableQuery))
    {
        QString copyQuery = QString("INSERT INTO neo_patients SELECT "
                                    "ID,Name,dateTime,Age,Gender,Residence,maritalStatus,"
                                    "birthPlace,occupation,smoker,cigarretsPerDay,smokingYears,"
                                    "mobile,alcohol,pastHistory,familyHistory,notes,allergy,"
                                    "operations,ABO,husband,GPA,menarche,"
                                    "menoPause,lastFor,every,cycle,LMP,FPAL,cyclePain FROM patients");
        queryExec(copyQuery);
        dropAllViews();
        queryExec("DROP TABLE IF EXISTS patients;");
        queryExec("ALTER TABLE neo_patients RENAME TO patients;");
        createAllViews();
        db.commit();
        mDebug() << "Database updated to V 2.84";
        return true;
    }

    db.rollback();
    db.commit();
    return false;



}

bool sqlBase::removeObgynfromPatientsTable()
{
    db.transaction();
    QString createNeoPatientTableQuery =
            QString("CREATE TABLE IF NOT EXISTS neo_patients"
                    "("
                    "ID  INTEGER PRIMARY KEY,"
                    "Name    varchar,"
                    "dateTime    varchar,"
                    "Age varchar,"
                    "Gender	varchar,"
                    "Residence	varchar,"
                    "maritalStatus	varchar,"
                    "birthPlace	varchar,"
                    "occupation	varchar,"
                    "smoker	varchar,"
                    "cigarretsPerDay	varchar,"
                    "smokingYears	varchar,"
                    "mobile	varchar,"
                    "alcohol varchar,"
                    "pastHistory	varchar,"
                    "familyHistory	varchar,"
                    "notes	varchar,"
                    "allergy	varchar,"
                    "operations	varchar,"
                    "ABO integer"
                    ")");
    if (queryExec(createNeoPatientTableQuery))
    {
        QString copyQuery = QString("INSERT INTO neo_patients SELECT "
                                    "ID,Name,dateTime,Age,Gender,Residence,maritalStatus,"
                                    "birthPlace,occupation,smoker,cigarretsPerDay,smokingYears,"
                                    "mobile,alcohol,pastHistory,familyHistory,notes,allergy,"
                                    "operations,ABO FROM patients");
        queryExec(copyQuery);
        dropAllViews();
        queryExec("DROP TABLE IF EXISTS patients;");
        queryExec("ALTER TABLE neo_patients RENAME TO patients;");
        createAllViews();
        db.commit();
        mDebug() << "Database updated to V 2.86";
        return true;
    }

    db.rollback();
    db.commit();
    return false;
}

QString sqlBase::getDecryptedName(QString rawName)
{
    return crypto.decryptToString(rawName);
}

QString sqlBase::getEncryptedName(QString rawName)
{
    return crypto.encryptToString(rawName);
}

void sqlBase::encryptDecryptNames(bool enable)
{
    QString fromName,toName;
    for (int id =1;id< getPatientIndexLength();id++)
    {
        fromName = getPatientNamefromID(id);
        toName = enable? getEncryptedName(fromName):getDecryptedName(fromName);
        queryExec(QString("UPDATE patients SET Name='%1' WHERE ID=%2;").arg(toName).arg(id));
        qApp->processEvents();
    }

}

QString sqlBase::getHumanizedName(QString rawName)
{
    return encryptionEnabled? getDecryptedName(rawName):rawName;
}

QString sqlBase::getComputerizedName(QString rawName)
{
    return encryptionEnabled? getEncryptedName(rawName):rawName;
}

QString sqlBase::getPatientTooltip(const sqlBase::patientInfo &info)
{
    return QString("<table>"
                   "<tr>"
                   "<td>Name</td><td>:</td><td><div align=\"left\">%1</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Age</td><td>:</td><td><div align=\"left\">%2</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Gender</td><td>:</td><td><div align=\"left\">%3</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Residence</td><td>:</td><td><div align=\"left\">%4</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Marital Status</td><td>:</td><td><div align=\"left\">%5</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Occupation</td><td>:</td><td><div align=\"left\">%6</div><\td>"
                   "</tr>"
                   "<tr>"
                   "<td>Mobile</td><td>:</td><td><div align=\"left\">%7</div><\td>"
                   "</tr>"
                   "</table>")
            .arg(info.Name)
            .arg(info.Age)
            .arg(info.Gender)
            .arg(info.Residence)
            .arg(info.MaritalStatus)
            .arg(info.Occupation)
            .arg(info.Mobile);
}

void sqlBase::dropAllViews()
{
    queryExec("DROP VIEW IF EXISTS agendaView;");
    queryExec("DROP VIEW IF EXISTS registerView;");
    queryExec("DROP VIEW IF EXISTS EddView;");
}

void sqlBase::createAllViews()
{
    createAgendaView();
    createMyRegisterView();
    createEddView();
}

int sqlBase::getVisitType(int ID,int visitJulianDate)
{
    QString sqlCmd = QString("SELECT visitType FROM agendaView where ID=%1 AND followDate=%2;")
            .arg(ID)
            .arg(visitJulianDate);

    int eVisitType = sqlExec(sqlCmd).toInt();

    if (eVisitType < settings.getMaxFollowUpsPerProblem()+1 )
        eVisitType +=1;

    return eVisitType;
}

QList<QBrush> sqlBase::getVisitColors()
{
    QList<QBrush> brushes;

    brushes.append(QBrush(QColor::fromRgb(204,229,255)));
    brushes.append(QBrush(QColor::fromRgb(255,255,204)));
    brushes.append(QBrush(QColor::fromRgb(229,255,204)));
    brushes.append(QBrush(QColor::fromRgb(204,255,204)));
    brushes.append(QBrush(QColor::fromRgb(204,255,229)));
    brushes.append(QBrush(QColor::fromRgb(255,255,255)));
    return brushes;
}

QString sqlBase::getAge(int julianDays,bool printable)
{
    int speciality = settings.userSpeciality();
    QString Age;
    if ( speciality == dataHelper::Speciality::Paediatrics ||
         speciality == dataHelper::Speciality::FamilyMedicine )
        Age = dataHelper::julianToAge(julianDays,printable?
                                          dataHelper::AgeStyle::compact:dataHelper::AgeStyle::expanded);
    else
        Age = dataHelper::julianToAge(julianDays);
    return Age;

}

void sqlBase::agendaAttendedLoader(int julianDate,QStandardItemModel *agendaModel,double &percent)
{
    QLocale en_US = QLocale(QLocale::English,QLocale::UnitedStates);
    int ID;
    QStandardItemModel *m = agendaModel;
    int rows = m->rowCount();

    QList<QBrush> brushes = getVisitColors();

    int _attended = 0;
    percent = 00.00;

    for ( int r=0;r<rows;r++){
        ID = m->data(m->index(r,0)).toInt();

        if(ID < 1)
            continue;

        Attended attended = isFollowVisitAttended(ID,julianDate);
        //qApp->processEvents();
        if ( attended.state){
            m->item(r,2)->setCheckState(Qt::CheckState(Qt::Checked));
            m->item(r,2)->setText(en_US.toString(attended.time,"hh:mm AP"));
            _attended +=1;
            for (int c=0 ; c < m->columnCount(); c++) {
                m->item(r,c)->setBackground(brushes.at(attended.visitType));
                //qApp->processEvents();
            }
        }else {
            attended.visitType = getVisitType(ID,julianDate);
            for (int c=0 ; c < m->columnCount(); c++) {
                m->item(r,c)->setBackground(( attended.visitType ==1
                                              && julianDate < QDate::currentDate().toJulianDay() )?
                                                QBrush(QColor::fromRgb(255,204,255)):brushes.at(attended.visitType));
                //qApp->processEvents();
            }
        }

        m->item(r,2)->setToolTip(dataHelper::getVisitType(attended.visitType,settings));
        //qApp->processEvents();
    }

    double _total = static_cast<double>(m->rowCount());
    if(_total > 0)
        percent = static_cast<double>(_attended / _total) * 100;
}

QStandardItemModel *sqlBase::getMyRegisterCalcModel(QStandardItemModel *myRegisterModel,
                                                    QStandardItemModel *calcModel,
                                                    sqlExtra *sqlextra,
                                                    const QModelIndexList &selection,
                                                    double &TOTAL)
{
    calcModel->clear();
    int maxFollowsPerProblem = settings.getMaxFollowUpsPerProblem();
    QStringList services = sqlextra->getPaidServicesList();
    int startCol = 6;
    int endCol = startCol + services.count();

    QList<int> selectedRows;

    if(selection.size() == 0)
        for (int i = 0; i < myRegisterModel->rowCount(); i++)
            selectedRows << i;
    else
        for (int i = 0; i < selection.size(); i++)
            selectedRows << selection[i].row();


    int count;
    QString service;
    double subTOTAL=0;
    QString visitType;

    int newVisitCOUNT = 0;
    int follow1VisitCOUNT = 0;
    int follow2VisitCOUNT = 0;
    int follow3VisitCOUNT = 0;
    int follow4VisitCOUNT = 0;
    int freeVisitCOUNT=0;

    double subTotalNewVisits = 0;
    double subTotalFollow1Visits = 0;
    double subTotalFollow2Visits = 0;
    double subTotalFollow3Visits = 0;
    double subTotalFollow4Visits = 0;
    double subTotalFree = 0;

    foreach (int currentRow, selectedRows)
    {
        visitType = myRegisterModel->index(currentRow,4).data().toString();
        if (visitType == "New Visit")
        {
            newVisitCOUNT+=1;
            subTotalNewVisits += myRegisterModel->index(currentRow,5).data().toDouble();
        }
        else if (visitType == "Follow Up1")
        {
            follow1VisitCOUNT+=1;
            subTotalFollow1Visits += myRegisterModel->index(currentRow,5).data().toDouble();
        }
        else if (visitType == "Follow Up2")
        {
            follow2VisitCOUNT+=1;
            subTotalFollow2Visits += myRegisterModel->index(currentRow,5).data().toDouble();
        }
        else if (visitType == "Follow Up3")
        {
            follow3VisitCOUNT+=1;
            subTotalFollow3Visits += myRegisterModel->index(currentRow,5).data().toDouble();
        }
        else if (visitType == "Follow Up4")
        {
            follow4VisitCOUNT+=1;
            subTotalFollow4Visits += myRegisterModel->index(currentRow,5).data().toDouble();
        }
        else if (visitType == "Free")
        {
            freeVisitCOUNT+=1;
            subTotalFree = 0;
        }
        qApp->processEvents();
    }

    if (newVisitCOUNT > 0)
    {
        QStandardItem *newItem = new QStandardItem("New Visit");
        newItem->setBackground(getVisitColors().at(0));
        QStandardItem *newCOUNT = new QStandardItem(QString::number(newVisitCOUNT));
        newCOUNT->setBackground(getVisitColors().at(0));
        newCOUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        QStandardItem *newSUBTOTAL = new QStandardItem(QString::number(subTotalNewVisits));
        newSUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        newSUBTOTAL->setBackground(getVisitColors().at(0));
        calcModel->appendRow(QList<QStandardItem*>() << newItem << newCOUNT << newSUBTOTAL);
    }

    if (follow1VisitCOUNT > 0 )
    {
        QStandardItem *followItem1 = new QStandardItem("Follow Up1");
        followItem1->setBackground(getVisitColors().at(1));
        QStandardItem *follow1COUNT = new QStandardItem(QString::number(follow1VisitCOUNT));
        follow1COUNT->setBackground(getVisitColors().at(1));
        follow1COUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        QStandardItem *follow1SUBTOTAL = new QStandardItem(QString::number(subTotalFollow1Visits));
        follow1SUBTOTAL->setBackground(getVisitColors().at(1));
        follow1SUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        calcModel->appendRow(QList<QStandardItem*>() << followItem1 << follow1COUNT << follow1SUBTOTAL );
    }


    if (maxFollowsPerProblem > 1 && follow2VisitCOUNT > 0 )
    {
        QStandardItem *followItem2 = new QStandardItem("Follow Up2");
        followItem2->setBackground(getVisitColors().at(2));
        QStandardItem *follow2COUNT = new QStandardItem(QString::number(follow2VisitCOUNT));
        follow2COUNT->setBackground(getVisitColors().at(2));
        follow2COUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        QStandardItem *follow2SUBTOTAL = new QStandardItem(QString::number(subTotalFollow2Visits));
        follow2SUBTOTAL->setBackground(getVisitColors().at(2));
        follow2SUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        calcModel->appendRow(QList<QStandardItem*>() << followItem2 << follow2COUNT << follow2SUBTOTAL );
    }

    if (maxFollowsPerProblem > 2 && follow3VisitCOUNT > 0 )
    {
        QStandardItem *followItem3 = new QStandardItem("Follow Up3");
        followItem3->setBackground(getVisitColors().at(3));
        QStandardItem *follow3COUNT = new QStandardItem(QString::number(follow3VisitCOUNT));
        follow3COUNT->setBackground(getVisitColors().at(3));
        follow3COUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        QStandardItem *follow3SUBTOTAL = new QStandardItem(QString::number(subTotalFollow3Visits));
        follow3SUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        follow3SUBTOTAL->setBackground(getVisitColors().at(3));
        calcModel->appendRow(QList<QStandardItem*>() << followItem3 << follow3COUNT << follow3SUBTOTAL );
    }

    if (maxFollowsPerProblem > 3 && follow4VisitCOUNT > 0 )
    {
        QStandardItem *followItem4 = new QStandardItem("Follow Up4");
        followItem4->setBackground(getVisitColors().at(4));
        QStandardItem *follow4COUNT = new QStandardItem(QString::number(follow4VisitCOUNT));
        follow4COUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        follow4COUNT->setBackground(getVisitColors().at(4));
        QStandardItem *follow4SUBTOTAL = new QStandardItem(QString::number(subTotalFollow4Visits));
        follow4SUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        follow4SUBTOTAL->setBackground(getVisitColors().at(4));
        calcModel->appendRow(QList<QStandardItem*>() << followItem4 << follow4COUNT << follow4SUBTOTAL );
    }

    if (freeVisitCOUNT > 0)
    {
        QStandardItem *freeItem = new QStandardItem("Free");
        freeItem->setBackground(getVisitColors().at(5));
        QStandardItem *freeCOUNT = new QStandardItem(QString::number(freeVisitCOUNT));
        freeCOUNT->setBackground(getVisitColors().at(5));
        freeCOUNT->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        QStandardItem *freeSUBTOTAL = new QStandardItem(QString::number(subTotalFree));
        freeSUBTOTAL->setBackground(getVisitColors().at(5));
        freeSUBTOTAL->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
        calcModel->appendRow(QList<QStandardItem*>() << freeItem << freeCOUNT << freeSUBTOTAL );
    }

    TOTAL = static_cast<double>(subTotalNewVisits + subTotalFollow1Visits + subTotalFollow2Visits + subTotalFollow3Visits + subTotalFollow4Visits +subTotalFree);
    for ( int c=startCol; c<endCol;c++)
    {
        count = 0;
        subTOTAL = 0;
        service = services.at(c-6);
        foreach (int r, selectedRows)
        {
            count += myRegisterModel->index(r,c).data(Qt::CheckStateRole).toInt()/2;
            subTOTAL += myRegisterModel->index(r,c).data(Qt::DisplayRole).toDouble();
        }
        //subTOTAL = count*sqlextra->getPaidServicePrice(service);

        if ( count > 0 )
        {
            QStandardItem *itemService = new QStandardItem(service);
            itemService->setBackground(QBrush(QColor::fromRgb(255,204,255)));
            QStandardItem *itemCount = new QStandardItem(QString::number(count));
            itemCount->setBackground(QBrush(QColor::fromRgb(255,204,255)));
            itemCount->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
            QStandardItem *itemPrice = new QStandardItem(QString::number(subTOTAL));
            itemPrice->setBackground(QBrush(QColor::fromRgb(255,204,255)));
            itemPrice->setData(Qt::AlignCenter,Qt::TextAlignmentRole);
            calcModel->appendRow(QList<QStandardItem*>() << itemService << itemCount << itemPrice );
        }
        TOTAL+=subTOTAL;
    qApp->processEvents();
    }
    calcModel->setHorizontalHeaderLabels(QStringList() << "Service" << "Count" << "SUBTOTAL");
    return calcModel;
}

void sqlBase::registerServiceLoader(QStandardItemModel *myRegisterModel,sqlExtra *sqlextra)
{
    QStringList serviceList = sqlextra->getPaidServicesList();
    int columns = myRegisterModel->columnCount();
    int rows = myRegisterModel->rowCount();
    int date,ID;

    QString serviceName;
    ServiceState serviceState;

    for ( int x=6;x<columns;x++)
    {
        serviceName = serviceList.at(x-6);
        for ( int r=0;r<rows;r++)
        {
            date = myRegisterModel->data(myRegisterModel->index(r,3)).toInt();
            ID = myRegisterModel->data(myRegisterModel->index(r,0)).toInt();
            QStandardItem *item = myRegisterModel->item(r,x);
            item->setCheckable(false);
            serviceState = isServiceExistsInThisVisit(ID,date,serviceName);
            if (!dataHelper::doubleEqual(serviceState.price,0))
                item->setData(QVariant(serviceState.price),Qt::DisplayRole);
            item->setCheckState(Qt::CheckState((serviceState.state)? Qt::Checked:Qt::Unchecked));
        }
    }
}

void sqlBase::createNewVisit(int ID,
                             QString previous,
                             QDateTime datetime,
                             int visitType,
                             double visitPrice,
                             const QDate &lastSelectedFollowupDate,
                             DrugsItemModel *drugsModel,
                             InvestModel *investModel,
                             sqlExtra *sqlextra)
{
    QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
    QString englishDateTime = locale.toString(datetime, "dd/MM/yyyy hh:mm AP ddd");
    int nextDateJulian = static_cast<int>(datetime.date().toJulianDay());
    int previousDateJulian = static_cast<int>(locale.toDateTime(previous,"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());

    if (visitType ==0)
    {
        visit.clear();
        drugsModel->clear();
        investModel->clear();
    }
    else
    {
        visit = getPatientVisitData(ID,previous);
        drugsModel->blockSignals(true);
        investModel->blockSignals(true);
        drugsModel = readDrugs(ID,previousDateJulian,drugsModel);
        investModel = getInvestigationsModel(investModel,ID,previousDateJulian);
        drugsModel->blockSignals(false);
        investModel->blockSignals(false);

        visit.bp.clear();
        visit.pulse.clear();
        visit.temp.clear();
        visit.rr.clear();
        visit.headCir.clear();
        visit.weight.clear();
        visit.length.clear();

        int rows = investModel->rowCount();
        QStringList paidServices = sqlextra->getPaidServicesList();
        for ( int row = 0; row < rows ; row++)
        {
            if (paidServices.contains(investModel->item(row,1)->text()))
                investModel->item(row,6)->setText(QString::number(3));
        }
    }

    visit.ID = ID;
    visit.visitDateTime = englishDateTime;
    visit.followDate = QString::number(settings.isRemmberlastFollowupDate()? static_cast<int>(lastSelectedFollowupDate.toJulianDay()):nextDateJulian);
    visit.visitType = QString::number(visitType);

    visitData vdata;
    vdata.ID = ID;
    vdata.visit = visit;
    vdata.visitDate = nextDateJulian;
    vdata.visitDateTime = englishDateTime;
    vdata.visitPrice = visitPrice;
    vdata.drugsModel = drugsModel;
    vdata.invModel = investModel;
    saveVisitData(vdata);
    //    drugsLoaded = false;
    //    investigationLoaded = false;
}

QSqlTableModel *sqlBase::getConditionsModel(QSqlTableModel *conditionsModel)
{
    conditionsModel = new QSqlTableModel(this,db);
    conditionsModel->clear();
    conditionsModel->setTable("conditions");
    conditionsModel->setSort(0,Qt::AscendingOrder);
    conditionsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    conditionsModel->select();
    conditionsModel->setHeaderData(0,Qt::Horizontal,"_id");
    conditionsModel->setHeaderData(1,Qt::Horizontal,"state");
    conditionsModel->setHeaderData(2,Qt::Horizontal,"name");
    return conditionsModel;
}

bool sqlBase::addCondition(QString name, int _id)
{
    QString query1 = QString("INSERT INTO conditions (_id,state,name) VALUES (%1,%2,\"%3\");")
            .arg(_id).arg(1).arg(name);
    QString query2 = QString("ALTER TABLE conditions_patients ADD c%1").arg(_id);
    return ( queryExec(query1) && queryExec(query2) );
}

QList<QPair<int, QString> > sqlBase::getConditions()
{
    QPair<int, QString> pair;
    QList<QPair<int, QString> > list;

    bool q = query->exec("SELECT _id,name,state FROM conditions WHERE state=1");

    if (!q)
    {
        mDebug() << "Failed to get conditions";
    }
    while(query->next())
    {
        pair.first = query->value(0).toInt();
        pair.second = query->value(1).toString();
        list.append(pair);
    }
    query->finish();
    return list;
}

bool sqlBase::insertDefaultConditions()
{
    if ( getConditionsStatus() == static_cast<int>(conditionsVersion) )
        return true;

    QStringList f1 = QStringList() << "0"  << "1"  << "2"  << "3"  << "4"  <<
                                      "5"  << "6"  << "7"  << "8"  << "9"  <<
                                      "10" << "11" << "12" << "13" << "14" <<
                                      "15" << "16" << "17" << "18" << "19" <<
                                      "20" << "21" << "22" << "23" << "24" <<
                                      "25" << "26" << "27" << "28" << "29";

    QStringList f2 = QStringList() << "Diabetes e pregnancy" <<
                                      "Diabetes" <<
                                      "Coronary artery disease" <<
                                      "Tuberculosis" <<
                                      "Bronchial asthma" <<
                                      "Hypertension e pregnancy" <<
                                      "Hypertension" <<
                                      "CHF" <<
                                      "Bilharziasis" <<
                                      "COPD" <<
                                      "Anemia e pregnancy" <<
                                      "Anemia" <<
                                      "Chronic renal failure" <<
                                      "Hyperuricemia" <<
                                      "Peptic ulcer disease" <<
                                      "Rheurmatic fever" <<
                                      "Peripheral vascular disease" <<
                                      "Chronic liver disease" <<
                                      "Hyperlipidemia" <<
                                      "CVS" <<
                                      "Infirtility" <<
                                      "Blood transfusion" <<
                                      "Varicose veins" <<
                                      "Irritable bowl syndrome" <<
                                      "Myocardial infarction" <<
                                      "DVT" <<
                                      "Nasal allergy" <<
                                      "Cholecystitis" <<
                                      "Osteoartheritis" <<
                                      "Peripheral neuropathy" ;

    QString query;

    for ( int i =0 ; i < f1.count();i++)
    {
        query = QString("INSERT INTO conditions (_id,state,name) VALUES(%1,1,\"%2\")").arg(f1.at(i)).arg(f2.at(i));
        queryExec(query);
    }

    //set conditions metadata
    queryExec(QString("INSERT INTO metadata (data,version) VALUES(\"%1\",%2)").arg("conditions").arg(1));
    return true;
}

bool sqlBase::savePatientConditions(int ID,QList<QPair<QString, int> > list)
{
    QString query;
    QString _s;
    QPair<QString,int> p;

    if ( !isConditionRowExists(ID))
    {
        if ( !queryExec(QString("INSERT INTO conditions_patients (ID) VALUES (%1)").arg(ID)))
            return false;
    }

    foreach (p, list)
        _s.append(QString("%1=%2, ").arg(p.first).arg(p.second));

    query = QString("UPDATE conditions_patients SET %1 WHERE ID=%2").arg(_s.left(_s.lastIndexOf(","))).arg(ID);
    return queryExec(query);
}

QList<QPair<QString, int> > sqlBase::readPatientConditions(int ID)
{
    QList<QPair<QString, int> > list;
    QPair <QString, int> pair;
    list.clear();
    query->clear();
    bool q = query->exec(QString("SELECT * FROM conditions_patients WHERE ID=%1").arg(ID));
    if (!q)
    {
        mDebug() << "Failed to load patient conditions" << query->lastError().text();
    }

    QSqlTableModel conditionsModel;
    int cols = getConditionsModel(&conditionsModel)->rowCount();

    while (query->next())
    {
        for(int col = 1; col <= cols ; col++)
        {
            pair.first = QString("cb_%1").arg(col-1);
            pair.second = query->value(col).toInt();
            list.append(pair);
        }

    }
    query->finish();
    return list;
}


bool sqlBase::createPatientItemModel()
{
    if (patientTableModel == nullptr)
        delete patientTableModel;

    patientTableModel = new QStandardItemModel(this->parent());
    return true;
}

bool sqlBase::queryExec(QString sqlPhrase)
{
    query->clear();

    if (!query->exec(sqlPhrase))
    {
        mDebug() << sqlPhrase << query->lastError().text();
    }
    else
    {
        query->finish();
        return true;
    }
    query->finish();
    return false;
}

QStringList sqlBase::sqlExecList(QString sqlCmd, bool crypt)
{
    query->clear();
    QStringList list;
    QString item;
    if (!query->exec(sqlCmd))
    {
        mDebug() << sqlCmd << query->lastError().text();
    }

    while( query->next())
    {
        item = crypt? getHumanizedName(query->value(0).toString()):query->value(0).toString();
        list << item;
    }

    query->finish();
    return list;
}

QList<QPair<QString, QString> >sqlBase::sqlExecPair(QString sqlCmd)
{
    query->clear();
    QList<QPair<QString, QString> > list;
    QPair<QString,QString> pair;
    query->exec(sqlCmd);
    while (query->next())
    {
        pair.first = query->value(0).toString();
        pair.second = query->value(1).toString();
        list.append(pair);
    }
    query->finish();
    return list;
}

QString sqlBase::genericQuery(int ID, QString col, QString table)
{
    QString sqlPhrase = QString ("SELECT %1 FROM %2 WHERE ID=%3").arg(col).arg(table).arg(ID);

    return sqlExec(sqlPhrase);
}

bool sqlBase::haveSameNameWithDifferentID(int ID, QString name)
{
    encryptionEnabled=isEncryptionEnabled();
    QString sName;
    int sID;


    QString sqlPhrase = QString("SELECT ID,Name FROM patients");

    QList<QPair<QString,QString> > list = sqlExecPair(sqlPhrase);
    QPair<QString,QString> pair;

    foreach (pair, list)
    {
        sID = pair.first.toInt();
        sName = pair.second;

        if ( ( getHumanizedName(sName) == name ) && (sID != ID))
        {
            return true;
        }
    }
    return false;

}

bool sqlBase::haveSameNameWithSameID(int ID, QString name)
{
    encryptionEnabled=isEncryptionEnabled();
    QString sName;
    int sID;


    QString sqlPhrase = QString("SELECT ID,Name FROM patients");

    QList<QPair<QString,QString> > list = sqlExecPair(sqlPhrase);
    QPair<QString,QString> pair;

    foreach (pair, list)
    {
        sID = pair.first.toInt();
        sName = pair.second;

        if ( ( getHumanizedName(sName) == name ) && (sID == ID))
        {
            return true;
        }
    }
    return false;
}


QList<QPair<QString, QString> > sqlBase::getListVisitsType(int ID)
{
    QString sqlPhrase = QString("SELECT visitDateTime,visitType FROM visits WHERE ID=%1").arg(ID);
    return sqlExecPair(sqlPhrase);
}

InvestModel *sqlBase::getInvestigationsModel(InvestModel *investModel,int ID,int visitJulianDate)
{
    investModel->clear();
    QString selectInvestigationQuery;

    if ( visitJulianDate == 0 )
        selectInvestigationQuery = QString("SELECT * FROM investigations WHERE ID=%1 AND invState !=0 AND length(PATH) > 8").arg(ID);
    else
        selectInvestigationQuery = QString("SELECT * FROM investigations WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(visitJulianDate);

    query->clear();
    bool i = query->exec(selectInvestigationQuery);
    if ( !i )
    {
        mDebug() << "FAILED TO GET INVESTIGATIONS MODEL FOR ID:VISITDATE" << ID << ":" << visitJulianDate <<query->lastError().text();
    }
    QStringList paths;
    QString name;
    int row = 0;
    QString path;
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QStandardItem *IDItem, *nameItem, *visitDateItem, *pathItem,
            *invDateItem , *invTimeItem, *invStateItem,
            *priceItem, *resultsItem;


    while ( query->next())
    {
        IDItem =new QStandardItem(QString::number(ID));
        name = query->value(1).toString();
        path = query->value(3).toString();
        nameItem =new QStandardItem(name);
        //nameItem->setToolTip(invIconHelper::getInvestigationTooltip(path,name));
        visitDateItem =new QStandardItem(QString::number(query->value(2).toInt()));
        pathItem =new QStandardItem(query->value(3).toString());
        invDateItem =new QStandardItem();
        invTimeItem =new QStandardItem();
        invStateItem =new QStandardItem(QString::number(query->value(6).toInt()));
        priceItem =new QStandardItem(query->value(7).toString());
        resultsItem =new QStandardItem(query->value(8).toString());

        if ( visitJulianDate == 0 ) // for list not visitbox
        {
            invDateItem->setText(locale.toString(QDate::fromJulianDay(query->value(4).toInt()),"dd/MM/yyyy"));
            if ( ! paths.contains(query->value(3).toString()))
                paths << query->value(3).toString();
            else
                continue;
        }
        else
            invDateItem->setText(QString::number(query->value(4).toInt()));

        if ( visitJulianDate == 0 )
            invTimeItem->setText(locale.toString(QTime::fromMSecsSinceStartOfDay(query->value(5).toInt()*1000),"hh:mm AP"));
        else
            invTimeItem->setText(query->value(5).toString());

        investModel->setItem(row,0,IDItem);
        investModel->setItem(row,1,nameItem);
        investModel->setItem(row,2,visitDateItem);
        investModel->setItem(row,3,pathItem);
        investModel->setItem(row,4,invDateItem);
        investModel->setItem(row,5,invTimeItem);
        investModel->setItem(row,6,invStateItem);
        investModel->setItem(row,7,priceItem);
        investModel->setItem(row,8,resultsItem);
        row+=1;
    }
    query->finish();
    return investModel;
}

bool sqlBase::saveInvestigationsModel(int ID, int visitDate, InvestModel *model)
{
    int rows = model->rowCount();
    bool x = true;
    if ( rows == 0 )
    {
        return true;
    }
    int invDate, invState;
    double price;
    QString invName, invPath, invTime, invResults;

    bool d,e=false;

    query->clear();

    d = query->exec(QString("DELETE FROM investigations WHERE ID=%1 AND VISITDATE=%2").arg(ID).arg(visitDate));
    if ( !d )
    {
        mDebug() << "Failed to delete investigations" << query->lastError().text();

    }
    query->finish();

    for ( int row=0; row<rows; row++)
    {
        invName = model->item(row,1)->text();
        invPath = model->item(row,3)->text();
        invDate = model->item(row,4)->text().toInt();
        //invTime = QTime::fromString(model->item(row,5)->text(),"hh:mm AP").msecsSinceStartOfDay();
        invTime = model->item(row,5)->text();
        invState = model->item(row,6)->text().toInt();
        price = model->item(row,7)->text().toDouble();
        invResults = model->item(row,8)->text();

        e = addInvestigation(ID,visitDate,invName,invPath,invDate,invTime,invState,price,invResults);
        if (!e)
            x = e;
    }
    return x;
}

int sqlBase::getInvestigationsCount(int ID)
{
    query->clear();
    int size = 0 ;
    bool z = query->exec(QString("SELECT  invState from investigations WHERE ID=%1 AND length(PATH) > 8;").arg(ID));
    if ( !z )
    {
        mDebug() << "ERROR GETTING INVEST MEDIA SIZE" << query->lastError().text();
        size = 0;
    }
    while(query->next())
    {
        size +=1;
    }
    query->finish();
    return size;
}

bool sqlBase::deleteInvestigation(int ID, int visitDate, QString path, QString name)
{
    query->clear();
    bool b = query->exec(QString("DELETE FROM investigations"
                                 " WHERE ID=%1 AND"
                                 " VISITDATE=%2 AND"
                                 " NAME=\"%4\"")
                         .arg(ID)
                         .arg(visitDate)
                         .arg(name));
    if (!b )
    {
        mDebug() << "ERROR DELETE investigation: ? : " << query->lastError().text();
    }
    query->finish();
    deleteInvestigationMedia(path);
    return  b ;
}

bool sqlBase::removeMediaUrlNormalizeRequest(int ID, int visitDate, QString path, QString name)
{
    query->clear();
    bool b = query->exec(QString("UPDATE investigations SET INVSTATE=0 , PATH=\"\""
                                 " WHERE ID=%1 AND"
                                 " VISITDATE=%2 AND"
                                 " NAME=\"%4\"")
                         .arg(ID)
                         .arg(visitDate)
                         .arg(name));
    if (!b )
    {
        mDebug() << "ERROR DELETE investigation: ? : " << query->lastError().text();
    }
    query->finish();
    deleteInvestigationMedia(path);
    return  b ;
}


QStringList sqlBase::investigationsPathListForVisit(int ID, int visitDate)
{
    QStringList pathList;
    query->clear();
    bool b = query->exec(QString("SELECT PATH FROM investigations"
                                 " WHERE ID=%1 AND"
                                 " VISITDATE=%2")
                         .arg(ID)
                         .arg(visitDate));
    if (!b )
    {
        mDebug() << "ERROR DELETE VISIT investigation: ? : " << query->lastError().text();
    }
    while(query->next())
    {
        pathList << query->value(0).toString();
    }
    query->finish();

    return  pathList ;
}

void sqlBase::closeDataBase()
{
    query->finish();
    db.close();
}

QStandardItemModel *sqlBase::getAgendaModel(int julianDate,QStandardItemModel *agendaModel)
{
    query->clear();
    bool x = query->exec(QString("SELECT * FROM agendaView "
                                 "WHERE followDate=%1 AND followDate!=visitJulianDate AND checkButtonCaseClose=\"false\"")
                         .arg(julianDate));
    if ( !x )
    {
        mDebug() << "Failed to load agendaView " << query->lastError().text();
    }

    agendaModel->clear();
    int row = 0;
    int _id;

    int todayJulian = static_cast<int>(QDate::currentDate().toJulianDay());

    patientInfo info;

    while(query->next())
    {
        _id = query->value(0).toInt();
        QStandardItem *idItem = new QStandardItem();
        idItem->setData(QVariant(_id), Qt::DisplayRole);
        info.Name = getHumanizedName(query->value(1).toString());

        QStandardItem *nameItem = new QStandardItem(info.Name);
        QStandardItem *checkableItem = new QStandardItem(true);
        checkableItem->setCheckable(false);
        checkableItem->setCheckState(Qt::CheckState(Qt::Unchecked));

        agendaModel->setItem(row,0,idItem);
        agendaModel->setItem(row,1,nameItem);
        agendaModel->setItem(row,2,checkableItem);

        info.Mobile = query->value(5).toString();
        info.Age = getAge(todayJulian - query->value(6).toInt());
        info.Gender = query->value(7).toString();
        info.Residence = query->value(8).toString();
        info.MaritalStatus = query->value(9).toString();
        info.Occupation = query->value(10).toString();

        agendaModel->item(row,1)->setToolTip(getPatientTooltip(info));
        row +=1;
    }


    agendaModel->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Attended");

    query->finish();
    return agendaModel;
}

QStandardItemModel *sqlBase::getMyRegisterModel(RegisterRange timeframe, QStandardItemModel *myRegisterModel, sqlExtra *sqlextra)
{
    QLocale en_US = QLocale(QLocale::English,QLocale::UnitedStates);
    encryptionEnabled=isEncryptionEnabled();
    query->clear();

    QString querycmd;

    if ( (timeframe.startTime < timeframe.endTime) &&  (timeframe.endDate == timeframe.startDate) )
    {
        querycmd=QString("SELECT * FROM registerView "
                         "WHERE visitJulianDate=%1 AND visitTime>=%2 AND visitTime<=%4")
                .arg(timeframe.startDate)
                .arg(timeframe.startTime)
                .arg(timeframe.endTime);
    }
    else if ( (timeframe.endDate - timeframe.startDate) == 1 )
    {
        querycmd=QString("SELECT * FROM registerView "
                         "WHERE visitJulianDate=%1 AND visitTime>=%2 AND visitTime<=%3 "
                         "UNION ALL "
                         "SELECT * FROM registerView "
                         "WHERE visitJulianDate=%4 AND visitTime>=%5 AND visitTime<=%6")
                .arg(timeframe.startDate)
                .arg(timeframe.startTime)
                .arg(86340)
                .arg(timeframe.endDate)
                .arg(0)
                .arg(timeframe.endTime);
    }
    else if ( (timeframe.endDate - timeframe.startDate) >= 2 )
    {
        querycmd=QString("SELECT * FROM registerView "
                         "WHERE visitJulianDate=%1 AND visitTime>=%2 AND visitTime<=%3 "
                         "UNION ALL "
                         "SELECT * FROM registerView "
                         "WHERE visitJulianDate>%4 AND visitJulianDate<%5 "
                         "UNION ALL "
                         "SELECT * FROM registerView "
                         "WHERE visitJulianDate=%6 AND visitTime>=%7 AND visitTime<=%8")
                .arg(timeframe.startDate)
                .arg(timeframe.startTime)
                .arg(86340)
                .arg(timeframe.startDate)
                .arg(timeframe.endDate)
                .arg(timeframe.endDate)
                .arg(0)
                .arg(timeframe.endTime);
    }
    else
    {
        myRegisterModel->clear();
        return myRegisterModel;
    }

    //mDebug() << querycmd;
    bool x = query->exec(querycmd);

    if ( !x )
    {
        mDebug() << "Failed to load registerView " << query->lastError().text();
        mDebug() << query->executedQuery();
    }

    myRegisterModel->clear();
    int row = 0;
    int _id;
    int visitType;
    int todayJulian = static_cast<int>(QDate::currentDate().toJulianDay());
    double price;
    int julianDate,timeMS;
    QList<QBrush> brushes = getVisitColors();
    patientInfo info;

    while(query->next())
    {

        _id = query->value(0).toInt();
        info.Name = getHumanizedName(query->value(1).toString());
        visitType = query->value(2).toInt();
        julianDate = query->value(3).toInt();
        timeMS = query->value(4).toInt();
        price = query->value(5).toDouble();
        info.Mobile = query->value(6).toString();
        info.Age = getAge(todayJulian - query->value(7).toInt());
        info.Gender = query->value(8).toString();
        info.Residence = query->value(9).toString();
        info.MaritalStatus = query->value(10).toString();
        info.Occupation = query->value(11).toString();


        QStandardItem *idItem = new QStandardItem;
        idItem->setData(QVariant(_id), Qt::DisplayRole);
        idItem->setBackground(brushes.at(visitType));

        QStandardItem *nameItem = new QStandardItem(info.Name);
        nameItem->setBackground(brushes.at(visitType));

        QStandardItem *visitTypeItem = new QStandardItem(dataHelper::getVisitType(visitType,settings));
        visitTypeItem->setBackground(brushes.at(visitType));

        QStandardItem *dateTimeItem = new QStandardItem(QString("%1%2").arg(julianDate).arg(timeMS));
        QStandardItem *dateItem = new QStandardItem(QString::number(julianDate));
        QStandardItem *priceItem = new QStandardItem;
        priceItem->setData(QVariant(price),Qt::DisplayRole);

        myRegisterModel->setItem(row,0,idItem);
        myRegisterModel->setItem(row,1,nameItem);
        myRegisterModel->setItem(row,2,dateTimeItem);
        myRegisterModel->setItem(row,3,dateItem);
        myRegisterModel->setItem(row,4,visitTypeItem);

        QString date = en_US.toString(QDate::fromJulianDay(julianDate),"dd/MM/yyyy");
        QString time = en_US.toString(QTime::fromMSecsSinceStartOfDay(timeMS*1000),"hh:mm AP");

        myRegisterModel->item(row,4)->setToolTip(QString("%1 - %2").arg(date).arg(time));
        myRegisterModel->setItem(row,5,priceItem);

        myRegisterModel->item(row,1)->setToolTip(getPatientTooltip(info));
        row +=1;
    }
    query->finish();

    QStringList labels;
    QStringList serviceList = sqlextra->getPaidServicesList();
    labels << "ID" << "Name" << "julianDateTime" << "julianDate" << "VisitType" << "price";
    labels << serviceList;

    myRegisterModel->setHorizontalHeaderLabels(labels);

    int columns = labels.count();
    QString serviceName;
    int rows = myRegisterModel->rowCount();
    for ( int x=6;x<columns;x++)
    {
        serviceName = serviceList.at(x-6);
        for ( int r=0;r<rows;r++)
        {
            QStandardItem *item = new QStandardItem(true);
            item->setCheckable(false);
            item->setCheckState(Qt::CheckState(Qt::Unchecked));
            item->setBackground(myRegisterModel->item(r,0)->background());
            myRegisterModel->setItem(r,x,item);
        }
    }


    return myRegisterModel;
}

QStandardItemModel *sqlBase::getEddModel(qint64 start, qint64 end, QStandardItemModel *eddModel)
{
    query->clear();

    int EDD_start = static_cast<int> (start - 280);
    int EDD_end   = static_cast<int> (end - 280);

    //    mDebug() << QDate::fromJulianDay(EDD_start).toString("dd/MM/yyyy");
    //    mDebug() << QDate::fromJulianDay(EDD_end).toString("dd/MM/yyyy");
    bool x = query->exec(QString("SELECT * FROM EddView "
                                 "WHERE LMPDATE >= %1 AND LMPDATE < %2 AND "
                                 "Antenatal='true'")
                         .arg(EDD_start)
                         .arg(EDD_end));
    if ( !x )
    {
        mDebug() << "Failed to load eddView " << query->lastError().text();
    }

    eddModel->clear();
    int row = 0;
    int _id;
    qint64 todayJulian = QDate::currentDate().toJulianDay();
    patientInfo info;

    while(query->next())
    {
        _id = query->value(QString("ID")).toInt();
        QStandardItem *idItem = new QStandardItem();
        idItem->setData(QVariant(_id), Qt::DisplayRole);

        info.Name = getHumanizedName(query->value(QString("Name")).toString());
        info.Mobile = query->value(QString("mobile")).toString();
        info.Age = getAge(static_cast<int>(todayJulian) - query->value(QString("Age")).toInt());
        info.Gender = query->value(QString("Gender")).toString();
        info.Residence = query->value(QString("Residence")).toString();
        info.MaritalStatus = query->value(QString("maritalStatus")).toString();
        info.Occupation = query->value(QString("occupation")).toString();

        QStandardItem *nameItem = new QStandardItem(info.Name);
        QStandardItem *ageItem = new QStandardItem(info.Age);
        QStandardItem *mobileItem = new QStandardItem(info.Mobile);
        QStandardItem *gpaItem = new QStandardItem(query->value(QString("GPA")).toString());

        QString eddString = QDate::fromJulianDay(int(query->value(QString("LMPDATE")).toInt() + 280)).toString("dddd dd/MM/yyyy");
        QStandardItem *eddItem = new QStandardItem(eddString);
        eddModel->setItem(row,0,idItem);
        eddModel->setItem(row,1,nameItem);
        eddModel->setItem(row,2,ageItem);
        eddModel->setItem(row,3,mobileItem);
        eddModel->setItem(row,4,gpaItem);
        eddModel->setItem(row,5,eddItem);
        eddModel->item(row,1)->setToolTip(getPatientTooltip(info));
        row +=1;
    }


    eddModel->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Age" << "Mobile" << "GPA" << "Date");


    query->finish();
    return eddModel;
}

QStringList sqlBase::getInvestigationsMediaFilesList()
{
    QString sqlCMD = "SELECT PATH FROM investigations WHERE  INVSTATE=1";
    return sqlExecList(sqlCMD);
}

bool sqlBase::createEmptyPatientProfiles(int maxID)
{
    encryptionEnabled=isEncryptionEnabled();
    killLoopFlag_ = false;
    db.transaction();
    int minID = getPatientIndexLength();
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString name,sqlCMD;
    bool b = false;
    for (int id=minID;id<maxID+1;id++)
    {

        if (killLoopFlag_)
        {
            db.rollback();
            //break;
            return b;
        }
        //name = crypto.encryptToString(QString("Patient Record #%1").arg(id));
        name = getComputerizedName(QString("Patient Record #%1").arg(id));
        sqlCMD = QString ("INSERT INTO patients(ID,Name,dateTime)VALUES(%1,\"%2\",\"%3\")")
                .arg(id)
                .arg(name)
                .arg(dateTime);
        emit emptyProfileProgressbar(id,maxID);
        query->clear();
        b = query->exec(sqlCMD);
        if (!b)
        {
            mDebug() << "Failed to create empty profiles ?" << query->lastError().text();
            db.rollback();
            query->finish();
            return b;
        }

    }
    query->finish();
    db.commit();
    return b;
}

bool sqlBase::setPassWD(QString pw)
{
    bool b=false;
    QByteArray passArray = pw.toUtf8();
    QString password =  QString(QCryptographicHash::hash((passArray),QCryptographicHash::Md5).toHex());
    if(isUserExists("doktor"))
    {
        b =  queryExec(QString("UPDATE credentials SET passwordHash=\"%1\"").arg(password));
    }
    else
    {
        b = queryExec(QString("INSERT INTO credentials (userName,passwordHash) VALUES (\"doktor\",\"%1\")").arg(password));
    }
    return b;
}

bool sqlBase::clearPW()
{
    bool b=false;
    if(isUserExists("doktor"))
    {
        b =  queryExec("UPDATE credentials SET passwordHash=NULL");
    }
    else
    {
        b = queryExec("INSERT INTO credentials (userName,passwordHash) VALUES (\"doktor\",NULL)");
    }
    return b;
}

QString sqlBase::getUserPasswordHash(QString user)
{
    return sqlExec(QString("SELECT passwordHash FROM credentials WHERE userName=\"%1\"").arg(user));
}
