// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef STYLEWIDGET_H
#define STYLEWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include "themerenamer.h"
#include "dataiohelper.h"
#include "mstyler.h"

namespace Ui {
class StyleWidget;
}

class StyleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StyleWidget(QWidget *parent = nullptr);
    mStyler::Style getStyle();
    void putStyle(const mStyler::Style &style);
    void setSelectedTheme(const QString& theme);
    QString getSelectedTheme();
    ~StyleWidget();
    bool save();

private:
    Ui::StyleWidget *ui;
    mStyler styler;
    QString selected_theme;
    mStyler::Style loadedStyle;
    QFileSystemModel themeWatcher;
    QStringList packagedThemes;
    int packagedThemes_count;
    QString path;


protected:

private slots:
    void on_Styles_activated(int index);
    void themesListMaker(QModelIndex, int, int);
    void on_Styles_currentTextChanged(const QString &arg1);
    void on_btn_save_as_clicked();
    void on_btn_Delete_clicked();
    void on_btn_apply_clicked();
signals:
    void applyTheme();
    void saveSelectedTheme(QString t);
};

#endif // STYLEWIDGET_H
