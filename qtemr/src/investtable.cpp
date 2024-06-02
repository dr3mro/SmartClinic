// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "investtable.h"

#include "qglobal.h"

investTable::investTable(QWidget *parent) : zTableView(parent) {
  setSortColumn(sortCol);
  connect(parent->window(), SIGNAL(setReadWrite(bool)), this,
          SLOT(makeReadWrite(bool)));
  connect(this, SIGNAL(itemMoved()), this, SLOT(save()));
  sqlbase = new sqlBase(this, "qt_sql_base_invstTable", false);
  sqlextra = new sqlExtra(this, "qt_sql_extra_invstTable", false);
  invModel = new InvestModel(this);
  nonPrintableFont.setItalic(true);
  nonPrintableFont.setBold(false);
  printableFont.setBold(true);
  serviceFont.setBold(true);
  serviceFont.setItalic(true);
  isReadOnly = false;
  setToolTip(
      "<html>"
      "<b>Tips:</b>"
      "<ul>"
      "<li><b>SHIFT+Double Left click:</b> toggles item printable / "
      "calculable.</li>"
      "<li><b>Double Middle click:</b> toggles item printable / "
      "calculable.</li>"
      "<li><b>SHIFT+↑/↓:</b> moves item up and down.</li>"
      "<li><b>CTRL+Double click :</b> adds / Removes JPEG file of item.</li>"
      "<li><b>Double click :</b> views JPEG file of current item.</li>"
      "</ul>"
      "<b>COLORS:</b>"
      "<ol>"
      "<li> <b style=\"color:Red;\"> &#9632;</b> : paid service that was added "
      "to this visit.</li>"
      "<li> <b style=\"color:Magenta;\"> &#9632;</b>  : paid service that was "
      "added to a previous visit.</li>"
      "<li> <b style=\"color:Blue;\"> &#9632;</b> :  this item has a JPEG "
      "image.</li>"
      "<li> <b style=\"color:Black;\"> &#9632;</b> :  this is a normal "
      "item.</li>"
      "<li> <b style=\"color:Black;\"> <i>Italic</i> </b>: this is a non "
      "printable item.</li>"
      "</ol>"
      "</html>");
  viewport()->installEventFilter(this);
  timer = new QTimer(this);
  timer->setInterval(50);
  connect(timer, SIGNAL(timeout()), this, SLOT(tweakInveMedia()));
  worker = new wm_invModelLoader;
  invTooltipWorker = new wm_investTooltipLoader;
  scale = invIconHelper::getScale();
  invTooltipWorker->setScale(scale);

  worker->setInvestigationsModel(invModel);
  invTooltipWorker->setInvestigationsModel(invModel);

  connect(&watcher, SIGNAL(finished()), this, SLOT(loadInvestigations()));
  connect(&tooltipWatcher, SIGNAL(finished()), this, SLOT(putToolTip()));
  connect(invModel, SIGNAL(modelAboutToBeClear()), invTooltipWorker,
          SLOT(killloop()));
}

void investTable::populateInvests(int id, qint64 t_julianDate,
                                  qint64 t_visitTime) {
  timer->stop();
  working = true;
  ID = id;
  this->visitJulianDate = t_julianDate;
  this->visitTime = t_visitTime;
  worker->setIdJulianDateTime(id, visitJulianDate, visitTime);
#if QT_VERSION >= 0x060000
  future = QtConcurrent::run(&wm_invModelLoader::Work, worker);
#else
  future = QtConcurrent::run(worker, &wm_invModelLoader::Work);
#endif

  watcher.setFuture(future);
}

bool investTable::saveInvestigation(const int &ID, const int &julianDate,
                                    const qint64 &visitTime) {
  if (!working)
    return sqlbase->saveInvestigationsModel(ID, julianDate, visitTime,
                                            invModel);

  return false;
}

bool investTable::addNewInvest(int _ID, int _julianDate, QString newInvest,
                               int state, double price) {
  if (newInvest.simplified().isEmpty()) return false;

  int invLength = invModel->rowCount();

  QString invest;
  int invstate;
  for (int i = 0; i < invLength; i++) {
    invest = invModel->item(i, 1)->text();
    invstate = invModel->item(i, 6)->text().toInt();

    if (invest.toUpper() == newInvest.toUpper()) {
      if (invstate == InvestModel::InvestigationsStates::wasPaid) {
        invModel->item(i, 6)->setText(
            QString::number(InvestModel::InvestigationsStates::isPaid));
        invModel->item(i, 7)->setText(QString::number(price));
        return true;
      } else if (invstate == InvestModel::InvestigationsStates::nonPrintable) {
        invModel->item(i, 6)->setText(
            QString::number(InvestModel::InvestigationsStates::normal));
        QList<QStandardItem *> item = invModel->takeRow(i);
        invModel->insertRow(getInvestigationCount(), item);
        return true;
      } else if (invstate == InvestModel::InvestigationsStates::hasMedia) {
        invModel->item(i, 6)->setText(QString::number(
            InvestModel::InvestigationsStates::PrintableWithMedia));
        QList<QStandardItem *> item = invModel->takeRow(i);
        invModel->insertRow(getInvestigationCount(), item);
        return true;
      }

      popUpMessage(
          "Warning",
          "The item you are trying to add to this List already exists!");
      return false;
    }
  }

  QStandardItem *IDItem = new QStandardItem;
  QStandardItem *nameItem = new QStandardItem;
  QStandardItem *visitDateItem = new QStandardItem;
  QStandardItem *pathItem = new QStandardItem;
  QStandardItem *invDateItem = new QStandardItem;
  QStandardItem *invTimeItem = new QStandardItem;
  QStandardItem *invStateItem = new QStandardItem;
  QStandardItem *priceItem = new QStandardItem;
  QStandardItem *resultsItem = new QStandardItem;

  // set text
  IDItem->setText(QString::number(_ID));
  nameItem->setText(newInvest);
  visitDateItem->setText(QString::number(_julianDate));
  invStateItem->setText(QString::number(state));
  invDateItem->setText(QString::number(QDate::currentDate().toJulianDay()));
  invTimeItem->setText(
      QString::number(QTime::currentTime().msecsSinceStartOfDay() / 1000));
  priceItem->setText(QString::number(price));
  QList<QStandardItem *> newRow;

  newRow.append(IDItem);
  newRow.append(nameItem);
  newRow.append(visitDateItem);
  newRow.append(pathItem);
  newRow.append(invDateItem);
  newRow.append(invTimeItem);
  newRow.append(invStateItem);
  newRow.append(priceItem);
  newRow.append(resultsItem);

  if (state == InvestModel::InvestigationsStates::isPaid ||
      state == InvestModel::InvestigationsStates::wasPaid) {
    invModel->insertRow(getServicesCount(), newRow);
  } else {
    invModel->insertRow(getInvestigationCount(), newRow);
  }

  sqlextra->addToAutoComplete("investigations", newInvest);
  setModel(invModel);
  tweakTable();

  if (state !=
      InvestModel::InvestigationsStates::isPaid)  // this to update print button
    emit togglePrintButton();

  return true;
}

bool investTable::addInvMedia(bool setState) {
  myMessageBox msgbox;
  int row = selectionModel()->currentIndex().row();
  QLocale locale(QLocale::English, QLocale::UnitedStates);

  QString invName = invModel->item(row, 1)->text().replace(
      QRegularExpression("[^A-Za-z\\d\\s]"), "_");
  QDateTime dateTime = QDateTime::currentDateTime();
  QString dt = locale.toString(dateTime, "ddMMyyyyHHmmss");
  //    int visitJulianDate = invModel->item(0,2)->text().toInt();

  QFileDialog fileDialog;

  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);
  QString m_Path = reg.value("lastFolder").toString();

  if (m_Path.isEmpty())
    m_Path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

  QString selectedFile = fileDialog.getOpenFileName(
      this, "Select a supported file", m_Path, "*.png *.jpeg *.jpg *.pdf");

  if (selectedFile.isEmpty() || selectedFile.isNull()) return false;

  QString mFileBaseName = QFileInfo(selectedFile).baseName().replace(" ", "_");
  QString mFileExtention = QFileInfo(selectedFile).completeSuffix();

  QString mCopytoPath = QString("data/media/%1/").arg(this->ID);
  QString mLocalFilePath =
      QString("%1%2_%3.%4").arg(mCopytoPath, invName, dt, mFileExtention);

  QImage mImg;
  QDir mediaDir(mCopytoPath);

  if (mFileExtention.compare("pdf", Qt::CaseInsensitive) /* not PDF */ &&
      mImg.load(selectedFile) /* image is valid*/) {
    mediaDir.mkpath("./");

    QFile::copy(selectedFile, mLocalFilePath);

    invModel->item(row, 3)->setText(mLocalFilePath);

    if (setState)
      invModel->item(row, 6)->setText(
          QString::number(InvestModel::InvestigationsStates::hasMedia));

    invModel->item(row, 5)->setText(
        QString::number(QTime::currentTime().msecsSinceStartOfDay() / 1000));
    invModel->item(row, 1)->setToolTip(
        invIconHelper::getInvestigationTooltip(mLocalFilePath, invName, scale));

    setModel(invModel);

    saveInvestigation(ID, visitJulianDate, visitTime);

    emit popUpMessage(
        "Information",
        QString("Image file has been added to patient's file as [%1].")
            .arg(invName));

    int reply = msgbox.question(this, "Alert!",
                                "Do you Agree to delete source image file "
                                "after adding to patient profile?",
                                QMessageBox::Yes, QMessageBox::No);

    if (reply == QMessageBox::Yes) QFile::remove(selectedFile);

    reg.setValue("lastFolder", QFileInfo(selectedFile).path());
    return true;
  } else if (!mFileExtention.compare("pdf", Qt::CaseInsensitive) /* is PDF */) {
    mediaDir.mkpath("./");

    QFile::copy(selectedFile, mLocalFilePath);

    invModel->item(row, 3)->setText(mLocalFilePath);

    if (setState)
      invModel->item(row, 6)->setText(
          QString::number(InvestModel::InvestigationsStates::hasMedia));

    invModel->item(row, 5)->setText(
        QString::number(QTime::currentTime().msecsSinceStartOfDay() / 1000));
    invModel->item(row, 1)->setToolTip(invName);

    setModel(invModel);

    saveInvestigation(ID, visitJulianDate, visitTime);

    emit popUpMessage(
        "Information",
        QString("PDF file has been added to patient's file as [%1].")
            .arg(invName));

    int reply = msgbox.question(this, "Alert!",
                                "Do you Agree to delete source PDF file after "
                                "adding to patient profile?",
                                QMessageBox::Yes, QMessageBox::No);

    if (reply == QMessageBox::Yes) QFile::remove(selectedFile);

    reg.setValue("lastFolder", QFileInfo(selectedFile).path());
    return true;
  } else {
    emit popUpMessage("Warning", "File selected is invalid format.");
  }
  return false;
}

void investTable::tweakInveMedia() {
  if (working) return;
  int rows = invModel->rowCount();
  QString mediaFile, invName;
  QStandardItem *item;
  QStringList paidServices = sqlextra->getPaidServicesList();
  for (int r = 0; r < rows; r++) {
    item = invModel->item(r, 6);
    invName = invModel->item(r, 1)->text();
    mediaFile = invModel->item(r, 3)->text();
    QFile mf(mediaFile);

    if (!paidServices.contains(invName) && !mf.exists() &&
        item->text() !=
            QString::number(InvestModel::InvestigationsStates::normal) &&
        item->text() !=
            QString::number(InvestModel::InvestigationsStates::nonPrintable)) {
      item->setText(QString::number(InvestModel::InvestigationsStates::normal));
      invModel->item(r, 3)->setText("");
      save();
    }

    if (item->text() ==
        QString::number(
            InvestModel::InvestigationsStates::normal))  // generic
                                                         // investigation
    {
      invModel->setData(invModel->index(r, 1), QVariant(QBrush(Qt::black)),
                        Qt::ForegroundRole);
      invModel->item(r, 1)->setFont(printableFont);
    } else if (item->text() ==
               QString::number(
                   InvestModel::InvestigationsStates::
                       hasMedia))  // this investigation has a saved media file
    {
      invModel->setData(invModel->index(r, 1), QVariant(QBrush(Qt::blue)),
                        Qt::ForegroundRole);
      invModel->item(r, 1)->setFont(nonPrintableFont);
    } else if (item->text() ==
               QString::number(InvestModel::InvestigationsStates::
                                   isPaid))  // this investigation is paid
    {
      invModel->setData(invModel->index(r, 1), QVariant(QBrush(Qt::red)),
                        Qt::ForegroundRole);
      invModel->item(r, 1)->setFont(serviceFont);
    } else if (item->text() ==
               QString::number(InvestModel::InvestigationsStates::
                                   wasPaid))  // this investigation (was) paid
    {
      invModel->setData(invModel->index(r, 1), QVariant(QBrush(Qt::magenta)),
                        Qt::ForegroundRole);
      invModel->item(r, 1)->setFont(serviceFont);
    } else if (item->text() ==
               QString::number(
                   InvestModel::InvestigationsStates::
                       nonPrintable))  // this investigation non printable
    {
      invModel->item(r, 1)->setFont(nonPrintableFont);
    } else if (item->text() ==
               QString::number(
                   InvestModel::InvestigationsStates::
                       PrintableWithMedia))  // this investigation  printable
                                             // and has media
    {
      invModel->setData(invModel->index(r, 1), QVariant(QBrush(Qt::blue)),
                        Qt::ForegroundRole);
      invModel->item(r, 1)->setFont(printableFont);
    }
  }

  setModel(invModel);
}

void investTable::loadInvestigations() {
  invModel = future.result();
  createTooltips(invModel);

  setModel(invModel);
  tweakTable();

  timer->start();
  isModelLoaded = true;
}

void investTable::clearSelection() {
  emit toggleRemoveInvButton(false);
  zTableView::clearSelection();
}

void investTable::save() { saveInvestigation(ID, visitJulianDate, visitTime); }

void investTable::putToolTip() {
  invModel = tooltipFuture.result();

  setModel(invModel);

  emit togglePrintButton();

  if (hasFocus())
    emit selectLastInvRow();  // last selected if one is good for delete.
  working = false;
}

void investTable::toggleInvestaigationState(const int &state,
                                            const QModelIndex &cell) {
  if (state == InvestModel::InvestigationsStates::hasMedia) {
    invModel->item(cell.row(), 6)
        ->setText(QString::number(
            InvestModel::InvestigationsStates::PrintableWithMedia));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(getServicesCount(), item);
  } else if (state == InvestModel::InvestigationsStates::PrintableWithMedia) {
    invModel->item(cell.row(), 6)
        ->setText(QString::number(InvestModel::InvestigationsStates::hasMedia));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(getInvestigationCount(), item);
  } else if (state == InvestModel::InvestigationsStates::normal) {
    invModel->item(cell.row(), 6)
        ->setText(
            QString::number(InvestModel::InvestigationsStates::nonPrintable));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(getInvestigationCount(), item);
  } else if (state == InvestModel::InvestigationsStates::nonPrintable) {
    invModel->item(cell.row(), 6)
        ->setText(QString::number(InvestModel::InvestigationsStates::normal));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(getInvestigationCount(), item);
  } else if (state == InvestModel::InvestigationsStates::isPaid) {
    invModel->item(cell.row(), 6)
        ->setText(QString::number(InvestModel::InvestigationsStates::wasPaid));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(getServicesCount(), item);
  } else if (state == InvestModel::InvestigationsStates::wasPaid) {
    myMessageBox msgbox;
    QString selectedItem = invModel->item(cell.row(), 1)->text();
    QString message = QString(
                          "This will toggle <b>%1</b> calcuable for this "
                          "visit, Are you Sure?")
                          .arg(selectedItem);
    int reply = msgbox.question(this, "Alert!", message, QMessageBox::Yes,
                                QMessageBox::No);

    if (reply == QMessageBox::No) return;
    invModel->item(cell.row(), 6)
        ->setText(QString::number(InvestModel::InvestigationsStates::isPaid));
    invModel->item(cell.row(), 7)
        ->setText(QString::number(sqlextra->getPaidServicePrice(selectedItem)));
    QList<QStandardItem *> item = tableModel->takeRow(cell.row());
    tableModel->insertRow(0, item);
  }
  save();
  selectRow(cell.row());
}

void investTable::deleteInvMedia(QString &mediaURL, QModelIndex &cell,
                                 bool isService) {
  myMessageBox msgbox;
  QString selectedItem = invModel->item(cell.row(), 1)->text();
  QString message = QString(
                        "This Will <b>DELETE</b> media file for <b>%1</b> that "
                        "is located in [<b>%2</b>], Are you Sure?"
                        "<center> <i><b>This Can't be undone!</b></i></center>")
                        .arg(selectedItem)
                        .arg(mediaURL);
  int reply = msgbox.question(this, "Alert!", message, QMessageBox::Yes,
                              QMessageBox::No);

  if (reply == QMessageBox::No) return;

  if (!isService)
    invModel->item(cell.row(), 6)
        ->setText(QString::number(InvestModel::InvestigationsStates::normal));

  QString sstatic = QString();
  invModel->item(cell.row(), 3)->setText(QString(""));
  invModel->item(cell.row(), 1)
      ->setToolTip(
          invIconHelper::getInvestigationTooltip(sstatic, selectedItem, scale));
  clearSelection();
  save();
  sqlbase->deleteInvestigationMedia(mediaURL);
}

int investTable::getInvestigationCount()  // plus services
{
  int rows = invModel->rowCount();
  int state;
  int count = 0;
  for (int row = 0; row < rows; row++) {
    state = invModel->item(row, 6)->text().toInt();
    if (state == InvestModel::InvestigationsStates::nonPrintable ||
        state == InvestModel::InvestigationsStates::hasMedia)
      continue;
    else
      count += 1;
  }
  return count;
}

int investTable::getServicesCount() {
  int rows = invModel->rowCount();
  int state;
  int count = 0;
  for (int row = 0; row < rows; row++) {
    state = invModel->item(row, 6)->text().toInt();
    if (state == InvestModel::InvestigationsStates::isPaid ||
        state == InvestModel::InvestigationsStates::wasPaid)
      count += 1;
  }
  return count;
}

void investTable::createTooltips(InvestModel *m) {
  invTooltipWorker->setInvestigationsModel(m);
#if QT_VERSION >= 0x060000
  tooltipFuture =
      QtConcurrent::run(&wm_investTooltipLoader::Work, invTooltipWorker);
#else
  tooltipFuture =
      QtConcurrent::run(invTooltipWorker, &wm_investTooltipLoader::Work);
#endif
  tooltipWatcher.setFuture(tooltipFuture);
}

void investTable::keyPressEvent(QKeyEvent *e) {
  if (!isModelLoaded) {
    zTableView::keyPressEvent(e);
    return;
  }

  QModelIndex cell = selectionModel()->currentIndex();
  if (!cell.isValid()) {
    zTableView::keyPressEvent(e);
    return;
  }

  QString mediaURL = invModel->item(cell.row(), 3)->text();
  int state = invModel->item(cell.row(), 6)->text().toInt();

  if (e->key() == Qt::Key_Space && !isReadOnly) {
    toggleInvestaigationState(state, cell);
    zTableView::keyPressEvent(e);
    return;
  }

  if (mediaURL.isEmpty() || (!mediaURL.endsWith(".jpg", Qt::CaseInsensitive) &&
                             !img.load(mediaURL))) {
    zTableView::keyPressEvent(e);
    return;
  }
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(mediaURL));
  }

  else if ((state != InvestModel::InvestigationsStates::normal ||
            state != InvestModel::InvestigationsStates::nonPrintable) &&
           e->key() == Qt::Key_Delete && !isReadOnly) {
    bool isService = false;
    if (state == InvestModel::InvestigationsStates::hasMedia ||
        state == InvestModel::InvestigationsStates::PrintableWithMedia)
      isService = false;
    else if (state == InvestModel::InvestigationsStates::isPaid ||
             state == InvestModel::InvestigationsStates::wasPaid)
      isService = true;
    deleteInvMedia(mediaURL, cell, isService);
  }
  zTableView::keyPressEvent(e);
}

void investTable::tweakTable() {
  horizontalHeader()->setHidden(true);
  verticalHeader()->setHidden(true);
  hideColumn(0);
  hideColumn(2);
  hideColumn(3);
  hideColumn(4);
  hideColumn(5);
  hideColumn(6);
  hideColumn(7);
  hideColumn(8);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  horizontalHeader()->setStretchLastSection(true);
}

void investTable::setPatientID(int id) { this->ID = id; }

InvestModel *investTable::getInvestigationsModel() { return invModel; }

void investTable::clearInvestigations() {
  timer->stop();
  invModel->removeRows(0, invModel->rowCount());
  invModel->clear();
  reset();
  setModel(invModel);
  timer->start();
}

QStringList investTable::getInvestigationsList() {
  int rows = invModel->rowCount();
  int state;
  QStringList investigations;
  for (int row = 0; row < rows; row++) {
    if (!invModel->hasIndex(row, 6)) return investigations;

    state = invModel->item(row, 6)->text().toInt();
    if (state == InvestModel::InvestigationsStates::normal ||
        state == InvestModel::InvestigationsStates::PrintableWithMedia)
      investigations << invModel->item(row, 1)->text();
  }
  return investigations;
}

bool investTable::printableInvestigationsExists() {
  return (getInvestigationsList().count() > 0);
}

bool investTable::isWorking() { return working; }

const qint64 investTable::getVisitTime() { return visitTime; }

const qint64 investTable::getVisitJulianDate() { return visitJulianDate; }

investTable::~investTable() {
  delete worker;
  delete invTooltipWorker;
  sqlbase->optimize();
  delete sqlbase;
  sqlextra->optimize();
  delete sqlextra;

  QSqlDatabase::removeDatabase("qt_sql_base_invstTable");
  QSqlDatabase::removeDatabase("qt_sql_extra_invstTable");

  delete invModel;
  delete timer;
}

bool investTable::eventFilter(QObject *o, QEvent *e) {
  if (!isModelLoaded) return zTableView::eventFilter(o, e);

  if ((o != this->viewport())) return zTableView::eventFilter(o, e);

  QModelIndex cell = selectionModel()->currentIndex();
  if (!cell.isValid()) return zTableView::eventFilter(o, e);

  QString mediaURL = invModel->item(cell.row(), 3)->text();
  int state = invModel->item(cell.row(), 6)->text().toInt();
  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
  QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);

  if (e->type() == QEvent::MouseButtonDblClick) {
    if (((mouseEvent->button() == Qt::LeftButton &&
          keyEvent->modifiers() != Qt::CTRL &&
          keyEvent->modifiers() == Qt::SHIFT &&
          keyEvent->modifiers() != Qt::ALT) ||
         mouseEvent->button() == Qt::MiddleButton) &&
        !isReadOnly) {
      toggleInvestaigationState(state, cell);
    } else if ((state != InvestModel::InvestigationsStates::normal ||
                state != InvestModel::InvestigationsStates::nonPrintable) &&
               mouseEvent->button() == Qt::LeftButton &&
               keyEvent->modifiers() == Qt::CTRL &&
               keyEvent->modifiers() != Qt::SHIFT &&
               keyEvent->modifiers() != Qt::ALT &&
               (((mediaURL.endsWith(".jpg", Qt::CaseInsensitive) ||
                  mediaURL.endsWith(".jpeg", Qt::CaseInsensitive) ||
                  mediaURL.endsWith(".png", Qt::CaseInsensitive)) &&
                 img.load(mediaURL)) ||
                mediaURL.endsWith(".pdf", Qt::CaseInsensitive)) &&
               !isReadOnly) {
      bool isService = false;
      if (state == InvestModel::InvestigationsStates::hasMedia ||
          state == InvestModel::InvestigationsStates::PrintableWithMedia)
        isService = false;
      else if (state == InvestModel::InvestigationsStates::isPaid ||
               state == InvestModel::InvestigationsStates::wasPaid)
        isService = true;
      deleteInvMedia(mediaURL, cell, isService);
    } else if ((state != InvestModel::InvestigationsStates::hasMedia ||
                state !=
                    InvestModel::InvestigationsStates::PrintableWithMedia) &&
               mouseEvent->button() == Qt::LeftButton &&
               keyEvent->modifiers() == Qt::CTRL &&
               keyEvent->modifiers() != Qt::SHIFT &&
               keyEvent->modifiers() != Qt::ALT && mediaURL.isEmpty() &&
               !isReadOnly) {
      bool ss = false;
      if (state == InvestModel::InvestigationsStates::isPaid ||
          state == InvestModel::InvestigationsStates::wasPaid)
        ss = false;
      else if (state == InvestModel::InvestigationsStates::normal ||
               state == InvestModel::InvestigationsStates::nonPrintable)
        ss = true;
      addInvMedia(ss);
    } else if ((mouseEvent->button() == Qt::LeftButton &&
                keyEvent->modifiers() != Qt::SHIFT) &&
               keyEvent->modifiers() != Qt::CTRL &&
               keyEvent->modifiers() != Qt::ALT) {
      if ((mediaURL.endsWith(".jpg", Qt::CaseInsensitive) ||
           mediaURL.endsWith(".jpeg", Qt::CaseInsensitive) ||
           mediaURL.endsWith(".png", Qt::CaseInsensitive)) &&
          img.load(mediaURL)) {
        if (settings.isUseNativePhotoViewer()) {
          QVector<QVector<QString> > vector = invModel->getMediaVector();
          int index = vector.at(1).indexOf(mediaURL);
          requestViewer.setRequests(vector, index);
          requestViewer.exec();
        } else {
          QDesktopServices::openUrl(QUrl::fromLocalFile(mediaURL));
        }

      } else if (mediaURL.endsWith(".pdf", Qt::CaseInsensitive)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(mediaURL));
      }
    }
  }

  clearSelection();
  togglePrintButton();
  return zTableView::eventFilter(o, e);
}
