#ifndef THEMERENAMER_H
#define THEMERENAMER_H

#include <QDialog>

namespace Ui {
class ThemeRenamer;
}

class ThemeRenamer : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeRenamer(bool& ok, QString& name,QStringList &themes, QWidget *parent = nullptr);
    ~ThemeRenamer();


private slots:
    void on_btn_Cancel_clicked();
    void on_btn_Ok_clicked();

    void on_inputThemeName_textChanged(const QString &arg1);

private:
    Ui::ThemeRenamer *ui;
    bool& Ok;
    QStringList & Themes;
    QString& Name;
};

#endif // THEMERENAMER_H
