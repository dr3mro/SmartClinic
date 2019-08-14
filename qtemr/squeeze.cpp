#include "squeeze.h"

squeeze::squeeze(QObject *parent) :
    QObject(parent)
{
}

void squeeze::compact (QString filename , QString zipfilename)
{
    dataIOhelper::saveFile(zipfilename,qCompress(dataIOhelper::readFile(filename),9));
}

void squeeze::expand (QString zipfilename , QString filename)
{
    dataIOhelper::saveFile(filename,qUncompress(dataIOhelper::readFile(zipfilename)));
}
