// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DATAIOHELPER_H
#define DATAIOHELPER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QXmlStreamReader>
#include <QtXml/QDomDocument>
#include <QFileInfo>
#include <QDir>
#include "mdebug.h"
#include "globalvariables.h"
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QCoreApplication>

class dataIOhelper : public QObject
{
    Q_OBJECT
public:
    explicit dataIOhelper(QObject *parent = nullptr);
    static QString getTextFileContents(QString filePath);
    static QStringList getTextFileContentsAsList(QString filePath);
    static QStandardItemModel *getBackUpModel(QObject *parent=nullptr);
    static bool add2BackUpXML(int row , QString date, QString zipPath, QString MD5);
    static bool removeBackUpXml(QString selectedZip);
    static bool writeXMLdoc(QDomDocument doc, QString path);
    static QDomDocument readXMLdoc(QString path);
    static QByteArray readFile(QString path);
    static void saveFile(QString path,QByteArray data);
    static void deleteFile(QString path);
    static void renameFile(QString f,QString s);
    static QString setCurrentFolder(bool forceChange=false);
    static QString getCurrentFolder();
    static bool isPortable();
    static bool makePortable(bool enable);
    static QString PortabilityLockFile();
    static void dumpLogoNotExists(bool force=false);
};

#endif // DATAIOHELPER_H