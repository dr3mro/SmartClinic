#include "mymessagebox.h"

myMessageBox::myMessageBox(QWidget *parent) : mMessageBox(parent) {
}

int myMessageBox::question(QWidget *parent, const QString &title,
                           const QString &text,
                           const StandardButton button0,
                           const StandardButton button1,
                           bool DefaultNo)
{
    messagebox = new mMessageBox(this);
    messagebox->setParent(parent);
    messagebox->setWindowFlags( this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint );;
    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->addButton(button0);
    messagebox->addButton(button1);
    messagebox->setIcon(QMessageBox::Icon::Question);

    QCheckBox cb;
    cb.setText("Yes, I am sure.");
    if(DefaultNo)
    {
        QAbstractButton *b = (QAbstractButton*) messagebox->buttons().at(0);
        QObject::connect(&cb,SIGNAL(toggled(bool)),b,SLOT(setEnabled(bool)));
        b->setEnabled(false);
        messagebox->setDefaultButton(button1);
        messagebox->setCheckBox(&cb);

    }

    messagebox->deleteLater();
    return messagebox->exec();

}
int myMessageBox::question(QWidget *parent,
                           const QString &title,
                           const QString &text,
                           StandardButton button0,
                           StandardButton button1,
                           StandardButton button2)
{
    messagebox = new mMessageBox(this);
    messagebox->setParent(parent);
    messagebox->setWindowFlags( this->windowFlags() | Qt::WindowStaysOnTopHint |  Qt::FramelessWindowHint );
    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->addButton(button0);
    messagebox->addButton(button1);
    messagebox->addButton(button2);
    messagebox->setIcon(QMessageBox::Icon::Question);
    messagebox->deleteLater();
    return messagebox->exec();
}

int myMessageBox::information(QWidget *parent, const QString &title, const QString &text)
{
    messagebox = new mMessageBox(this);
    messagebox->setParent(parent);
    messagebox->setWindowFlags( this->windowFlags() | Qt::WindowStaysOnTopHint |  Qt::FramelessWindowHint );
    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->setIcon(QMessageBox::Icon::Information);
    messagebox->deleteLater();
    return messagebox->exec();
}
