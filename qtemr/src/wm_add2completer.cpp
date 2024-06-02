// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_add2completer.h"

#include "qregularexpression.h"

wm_add2Completer::wm_add2Completer(QObject *parent)
    : QObject(parent),
      connectionName(QString("qt_sql_extra_add2Completer_%1_%2")
                         .arg(QRandomGenerator::global()->bounded(0, 9999999))
                         .arg(QTime::currentTime().msecsSinceStartOfDay())),
      sqlextra(new sqlExtra(this, connectionName, false)) {}

wm_add2Completer::~wm_add2Completer() {
  sqlextra->optimize();
  delete sqlextra;
  QSqlDatabase::removeDatabase(connectionName);
}

void wm_add2Completer::setVisitData(const sqlBase::Visit &v) { visit = v; }

void wm_add2Completer::setPatientData(const sqlBase::Patient &p) {
  patient = p;
}

void wm_add2Completer::setHusband(QString h) { husband = h; }

void wm_add2Completer::setMode(bool b) { autocompletebyword = b; }

void wm_add2Completer::save2Dict(QStringList dict) { saveDicts(dict); }

void wm_add2Completer::vWork() {
  if (autocompletebyword) {
    QStringList complaints =
        visit.presentation.split(QRegularExpression("\\s"), Qt::SkipEmptyParts);
    foreach (QString c, complaints) {
      if (c.length() > 2) sqlextra->addToAutoComplete("complaints", c);
    }

    QStringList diagnoses =
        visit.diagnosis.split(QRegularExpression("\\s"), Qt::SkipEmptyParts);
    foreach (QString d, diagnoses) {
      if (d.length() > 2) sqlextra->addToAutoComplete("diagnoses", d);
    }
  } else {
    QString complaint = visit.presentation;
    QString diagnoses = visit.diagnosis;
    sqlextra->addToAutoComplete("complaints", complaint);
    sqlextra->addToAutoComplete("diagnoses", diagnoses);
  }

  QStringList dicts = QStringList()
                      << visit.presentationAnalysis << visit.invResults
                      << visit.exGeneral << visit.exChestHeart
                      << visit.exAbdback << visit.exLL << visit.visitNotes
                      << visit.pelvicExam << visit.ObstUS;

  saveDicts(dicts);
  emit finished();
}

void wm_add2Completer::pWork() {
  QStringList dicts = QStringList()
                      << patient.pastHistory << patient.familyHistory
                      << patient.notes << husband;
  saveDicts(dicts);
  sqlextra->addToAutoComplete("places", patient.residence);
  sqlextra->addToAutoComplete("placeOfBirth", patient.birthPlace);
  sqlextra->addToAutoComplete("jobs", patient.occupation);
  emit finished();
}

void wm_add2Completer::saveDicts(const QStringList &dicts) {
  foreach (QString d, dicts) {
    foreach (QString w, splitDict(d)) {
      // mDebug() <<  w << (w.length() > 2)  <<
      // !w.contains(QRegularExpression("^(\\d+)")) <<
      // !w.contains(QRegularExpression("(\\d+)$"));
      w.remove(QRegularExpression(
          QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"]")));
      if (w.length() > 2 && !w.contains(QRegularExpression("^(\\d+)")) &&
          !w.contains(QRegularExpression("(\\d+)$")))
        sqlextra->addToAutoComplete("dictionary", w);
    }
  }
}

QStringList wm_add2Completer::splitDict(const QString &dict) {
  QString plainText = dataHelper::cleanHTML(dict);
  return plainText.split(QRegularExpression("[\r\n\t ]+"), Qt::SkipEmptyParts);
}
