// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "squeeze.h"

squeeze::squeeze(QObject *parent) : QObject(parent) {}

void squeeze::compact(QString filename, QString zipfilename) {
  dataIOhelper::saveFile(zipfilename,
                         qCompress(dataIOhelper::readFile(filename), 9));
}

void squeeze::expand(QString zipfilename, QString filename) {
  dataIOhelper::saveFile(filename,
                         qUncompress(dataIOhelper::readFile(zipfilename)));
}
