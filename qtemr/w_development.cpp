#include "w_development.h"
#include "ui_w_development.h"

w_development::w_development(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w_development)
{
    ui->setupUi(this);
    sqlbase = new sqlBase(this,"w_development",false);
}

void w_development::clear()
{
    ui->devHeadCB->setChecked(false);
    ui->devStandCB->setChecked(false);
    ui->devSitCB->setChecked(false);
    ui->devWalkCB->setChecked(false);
    ui->devCrawlCB->setChecked(false);
    ui->devTeethCB->setChecked(false);
    ui->devMotherCB->setChecked(false);
    ui->devLightCB->setChecked(false);
    ui->devSmileCB->setChecked(false);
    ui->devSpeechCB->setChecked(false);
    ui->devSoundCB->setChecked(false);
}

void w_development::load(int id)
{
    ID = id;
    sqlBase::development dev;
    dev = sqlbase->getDevelopment(ID);
    ui->devHeadCB->setChecked(dev.devHead);
    ui->devStandCB->setChecked(dev.devStand);
    ui->devSitCB->setChecked(dev.devSit);
    ui->devWalkCB->setChecked(dev.devWalk);
    ui->devCrawlCB->setChecked(dev.devCrawl);
    ui->devTeethCB->setChecked(dev.devTeeth);
    ui->devMotherCB->setChecked(dev.devMother);
    ui->devLightCB->setChecked(dev.devlight);
    ui->devSmileCB->setChecked(dev.devSmile);
    ui->devSpeechCB->setChecked(dev.devSpeech);
    ui->devSoundCB->setChecked(dev.devSound);
}

sqlBase::development w_development::getDevelopment(int id)
{
    sqlBase::development devel;
    devel.ID = id;
    devel.devHead = ui->devHeadCB->isChecked();
    devel.devStand = ui->devStandCB->isChecked();
    devel.devSit = ui->devSitCB->isChecked();
    devel.devWalk = ui->devWalkCB->isChecked();
    devel.devCrawl = ui->devCrawlCB->isChecked();
    devel.devTeeth = ui->devTeethCB->isChecked();
    devel.devMother = ui->devMotherCB->isChecked();
    devel.devlight = ui->devLightCB->isChecked();
    devel.devSmile = ui->devSmileCB->isChecked();
    devel.devSpeech = ui->devSpeechCB->isChecked();
    devel.devSound = ui->devSoundCB->isChecked();
    return devel;
}

bool w_development::isDevelopmentModified()
{
    sqlBase::development savedDevelop = sqlbase->getDevelopment(ID);
    sqlBase::development visibleDevelop = getDevelopment(ID);
    return(savedDevelop!=visibleDevelop);
}

void w_development::setID(int id)
{
    ID=id;
}

w_development::~w_development()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("w_development");
    delete ui;
}
