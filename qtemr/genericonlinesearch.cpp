#include "genericonlinesearch.h"
#include "ui_genericonlinesearch.h"

genericOnlineSearch::genericOnlineSearch(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::genericOnlineSearch)
{
    ui->setupUi(this);
    connect(ui->label,SIGNAL(leftClicked()),this,SLOT(tradeNameDoubleClicked()));
    connect(ui->label,SIGNAL(rightClicked()),this,SLOT(searchGoogle()));
    setWindowFlags(Qt::Tool);
    model = new QStringListModel(this);
}

void genericOnlineSearch::setModel(QStringList drugs)
{
    model->setStringList(drugs);
    ui->listView->setModel(model);

    int drugs_count = drugs.count();
    int height=50;

    if ( drugs_count > 3 && drugs_count < 22 )
        height = drugs_count*23;
    else if ( drugs_count <=3 )
        height = 100;
    else if ( drugs_count >= 22 )
        height = 500;

    resize(this->width(),(height<100)? 100:height);

    mDialog *win = static_cast<mDialog*> (this->parent());
    move( win->frameGeometry().topLeft() + win->rect().center() - this->rect().center());

    ui->buttonSearch->setEnabled(false);

}

void genericOnlineSearch::setTradeName(QString tname)
{
    rawTradeName = tname;
    ui->label->setText(QString("<b>%1</b>").arg(rawTradeName));
}

genericOnlineSearch::~genericOnlineSearch()
{
    delete model;
    delete ui;
}

QString genericOnlineSearch::searchEngine()
{
    QString searchString;
    int engine = ui->comboBox->currentIndex();
    switch (engine) {
    case 0:
        searchString = "https://www.drugs.com/search.php?searchterm=%1";
        break;
    case 1:
        searchString = "http://www.rxlist.com/script/main/srchcont_rxlist.asp?src=%1&x=0&y=0";
        break;
    case 2:
        searchString = "http://google2.fda.gov/search?q=%1&client=FDAgov&proxystylesheet=FDAgov&output=xml_no_dtd&site=FDAgov&requiredfields=-archive:Yes&sort=date:D:L:d1&filter=1";
        break;
    case 3:
        searchString = "https://druginfo.nlm.nih.gov/drugportal/name/%1";
        break;
    case 4:
        searchString = "https://en.wikipedia.org/wiki/%1";
        break;
    case 5:
        searchString = "https://www.google.com.eg/search?q=%1";
        break;
    default:
        break;
    }
    return searchString;
}

void genericOnlineSearch::openUrl(QString generic, QString engine)
{
    QString url = QString(engine).arg(generic);
    QDesktopServices::openUrl(QUrl(url));
}

void genericOnlineSearch::doOpen(const QModelIndex &index)
{
    QString generic = index.data(Qt::DisplayRole).toString();
    QString engineUrl = searchEngine();
    openUrl(generic,engineUrl);
}

void genericOnlineSearch::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        close();

    QWidget::keyReleaseEvent(e);
}

void genericOnlineSearch::on_listView_activated(const QModelIndex &index)
{
    doOpen(index);
}

void genericOnlineSearch::on_buttonSearch_clicked()
{
    QModelIndex cell = ui->listView->selectionModel()->currentIndex();
    doOpen(cell);
    ui->buttonSearch->setEnabled(false);

}

void genericOnlineSearch::on_listView_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    ui->buttonSearch->setEnabled(true);
}

void genericOnlineSearch::tradeNameDoubleClicked()
{
    QString tradeName = QString(rawTradeName.split(QRegExp("(\\d+(\\.\\d+)?)")).first()).simplified();
    QString form = rawTradeName.split(" ").last();
    QString tradeForm = QString("%1 %2").arg(tradeName).arg(form);
    QString engineUrl = searchEngine();
    openUrl(tradeForm,engineUrl);
}

void genericOnlineSearch::searchGoogle()
{
    QString tradeName = QString(rawTradeName.split(QRegExp("(\\d+(\\.\\d+)?)")).first()).simplified();
    QString form = rawTradeName.split(" ").last();
    QString tradeForm = QString("%1 %2").arg(tradeName).arg(form);
    QString engineUrl = "https://www.google.com.eg/search?q=%1";
    openUrl(tradeForm,engineUrl);
}
