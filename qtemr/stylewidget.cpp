#include "stylewidget.h"
#include "ui_stylewidget.h"

StyleWidget::StyleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleWidget)
{
    ui->setupUi(this);

    path = QString("%1\\themes").arg(dataIOhelper::getCurrentFolder());
    themeWatcher.setRootPath(path);

    connect(&themeWatcher,SIGNAL(rowsInserted(QModelIndex,int,int)),
            this,SLOT(themesListMaker(QModelIndex,int,int)));
    connect(&themeWatcher,SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this,SLOT(themesListMaker(QModelIndex,int,int)));

    packagedThemes = styler.getPackagedThemes();
    packagedThemes_count = packagedThemes.count();
    ui->Styles->addItems(packagedThemes);
}

mStyler::Style StyleWidget::getStyle()
{
    mStyler::Style style;
    style.window = ui->windowStyleEditor->getStyle();
    style.subwindow = ui->subwindowStyleEditor->getStyle();
    style.button = ui->buttonStyleEditor->getStyle();
    style.input = ui->inputStyleEditor->getStyle();
    style.elementText = ui->elementTextStylesEditor->getStyle();
    style.inputText = ui->inputTextStylesEditor->getStyle();
    style.list = ui->ListStylesEditor->getStyle();
    return style;
}

void StyleWidget::putStyle(const mStyler::Style &style)
{
    ui->windowStyleEditor->putStyle(style.window);
    ui->subwindowStyleEditor->putStyle(style.subwindow);
    ui->buttonStyleEditor->putStyle(style.button);
    ui->inputStyleEditor->putStyle(style.input);
    ui->elementTextStylesEditor->putStyle(style.elementText);
    ui->inputTextStylesEditor->putStyle(style.inputText);
    ui->ListStylesEditor->putStyle(style.list);
    ui->scrollArea->setDisabled(styler.getPackagedThemes().contains(selected_theme));
}

void StyleWidget::setSelectedTheme(const QString &theme)
{
    ui->Styles->setCurrentText(theme);
    loadedStyle = styler.getStyle(selected_theme);
    putStyle(loadedStyle);
}


QString StyleWidget::getSelectedTheme()
{
    return selected_theme;
}

StyleWidget::~StyleWidget()
{
    delete ui;
}

bool StyleWidget::save()
{
    selected_theme = ui->Styles->currentText();

    if(styler.getPackagedThemes().contains(selected_theme) || selected_theme.isEmpty())
        return false;

    mStyler::Style currentStyle = getStyle();
    if((loadedStyle!=currentStyle))
    {
        styler.saveStyle(selected_theme,currentStyle);
        return true;
    }
    return false;
}

void StyleWidget::on_Styles_activated(const QString &arg1)
{
    selected_theme = arg1;
    putStyle(styler.getStyle(selected_theme));
}

void StyleWidget::themesListMaker(QModelIndex ,int,int)
{
    ui->Styles->clear();
    QString t = selected_theme;
    ui->Styles->addItems(styler.getPackagedThemes());
    ui->Styles->addItems(styler.getNonPackagedThemes());
    ui->Styles->setCurrentText(t);
}

void StyleWidget::on_Styles_currentTextChanged(const QString &arg1)
{
    if(arg1.length()==0)
        return;

    selected_theme = arg1;
    bool isPackagedTheme = (packagedThemes.contains(arg1));
    ui->btn_Delete->setDisabled(isPackagedTheme);
}

void StyleWidget::on_btn_save_as_clicked()
{
    bool Ok;
    QString Name;
    QStringList  themes = QStringList() << styler.getNonPackagedThemes() << styler.getPackagedThemes();
    ThemeRenamer themerenamer(Ok,Name,themes,this);
    themerenamer.exec();

    if (Ok && !Name.isEmpty())
    {
        selected_theme = Name;
        styler.saveStyle(selected_theme,getStyle());
        ui->scrollArea->setDisabled(styler.getPackagedThemes().contains(selected_theme));
    }
}

void StyleWidget::on_btn_Delete_clicked()
{
    int reply = QMessageBox::question(0,"Alert!",
                                      QString("Are you sure that you want to delete theme %1?").arg(selected_theme),
                                      QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::No)
        return;

    dataIOhelper::deleteFile(styler.getThemePath(selected_theme));
}

void StyleWidget::on_btn_apply_clicked()
{
    if(!styler.getPackagedThemes().contains(selected_theme))
        styler.saveStyle(selected_theme,getStyle());

    emit saveSelectedTheme(selected_theme);//save theme to settings.ini
    emit applyTheme();
}
