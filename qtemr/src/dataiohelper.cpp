// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "dataiohelper.h"

dataIOhelper::dataIOhelper(QObject *parent) : QObject(parent) {}

QString dataIOhelper::getTextFileContents(QString filePath) {
  QFile file(filePath);
  QString contents;
  file.open(QFile::ReadOnly | QFile::Text);
  QTextStream in(&file);
  //    in.setCodec("UTF-8");
  contents = in.readAll();
  file.close();
  return contents;
}

QStringList dataIOhelper::getTextFileContentsAsList(QString filePath) {
  QFile file(filePath);
  QStringList contents;
  QString line;
  file.open(QFile::ReadOnly | QFile::Text);
  QTextStream in(&file);
  //    in.setCodec("UTF-8");
  while (!in.atEnd()) {
    line = in.readLine();
    contents << line;
  }
  file.close();
  return contents;
}

QStandardItemModel *dataIOhelper::getBackUpModel(QObject *parent) {
  double version = (double)dbVersion;
  QStandardItemModel *model = new QStandardItemModel(parent);
  QStandardItem *item1, *item2, *item3, *item4;
  QXmlStreamReader xmlread;
  QString path = QString("%1backup.xml").arg("./backup/");
  QFile file(path);
  if (!file.open(QFile::ReadOnly | QFile::Text)) return model;

  xmlread.setDevice(&file);
  QXmlStreamAttributes attributes;
  int x = 0;
  while (!xmlread.atEnd()) {
    xmlread.readNext();
    if (xmlread.name() == QString("item")) {
      attributes = xmlread.attributes();
      if (!attributes.empty()) {
        if (attributes.value("dbVersion").toDouble() == version) {
          item1 = new QStandardItem(attributes.value("date").toString());
          item2 = new QStandardItem(attributes.value("zipPath").toString());
          item3 = new QStandardItem(attributes.value("MD5").toString());
          item4 = new QStandardItem;
          item4->setData(QVariant(attributes.value("row").toInt()),
                         Qt::DisplayRole);
          model->setItem(x, 0, item1);
          model->setItem(x, 1, item2);
          model->setItem(x, 2, item3);
          model->setItem(x, 3, item4);
          x += 1;
        }
      }
    }
  }
  file.close();
  model->sort(3, Qt::DescendingOrder);
  return model;
}

bool dataIOhelper::add2BackUpXML(int row, QString date, QString zipPath,
                                 QString MD5) {
  double version = dbVersion;
  QString path = QString("backup/backup.xml");
  QDomDocument document = readXMLdoc(path);
  QDomElement root = document.firstChildElement();
  QDomElement domitem = document.createElement("item");
  root.appendChild(domitem);
  domitem.setAttribute("date", date);
  domitem.setAttribute("zipPath", zipPath);
  domitem.setAttribute("MD5", MD5);
  domitem.setAttribute("row", row);
  domitem.setAttribute("dbVersion", version);
  return writeXMLdoc(document, path);
}

bool dataIOhelper::removeBackUpXml(QString selectedZip) {
  QString path = QString("backup/backup.xml");
  QDomDocument document = readXMLdoc(path);
  QDomElement root = document.firstChildElement();
  QDomNodeList items = root.elementsByTagName("item");

  for (int i = 0; i < items.count(); i++) {
    QDomNode itemNode = items.at(i);
    QDomElement domitem = itemNode.toElement();
    QString z = domitem.attribute("zipPath");
    if (z == selectedZip) {
      root.removeChild(domitem);
    }
  }
  writeXMLdoc(document, path);
  return true;
}
bool dataIOhelper::writeXMLdoc(QDomDocument doc, QString path) {
  QFile file(path);
  QFileInfo fInfo(path);
  if (!fInfo.dir().exists()) {
    fInfo.dir().mkpath("./");
  }
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    mDebug() << "Open the file for writing failed";
    return false;
  } else {
    QTextStream stream(&file);
    // stream.setCodec("utf8");
    stream << doc.toString();
    file.close();
    return true;
  }
  return true;
}

QDomDocument dataIOhelper::readXMLdoc(QString path) {
  QDomDocument document;
  QFile file(path);
  if (!file.exists()) {
    document.setContent(QString("<xml/>"));
    writeXMLdoc(document, path);
  }
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    mDebug() << QString("%1<%2>").arg("Failed to open the file for reading.",
                                      path);
    document.setContent(QString("<xml/>"));
  } else {
    // loading
    if (!document.setContent(&file)) {
      mDebug() << "Failed to load the file for reading.<readXMLdoc>";
      document.setContent(QString("<xml/>"));
    }
    file.close();
  }
  return document;
}

QByteArray dataIOhelper::readFile(QString path) {
  QFile file(path);
  QByteArray ba;

  if (!file.exists()) return QByteArray();

  if (file.open(QFile::ReadOnly)) {
    ba = file.readAll();
    file.close();
  }
  return ba;
}

void dataIOhelper::saveFile(QString path, QByteArray data) {
  QFile file(path);
  if (!file.open(QFile::WriteOnly)) return;

  file.write(data);
  file.close();
  file.flush();
}

void dataIOhelper::deleteFile(QString path) {
  QFile f(path);
  if (f.exists()) f.remove();
}

void dataIOhelper::renameFile(QString f, QString s) {
  QFile file(f);
  if (file.exists()) file.rename(f, s);
}

QString dataIOhelper::setCurrentFolder(bool forceChange) {
  QString currentAppPath = getCurrentFolder();
  QString newAppPath = currentAppPath;

  bool pathChanged = false;

  if (currentAppPath.isEmpty() || forceChange) {
    if (!forceChange)
      QMessageBox::information(0, "Setup",
                               QString("This is the first time you run %1, "
                                       "Please configure your data location, "
                                       "if you cancel it will load on current "
                                       "executable folder and you will "
                                       "be asked the next time %1 is launched.")
                                   .arg(APPNAME),
                               QMessageBox::Ok);

    newAppPath = QFileDialog::getExistingDirectory(
        0, "Open Directory",
        currentAppPath.isEmpty()
            ? QCoreApplication::applicationDirPath().replace('/', '\\')
            : currentAppPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (newAppPath.isEmpty()) {
      if (QDir(currentAppPath).exists())
        newAppPath = currentAppPath;
      else
        newAppPath = QCoreApplication::applicationDirPath().replace('/', '\\');
    } else {
      pathChanged = true;
    }
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                  QSettings::NativeFormat);
    reg.setValue("ApplicationPath", newAppPath);
  }

  if (forceChange && pathChanged) {
    QMessageBox::information(
        0, "Message",
        QString("%1 will now exit to change data path, please relaunch %1.")
            .arg(APPNAME),
        QMessageBox::Ok);
    QFile lockFile(".lock");
    lockFile.remove();
    qApp->quit();
  }

  QDir::setCurrent(newAppPath);
  return newAppPath;
}

QString dataIOhelper::getCurrentFolder() {
  bool portablity = isPortable();
  QString currentAppPath;
  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);

  if (portablity)
    currentAppPath = QCoreApplication::applicationDirPath().replace('/', '\\');
  else
    currentAppPath = reg.value("ApplicationPath").toString().replace('/', '\\');

  return currentAppPath;
}

bool dataIOhelper::isPortable() {
  QFile portablity(PortabilityLockFile());
  return portablity.exists();
}

bool dataIOhelper::makePortable(bool enable) {
  bool state = false;
  QFile portability(PortabilityLockFile());

  if (enable)
    state = portability.open(QIODevice::WriteOnly);
  else
    state = portability.remove();

  return state;
}

QString dataIOhelper::PortabilityLockFile() {
  QString PortabilityLock =
      QString("%1/%2")
          .arg(QCoreApplication::applicationDirPath(), PORTABILITYLOCK)
          .replace('/', '\\');
  return PortabilityLock;
}

void dataIOhelper::dumpLogoNotExists(bool force) {
  QFile dest(LOGOFILE);
  if (force) dest.remove();

  if (dest.exists()) return;

  QFile src(":/Graphics/Graphics/logo.jpg");
  src.open(QIODevice::ReadOnly);
  dest.open(QIODevice::WriteOnly);
  QByteArray srcData = src.readAll();
  dest.write(srcData);
  src.close();
  dest.close();
}

void dataIOhelper::dumpBannerTemplate() {
  QFile dest(BANNERFILE);

  if (dest.exists()) dest.remove();

  QFile src("://banner.html");
  src.open(QIODevice::ReadOnly);
  dest.open(QIODevice::WriteOnly);
  QByteArray srcData = src.readAll();
  dest.write(srcData);
  src.close();
  dest.close();
}
void dataIOhelper::dumpTemplates() {
  QList<QPair<QString, QString> > templates{{BANNERFILE, "://banner.html"},
                                            {HEADERFILE, "://header.html"},
                                            {FOOTERFILE, "://footer.html"}};

  for (auto t : templates) {
    QFile dest(t.first);
    if (dest.exists()) continue;

    QFile src(t.second);
    src.open(QIODevice::ReadOnly);
    dest.open(QIODevice::WriteOnly);
    QByteArray srcData = src.readAll();
    dest.write(srcData);
    src.close();
    dest.close();
  }
}
