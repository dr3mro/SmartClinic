// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "datahelper.h"
#include "msettings.h"
#include <QRegularExpression>

dataHelper::dataHelper(QObject *parent) : QObject(parent)
{

}

QString dataHelper::cleanHTML(QString string){
    QTextDocument doc;
    doc.setHtml(string);
    return doc.toPlainText();
}

QString dataHelper::julianToAge(int totalDays,dataHelper::AgeStyle style)
{
    int years = totalDays/365;
    int months = (totalDays%365)/30;
    int days = (totalDays%365)%30;
    QString _string;

    switch (style) {
    case AgeStyle::normal:
        _string = "%1 Years old.";
        return QString(_string).arg(QString::number(years));
        break;
    case AgeStyle::expanded:
        _string = "%1 Years %2 Months %3 Days.";
        break;
    case AgeStyle::compact:
        _string = "<b>%1</b>Y<b>%2</b>M<b>%3</b>D";
        break;
    case AgeStyle::printable:
        _string = "%1";
        return QString(_string).arg(QString::number(years));
    default:
        break;
    }

    QString dateString = QString(_string).arg(
                QString::number(years),
                QString::number(months),
                QString::number(days));
    return dateString;
}

QString dataHelper::daysToAge(int totalDays)
{
    if ( totalDays ==  0)
    {
        totalDays = QDate::currentDate().toJulianDay();
    }
    int lifeJulian = QDate::currentDate().toJulianDay() - totalDays ;
    int years = lifeJulian/365;
    int months = (lifeJulian%365)/30;
    int days = (lifeJulian%365)%30;


    QString dateString = QString("%1 Years %2 Months %3 Days").arg(
                QString::number(years),
                QString::number(months),
                QString::number(days));
    return dateString;
}

int dataHelper::ageToYear( int totalDays )
{
    if ( totalDays ==  0)
    {
        totalDays = QDate::currentDate().toJulianDay();
    }
    int lifeJulian = QDate::currentDate().toJulianDay() - totalDays ;
    int years = lifeJulian/365;
    return years;
}

int dataHelper::julianToYear(int totalDays)
{
    int years = totalDays/365;
    return years;
}

//QString dataHelper::numericToVisitType(int x)
//{
//    QStringList visitTypes;
//    visitTypes << "New Visit" << "Follow Up1" << "Follow Up2" << "Follow Up3" << "Follow Up4" << "Free";
//    return visitTypes.at(x);
//}

bool dataHelper::str2bool(QString string)
{
    return (string == "true")? true:false;
}

QString dataHelper::bool2String(bool b)
{
    return (b == true)? QString("true"):QString("false");
}

int dataHelper::appversiontoint(QByteArray ba)
{
    return QString(ba).remove(".").toInt();
}

void dataHelper::switchToEasternArabic(QString & str)
{
    str.replace("0","٠");
    str.replace("1","١");
    str.replace("2","٢");
    str.replace("3","٣");
    str.replace("4","٤");
    str.replace("5","٥");
    str.replace("6","٦");
    str.replace("7","٧");
    str.replace("8","٨");
    str.replace("9","٩");
}

void dataHelper::delay(const int &delay_msec)
{
    QTime dieTime= QTime::currentTime().addMSecs(delay_msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool dataHelper::doubleEqual(double a, double b)
{
    //    mDebug() << a << b;
    return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

//QString dataHelper::getVisitType(int visitType, mSettings &settings)
//{
//    int maxfollowups = settings.getMaxFollowUpsPerProblem();

//    if (visitType == 0 ) {
//        return QString("New Visit");
//    }else if(visitType <= maxfollowups){
//        return QString("Follow Up%1").arg(visitType);
//    }else if (visitType == maxfollowups+1) {
//        return QString("Free");
//    }else
//        return QString("Undefined");

//}

void dataHelper::cleanExpanderHTML(QString &expander)
{
    expander.remove(QRegularExpression("style=\\\"([^\"]*)\\\"", QRegularExpression::CaseInsensitiveOption));
    expander.remove(QRegularExpression("\\n", QRegularExpression::CaseInsensitiveOption));
    expander.remove(QRegularExpression("<p ><span >", QRegularExpression::CaseInsensitiveOption));
    expander.replace(QRegularExpression("</span></p>"),"<br>");
    expander.remove(QRegularExpression("^.*<body >", QRegularExpression::CaseInsensitiveOption));
    expander.remove(QRegularExpression("<br><body>", QRegularExpression::CaseInsensitiveOption));
    expander.remove(QRegularExpression("<br></body></html>", QRegularExpression::CaseInsensitiveOption));
}

void dataHelper::cleanDrugName(QString &drug)
{
    drug.remove("(IMP)");
    drug.remove("e/n");
    drug.remove("e/e");
    drug.remove(QRegularExpression("\\d+[(A|ST.|T|C|BX|S|V|CT|NV|P|D|F|L]+\\W+"));
}

dataHelper::~dataHelper()
{

}

