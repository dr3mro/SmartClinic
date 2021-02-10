// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "inviconhelper.h"

invIconHelper::invIconHelper(QObject *parent) : QObject(parent)
{

}

QString invIconHelper::getInvestigationTooltip(const QString &path, const QString &name,const int &scale)
{
    if(path.endsWith(".jpg",Qt::CaseInsensitive) || path.endsWith(".jpeg",Qt::CaseInsensitive) )
    {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        QImageReader imageReader;
        imageReader.setFileName(path);
        imageReader.setAutoTransform(true);
        QImage image = imageReader.read();
        image.scaled(scale,scale,Qt::KeepAspectRatio,Qt::FastTransformation).save(&buffer,"PNG");
        QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
        buffer.close();
        return QString("<center>"
                       "<b>%1</b><br/>"
                       "<img src='data:image/png;base64, %2'><br/>"
                       "<i>Shift + double click to open file.</i>"
                       "</center>")
                .arg(name)
                .arg(QString(iconBase64));
    }
    return name;
}

int invIconHelper::getScale()
{
    QDesktopWidget* m = QApplication::desktop();
    QRect rec = m->screenGeometry(m->screenNumber(QCursor::pos()));
    int height = rec.height();
    return height/3;
}

