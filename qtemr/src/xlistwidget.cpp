// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "xlistwidget.h"

xListWidget::xListWidget(QWidget *parent) //-V730
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
    connect(this,SIGNAL(popUpMessage(QString,QString)),parent->window(),SLOT(popUpMessage(QString,QString)));
    connect(this,SIGNAL(afterAddItemxListWidget(QString,QString)),parent->window(),SLOT(afterAddItemxListWidget(QString,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(selectedRowChanged()));
    connect( parent->window(),SIGNAL(updateTextFont()),this,SLOT(setDefaultFont()));
}

void xListWidget::setListVariables(QString ln)
{
    listName = ln;
}

void xListWidget::addItem(const QString &label)
{
    QString newItemText=label;

    if ( label.isEmpty())
        return;

    for ( int i = 0 ; i < count() ; i++)
    {
        QString itemText = item(i)->text().simplified();
        if ( itemText.toUpper() == newItemText.toUpper() )
        {
            emit popUpMessage("Warning",QString("%1 already exists,Please Recheck!").arg(newItemText));
            return;
        }
    }

    QListWidget::addItem(newItemText.simplified());
    emit afterAddItemxListWidget(listName,newItemText);
}

void xListWidget::makeReadWrite(bool rw)
{
    clearSelection();
    pEditingMode = rw;
}

void xListWidget::selectedRowChanged()
{
    emit enableItemRemoveButton(pEditingMode);
}

void xListWidget::setDefaultFont()
{
    mSettings::defaultFont defaultfont = settings.getDefaultFont();
    QFont defaultFont = QFont(defaultfont.fontName);
    int defaultPointSize = static_cast<int>(defaultfont.fontSize);
    bool defaultBold = defaultfont.fontBold;
    defaultFont.setBold(defaultBold);
    defaultFont.setPointSize(defaultPointSize);
    setFont(defaultFont);
}
