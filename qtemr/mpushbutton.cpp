#include "mpushbutton.h"

mPushButton::mPushButton(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void mPushButton::makeReadWrite(bool rw)
{
    if (objectName() == "buttonNewCancel")
    {
        if ( rw )
        {
            setText("&Cancel");
            setToolTip("<html><head/><body><p>Exit edit Mode</p><p>F8</p></body></html>");
            setShortcut(Qt::Key_F8);
            setIcon(QIcon(":/Graphics/ex"));
        }
        else
        {
            setText("&New");
            setToolTip("<html><head/><body><p>Create new patient</p><p>F8</p></body></html>");
            setShortcut(Qt::Key_F8);
            setIcon(QIcon(":/Graphics/person"));
        }

    }
    else if ( objectName() == "ButtonSaveEdit")
    {
        if ( rw )
        {
            setText("&Save");
            setToolTip("<html><head/><body><p>Save current patient</p><p>F5</p></body></html>");
            setShortcut(Qt::Key_F5);
            setIcon(QIcon(":/Graphics/arrow_bottom"));
        }
        else
        {
            setText("&Edit");
            setToolTip("<html><head/><body><p>Enter Edit Mode</p><p>F5</p></body></html>");
            setShortcut(Qt::Key_F5);
            setIcon(QIcon(":/Graphics/pencil"));
        }
    }

}
