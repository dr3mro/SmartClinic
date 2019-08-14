#ifndef SQLBASE_H
#define SQLBASE_H

#include <QObject>
#include <QApplication>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>

#include "sqlextra.h"
#include "datahelper.h"
#include "simplecrypt.h"
#include "globalvariables.h"
#include "excelexport.h"
#include "msql.h"
#include "drugsitemmodel.h"
#include "msettings.h"
#include "investmodel.h"

class sqlBase : public msql
{
    Q_OBJECT
public:

    struct Patient
    {
        int ID;
        QString dateTime;
        QString age;
        QString gender;
        QString residence;
        QString maritalStatus;
        QString birthPlace;
        QString occupation;
        QString smoker;
        QString cigarretsPerDay;
        QString smokingYears;
        QString mobile;
        QString alcohol;
        QString name;
        QString pastHistory;
        QString familyHistory;
        QString allergy;
        QString operations;
        QString notes;
        int ABO;
        void clear()
        {
            ID = 0;
            name = pastHistory =  familyHistory = allergy ="";
            operations = notes ="";
            dateTime = residence = birthPlace = "";
            occupation = mobile= "";
            maritalStatus = "Single";
            gender = "Male";
            age = QString::number(QDate::currentDate().toJulianDay());
            cigarretsPerDay = smokingYears = "0";
            alcohol= smoker="false";
            ABO = 0;
        }

    };

    struct mPatient
    {
        int ID;
        QString dateTime;
        QString age;
        QString gender;
        QString residence;
        QString maritalStatus;
        QString birthPlace;
        QString occupation;
        QString smoker;
        QString cigarretsPerDay;
        QString smokingYears;
        QString mobile;
        QString alcohol;
        QString diabetes;
        QString hypertension;
        QString hyperlipidemia;
        QString chronicLiverDisease;
        QString chronicKidenyInjury;
        QString chronicObstructivePulmonaryDisease;
        QString peripheralVascularDisease;
        QString coronaryArteryDisease;
        QString bronchialAsthma;
        QString anemia;
        QString congestiveHeartFailure;
        QString hyperuricemia;
        QString bilharziasis;
        QString tuberculosis;
        QString pepticUlcer;
        QString IBS;
        QString name;
        QString pastHistory;
        QString familyHistory;
        QString allergy;
        QString drugs;
        QString operations;
        QString notes;
        QString devHead;
        QString devStand;
        QString devSit;
        QString devWalk;
        QString devCrawl;
        QString devTeeth;
        QString devMother;
        QString devlight;
        QString devSmile;
        QString devSpeech;
        QString devSound;
        QString pregLine;
        QString laborLine;
        QString NICULine;
        QString dietLine;
        QString GALine;
        QString GLine;
        QString PLine;
        QString LLine;

        int ABO;
        QString DMePregnancy;
        QString HTNePregnancy;
        QString AnemiaPregnancy;
        QString RheumaticFever;
        QString infertility;
        QString bloodTransfusion;
        QString varicoseVeins;
        QString CVS;
        QString MI;
        QString DVT;
        QString CHOLECYSTITIS;
        QString NasalAllergy;
        QString OSTEOARTHERITIS;
        QString PERIPHERALNEUROPATHY;
        QString husband;
        QString GPA;
        QString FPAL;
        QString menarche;
        int cycle;
        QString lastFor;
        QString every;
        int LMP;
        QString menoPause;
        int cyclePain;


        void clear()
        {
            ID = 0;
            dateTime = age = gender = residence = maritalStatus = birthPlace = "";
            occupation = smoker = cigarretsPerDay = smokingYears = "";
            mobile= alcohol= diabetes= hypertension= hyperlipidemia = "";
            chronicLiverDisease = chronicKidenyInjury = "";
            chronicObstructivePulmonaryDisease = peripheralVascularDisease= coronaryArteryDisease = "";
            bronchialAsthma = anemia = congestiveHeartFailure= hyperuricemia = bilharziasis ="";
            tuberculosis = pepticUlcer = IBS = name = pastHistory =  familyHistory = allergy ="";
            drugs = operations = notes = devHead = devStand = devSit = devWalk = "";
            devCrawl = devTeeth = devMother = devlight = devSmile = devSpeech = "";
            devSound = pregLine = laborLine = NICULine = dietLine = GALine = GLine = PLine = LLine = "";
            ABO = 0;
            DMePregnancy = HTNePregnancy = AnemiaPregnancy = RheumaticFever = infertility = bloodTransfusion = "";
            varicoseVeins = CVS = MI = husband = GPA = FPAL = menoPause = lastFor = every = menarche = "";
            cycle = cyclePain = 0;
            LMP = static_cast<int>(QDate::currentDate().toJulianDay());
            DVT = NasalAllergy = CHOLECYSTITIS = OSTEOARTHERITIS = PERIPHERALNEUROPATHY = "";
        }
    };

    struct Visit
    {
        int ID;
        QString visitAge;
        QString presentation;
        QString presentationAnalysis;
        QString diagnosis;
        QString investigations;
        QString invResults;
        QString drugList;
        QString pulse;
        QString rr;
        QString temp;
        QString bp;
        QString weight;
        QString length;
        QString headCir;
        QString exGeneral;
        QString exChestHeart;
        QString exAbdback;
        QString exLL;
        QString visitNotes;
        QString visitDateTime;
        QString followDate;
        QString visitType;
        QString checkButtonCaseClose;
        int LMPDATE;
        QString ObstUS;
        QString Antenatal;
        QString pelvicExam;

        void clear()
        {
            ID = 0;
            visitAge = presentation = presentationAnalysis = diagnosis = "";
            investigations = invResults = drugList = pulse = rr = temp = bp = "";
            weight = length = headCir = exGeneral = exChestHeart = exAbdback = "";
            exLL = visitNotes = visitDateTime = followDate = visitType = checkButtonCaseClose = "";
            ObstUS = Antenatal = pelvicExam="";
            LMPDATE = static_cast<int>(QDate::currentDate().toJulianDay());
        }

        bool operator!=(const Visit& visit) const
        {
            return std::tie(
                        ID,
                        visitAge,
                        presentation,
                        presentationAnalysis,
                        diagnosis,
                        investigations,
                        invResults,
                        drugList,
                        pulse,
                        rr,
                        temp,
                        bp,
                        weight,
                        length,
                        headCir,
                        exGeneral,
                        exChestHeart,
                        exAbdback,
                        exLL,
                        visitNotes,
                        visitDateTime,
                        followDate,
                        visitType,
                        checkButtonCaseClose,
                        LMPDATE,
                        ObstUS,
                        Antenatal,
                        pelvicExam
                        ) !=
                    std::tie(
                        visit.ID,
                        visit.visitAge,
                        visit.presentation,
                        visit.presentationAnalysis,
                        visit.diagnosis,
                        visit.investigations,
                        visit.invResults,
                        visit.drugList,
                        visit.pulse,
                        visit.rr,
                        visit.temp,
                        visit.bp,
                        visit.weight,
                        visit.length,
                        visit.headCir,
                        visit.exGeneral,
                        visit.exChestHeart,
                        visit.exAbdback,
                        visit.exLL,
                        visit.visitNotes,
                        visit.visitDateTime,
                        visit.followDate,
                        visit.visitType,
                        visit.checkButtonCaseClose,
                        visit.LMPDATE,
                        visit.ObstUS,
                        visit.Antenatal,
                        visit.pelvicExam
                        );
        }
    };

    struct visitData
    {
        int ID;
        sqlBase::Visit visit;
        int visitDate;
        QString visitDateTime;
        DrugsItemModel *drugsModel;
        InvestModel  *invModel;
        double visitPrice;
    };

    struct development
    {
        int ID;
        bool devHead;
        bool devStand;
        bool devSit;
        bool devWalk;
        bool devCrawl;
        bool devTeeth;
        bool devMother;
        bool devlight;
        bool devSmile;
        bool devSpeech;
        bool devSound;

        void clear()
        {
            devHead=false;
            devStand=false;
            devSit=false;
            devWalk=false;
            devCrawl=false;
            devTeeth=false;
            devMother=false;
            devlight=false;
            devSmile=false;
            devSpeech=false;
            devSound=false;
        }
        bool operator!=(const development& devel) const
        {
            return std::tie(
                        devHead,
                        devStand,
                        devSit,
                        devWalk,
                        devCrawl,
                        devTeeth,
                        devMother,
                        devlight,
                        devSmile,
                        devSpeech,
                        devSound
                        ) !=
                    std::tie(
                        devel.devHead,
                        devel.devStand,
                        devel.devSit,
                        devel.devWalk,
                        devel.devCrawl,
                        devel.devTeeth,
                        devel.devMother,
                        devel.devlight,
                        devel.devSmile,
                        devel.devSpeech,
                        devel.devSound
                        );
        }
    };

    struct perinatal
    {
        int ID;
        QString pregLine;
        QString laborLine;
        QString NICULine;
        QString dietLine;
        QString GALine;
        QString GLine;
        QString PLine;
        QString LLine;

        void clear()
        {
            pregLine="";
            laborLine="";
            NICULine="";
            dietLine="";
            GALine="";
            GLine="";
            PLine="";
            LLine="";
        }
        bool operator!=(const perinatal& pnatal) const
        {
            return std::tie(
                        pregLine,
                        laborLine,
                        NICULine,
                        dietLine,
                        GALine,
                        GLine,
                        PLine,
                        LLine
                        ) !=
                    std::tie(
                        pnatal.pregLine,
                        pnatal.laborLine,
                        pnatal.NICULine,
                        pnatal.dietLine,
                        pnatal.GALine,
                        pnatal.GLine,
                        pnatal.PLine,
                        pnatal.LLine
                        );
        }
    };

    struct obGyn
    {
        int ID;
        QString husband;
        QString GPA;
        QString FPAL;
        QString menarche;
        int cycle;
        QString lastFor;
        QString every;
        int LMP;
        bool menoPause;
        bool cyclePain;

        void clear()
        {
            husband="";
            GPA="G-P+";
            FPAL="---";
            menarche="";
            cycle=0;
            lastFor="";
            every="";
            LMP=QDate::currentDate().toJulianDay();
            menoPause=false;
            cyclePain=false;
        }

        bool operator!=(const obGyn& og) const
        {
            return std::tie(
                        GPA,
                        FPAL,
                        menarche,
                        cycle,
                        lastFor,
                        every,
                        LMP,
                        menoPause,
                        cyclePain
                        ) !=
                    std::tie(
                        og.GPA,
                        og.FPAL,
                        og.menarche,
                        og.cycle,
                        og.lastFor,
                        og.every,
                        og.LMP,
                        og.menoPause,
                        og.cyclePain
                        );
        }
    };

    struct Attended
    {
        bool state;
        QTime time;
        int visitType;
        void clear()
        {
            state = false;
            time = QTime::fromMSecsSinceStartOfDay(0);
            visitType=-1;
        }
    };

    struct temp
    {
        int ID;
        int date;
        int time;
        int vType;
    };

    struct t_conditions
    {
        int diabetes;
        int hypertension;
        int hyperlipidemia;
        int chronicLiverDisease;
        int chronicKidenyInjury;
        int chronicObstructivePulmonaryDisease;
        int peripheralVascularDisease;
        int coronaryArteryDisease;
        int bronchialAsthma;
        int anemia;
        int congestiveHeartFailure;
        int hyperuricemia;
        int bilharziasis;
        int tuberculosis;
        int pepticUlcer;
        int IBS;
        int DMePregnancy;
        int HTNePregnancy;
        int AnemiaPregnancy;
        int RheumaticFever;
        int infertility;
        int bloodTransfusion;
        int varicoseVeins;
        int CVS;
        int MI;
        int DVT;
        int NasalAllergy;
        int CHOLECYSTITIS;
        int OSTEOARTHERITIS;
        int PERIPHERALNEUROPATHY;
    };

    struct ServiceState
    {
        double price;
        bool state;
    };

    struct patientInfo {
        QString Name;
        QString Age;
        QString Gender;
        QString Residence;
        QString MaritalStatus;
        QString Occupation;
        QString Mobile;
    };


    struct visitItem
    {
        int visitType;
        QString visitDateTime;
        QString Diagnosis;
        int julianDay;
    };

    struct Sibling
    {
        QString DateOfBirth;
        QString TypeOfDelivery;
        QString Gender;
        QString PlaceOfBirth;
        QString Complications;
        QString State;
        QString Term;
    };

    struct RegisterRange
    {
        int startDate;
        int startTime;
        int endDate;
        int endTime;
    };

    explicit sqlBase(QObject *parent = nullptr, QString connectionName="qt_sql_base_connection", bool createTables=true);
    int getPatientIndexLength();
    int getPatientIDfromName(QString patientName);
    QString getPatientNamefromID(int ID);
    QStringList getPatientNameList();
    QVector<visitItem> getPatientVisits(int ID);
    QStandardItemModel *getPatientsTableModel();
    sqlBase::Patient getPatientData(int ID);
    sqlBase::mPatient getmPatientData(int ID);
    Visit getPatientVisitData(int ID , QString dateTimeString);
    bool addPatient2myDataBase(Patient patient);
    bool addVisit2myDataBase(Visit visit);
    bool addSurgicalNote(int ID, QString surgeryID, int julianDate, QString opName, QString opReport);
    bool addInvestigation(int ID, int visitDate, QString invName, QString invPath, int invDate, QString invTime, int invState, double price , QString invResults );
    bool isVisitExists(int ID , QString visitDateTime);
    bool isPatientExists(int ID);
    ServiceState isServiceExistsInThisVisit(int ID, int visitDate, QString ServiceName);
    sqlBase::Attended isFollowVisitAttended(int ID,int julianDate);
    bool isPatientNameUsed(QString name);
    bool updatePatient(int ID , Patient patient);
    bool updateVisit(int ID, QString visitDateTime , Visit visit);
    bool savePatient(int ID, Patient patient);
    bool saveVisit(int ID, QString visitDateTime , Visit visit, double Price);
    bool savePatientData(Patient& patient, DrugsItemModel *drugsModel, QStandardItemModel *siblings, QList<QPair<QString, int> > conditions, development develop, perinatal pnatal, obGyn og);
    bool saveVisitData(visitData vdata);
    DrugsItemModel *readDrugs(int ID, int visitDate, DrugsItemModel *drugsModel);
    QStandardItemModel *readSiblings(int ID,QStandardItemModel *model);
    QStandardItemModel *readSurgNotes(int ID,QStandardItemModel *model);
    bool saveDrugs(int ID, int visitDate, DrugsItemModel *model);
    bool saveSiblings(int ID,QStandardItemModel *model);
    bool updateSurgicalNote(int ID, QString surgeryID, int julianDate, QString opName, QString opReport);
    bool setVisitPrice(int ID, int visitDate,int visitTime,double price);
    bool updateVisitPrice(int ID, int visitDate,int visitTime,double price);
    bool deleteVisitPrice(int ID,int visitDate,int visitTime);
    bool deletePatientRecord(int ID);
    bool copyVisit2ID(int fID,int tID,QStringList visitList);
    bool deletePatientVisit(int ID, int julianDate);
    bool deleteSugicalNote(int ID,QString surgeryID);
    QString createPatientUpdatePreparePhrase(int ID);
    QString createVisitUpdatePreparePhrase(int ID,QString visitDateTime);
    QString createSurgicalNotesPrepareUpdatePhrase(int ID , QString surgeryID );
    QString createPatientInsertPreparePhrase();
    QString createVisitInsertPreparePhrase();
    QString createSurgicalNotesPrepareInsertPhrase();
    bool bindAndExecPatientSqlQuery(QString queryPhrase, Patient patient);
    bool bindAndExecVisitSqlQuery(QString queryPhrase , Visit visit);
    bool bindAndExecSurgicalNoteQuery(QString queryPhrase, int ID, QString surgeryID, int julianDate, QString opName, QString opReport);
    bool createPatientItemModel();
    bool queryExec(QString sqlPhrase);
    QStringList sqlExecList(QString sqlCmd, bool crypt=false);
    QList<QPair<QString, QString> > sqlExecPair(QString sqlCmd);
    QString genericQuery(int ID , QString col , QString table);
    bool haveSameNameWithDifferentID(int ID , QString name);
    QStandardItemModel *patientTableModel;
    QList< QPair<QString,QString> > getListVisitsType(int ID);
    InvestModel *getInvestigationsModel(InvestModel *investModel, int ID, int visitJulianDate);
    bool saveInvestigationsModel(int ID, int visitDate, InvestModel *model);
    int getInvestigationsCount(int ID);
    bool deleteInvestigation ( int ID, int visitDate, QString path, QString name);
    bool removeMediaUrlNormalizeRequest( int ID, int visitDate, QString path, QString name);
    QStringList investigationsPathListForVisit(int ID, int visitDate);
    void closeDataBase();
    QStandardItemModel *getAgendaModel(int julianDate, QStandardItemModel *agendaModel);
    QStandardItemModel *getEddModel(qint64 start, qint64 end, QStandardItemModel *eddModel);
    QStringList getInvestigationsMediaFilesList();
    bool createEmptyPatientProfiles(int maxID);
    bool setPassWD(QString pw);
    bool clearPW();
    QString getUserPasswordHash(QString user);
    bool isPasswordSet();
    bool updateLMP(int ID,int julianDate);
    int getFollowUpsCountForThisDate(QDate dt, int ID);
    bool exportPatientListToXML(QString fileName);
    bool exportPatientListToXLS(QString fileName);
    QStringList getDeceasedList();
    void toggleDeceased(int ID, int state, int row);
    void agendaAttendedLoader(int julianDate, QStandardItemModel *agendaModel, double &percent);
    QStandardItemModel *getMyRegisterCalcModel(QStandardItemModel *myRegisterModel, QStandardItemModel *calcModel, sqlExtra *sqlextra, const QModelIndexList &selection, int &TOTAL);
    QStandardItemModel* getMyRegisterModel(RegisterRange timeFrame, QStandardItemModel *myRegisterModel, sqlExtra *sqlextra);
    void registerServiceLoader(QStandardItemModel *myRegisterModel,sqlExtra *sqlextra);
    void createNewVisit(int ID, QString previous , QDateTime datetime, int visitType, double visitPrice, DrugsItemModel *drugsModel, InvestModel *investModel, sqlExtra *sqlextra);
    QSqlTableModel *getConditionsModel(QSqlTableModel *conditionsModel);
    bool addCondition(QString name,int _id);
    QList<QPair<int,QString> > getConditions();
    bool insertDefaultConditions();
    bool savePatientConditions(int ID, QList<QPair<QString,int> > list);
    QList<QPair<QString,int> >  readPatientConditions(int ID);
    double getDatabaseVersion();
    int getConditionsStatus();
    bool setDatabaseVersion(double version);
    bool setFollowDate(int ID,QString visitDateTime,int followDate);
    development getDevelopment(int id);
    bool saveDevelopment(development develop);
    bool savePerinatal(perinatal pnatal);
    perinatal getPerinatal(int id);
    bool saveObGyn(obGyn og);
    obGyn getObGyn(int id);
    QString getAge(int julianDays, bool printable=false);
    bool isEncryptionEnabled();
    void toggleEncryption(bool enabled);
    bool deleteInvestigationMedia(const QString &path);
    int getDrugsCout(int id,int date);
    ~sqlBase();


public slots:
    //void killLoopFlag();

signals:
    void emptyProfileProgressbar(int a,int b);
    void showMessage(QString title,QString text);
    void reloadPatientList();
    void patientIconSet(bool,int);
private:
    bool createPatientTable();
    bool createVisitsTable();
    bool createPatientDrugsTable();
    bool createSiblingsTable();
    bool createInvstTable();
    bool createPWtable();
    bool createMetadataTable();
    bool createSurgeryTable();
    bool createDeceasedTable();
    bool createVisitsPriceTable();
    bool createConditionsTable();
    bool createConditionsPatientTable();
    bool createPerinatalTable();
    bool createObGynTable();
    bool createDevelopmentTable();
    bool isUserExists(QString user);
    bool isConditionRowExists(int ID);
    bool isDevelopmentRowExists(int ID);
    bool isObGynRowExists(int ID);
    bool isPerinatalRowExists(int ID);
    bool createAgendaView();
    bool createMyRegisterView();
    bool createEddView();
    bool columnExists(QString colName,QString table);
    void createIndexes();
    void upgradeDatabase();
    QList<sqlBase::temp> getMigrateList();
//    bool migratePrices();
    bool migrateConditions();
    bool migrateSmoking();
    bool migratePerinatal();
    bool migrateDevelopment();
    bool migrateObGyn();
    bool removePerinatalDevelopmentfromPatientsTable();
    bool removeObgynfromPatientsTable();
    QString getDecryptedName(QString rawName);
    QString getEncryptedName(QString rawName);
    void encryptDecryptNames(bool enable);
    QString getHumanizedName(QString rawName);
    QString getComputerizedName(QString rawName);
    QString getPatientTooltip(const patientInfo &info);
    void dropAllViews();
    void createAllViews();
    Patient patient;
    mPatient mpatient;
    Visit visit;
    SimpleCrypt crypto;
    bool encryptionEnabled;
    int getVisitType(int ID, int visitJulianDate);
    QList<QBrush> getVisitColors();


};

#endif // SQLBASE_H
