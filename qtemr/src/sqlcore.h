#ifndef SQLCORE_H
#define SQLCORE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QStandardItemModel>
#include <QStringList>
#include <QtSql/QtSql>

#include "mdebug.h"
#include "msql.h"

class sqlCore : public msql {
  Q_OBJECT
 public:
  struct filters {
    QStringList categories;
    QStringList companies;
    QStringList forms;
  };
  explicit sqlCore(QObject *parent = nullptr,
                   QString connectionName = "qt_sql_core_connection");
  QStandardItemModel *getDrugsIndexModel(QStandardItemModel *model);
  QStandardItemModel *getFindDrugsModel(QStandardItemModel *model, QString col,
                                        QStringList filters);
  QStringListModel *getCoreDrugListModel();
  QStringList getCoreDrugList();
  QString getDrugDetail(QString tradeName, QString column);
  int getDrugsDatabaseVersion();
  filters getFilters();
  void closeDataBase();
  void updateDrugsDatabase();
  ~sqlCore();

 private:
  QStringListModel *drugModel;
  void processResponse(const QByteArray &response);
  void sendProgress(const QString &status);
  QNetworkAccessManager networkManager;

 signals:
  void drugsDatabaseUpdateFinished(bool success);
  void progress(const QString &status);

 private slots:
  void downloadProgress(qint64 a, qint64 b);
};

#endif  // SQLCORE_H
