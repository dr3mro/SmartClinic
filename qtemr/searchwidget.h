#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QValidator>

namespace Ui {
class searchWidget;
}

class searchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit searchWidget(QWidget *parent = nullptr);
    void selectRow(int row);
    void clearFilter();
    void closeDatabase();
    void reConnectDatabase();
    void toggleListHeader(bool visible);
    ~searchWidget();
public slots:
    void setFilter(int fc_);
    void showHideFilters(bool checked);
    void updatePatientList();
    void focusFilter();
    void focusList();
    void setID(int ID);

private slots:
    void on_filterLineEdit_textChanged(const QString &arg1);
    void on_filterByNameRadio_toggled(bool checked);
    void on_filterByIDRadio_toggled(bool checked);
    void on_filterByMobileRadio_toggled(bool checked);
    void on_filterLineEdit_returnPressed();
    void on_PatientListTableView_activated(const QModelIndex &index);
    void on_fuzzyCheckBox_clicked(bool checked);

private:
    Ui::searchWidget *ui;
    void filterToggled();
    bool filtersVisibility=false;
    bool isFuzzySearchEnabled=true;
    QRegExpValidator validator;

signals:
    void loadPatient();
    void loadPatient(int);
    void updatePatients();
    void closePatientList();

};

#endif // SEARCHWIDGET_H
