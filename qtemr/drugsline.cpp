#include "drugsline.h"

drugsLine::drugsLine(QWidget *parent):genericLineEdit(parent)
{
    favAction = addAction(QIcon(":/Graphics/expand"), QLineEdit::ActionPosition::TrailingPosition);
    favAction->setVisible(false);
    connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)),Qt::UniqueConnection);
    connect (parent->window(),SIGNAL(reloadCompleter()),this,SLOT(mUpdateCompleter()),Qt::UniqueConnection);
    connect (parent->window(),SIGNAL(loadCompleters()),this,SLOT(loadCompleter()),Qt::UniqueConnection);
    connect (this,SIGNAL(updateDrugsCompleter()),this,SLOT(loadCompleter()),Qt::UniqueConnection);
}

void drugsLine::loadCompleter()
{
    char delimterNone[] = "";

    delimeter = *delimterNone;
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    setToolTip("Middle mouse click or Shift + left click here to toggle between All \n"
               "drugs & Favourite drugs autocomplete modes - [CTRL+4] to focus");
    favouriteDrugs = reg.value(QString("enableFavourites_%1").arg(windowName)).toBool();
    if ( favouriteDrugs )
    {
         favAction->setVisible(true);
         setPlaceholderText("enter drug name here - Favourites");
         tableName = "favourites";
    }
    else
    {
        favAction->setVisible(false);
        setPlaceholderText("enter drug name here - All drugs");
        tableName = "drugs";
    }
    createCompleter();
}

void drugsLine::mousePressEvent(QMouseEvent *e)
{
    bool isSHiftModifier = e->modifiers().testFlag(Qt::KeyboardModifier::ShiftModifier);
    if (  (e->button() == Qt::MiddleButton || (e->button() == Qt::LeftButton && isSHiftModifier) ) && !isReadOnly() )
    {
        if ( !favouriteDrugs )
        {
             favAction->setVisible(true);
             setPlaceholderText("enter drug name here - Favourites");
             favouriteDrugs = true;
             mSetCompleter("favourites");
        }
        else
        {
            favAction->setVisible(false);
            favouriteDrugs = false;
            setPlaceholderText("enter drug name here - All drugs");
            mSetCompleter("drugs");
        }
        QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
        reg.setValue(QString("enableFavourites_%1").arg(windowName),favouriteDrugs);
    }

    QLineEdit::mousePressEvent(e);
}
