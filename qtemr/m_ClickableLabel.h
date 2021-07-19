// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef M_CLICKABLELABEL_H
#define M_CLICKABLELABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>


class m_ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit m_ClickableLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit m_ClickableLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    void setPhoneNumber(QString &p);
    QString getPhoneNumber();
private:
    QString phoneNumber="";
signals:
    void setFontBold(bool b);
    void leftMouseButtonClicked();

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // M_CLICKABLELABEL_H
