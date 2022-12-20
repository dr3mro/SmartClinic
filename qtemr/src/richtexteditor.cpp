// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "richtexteditor.h"
#include "ui_richtexteditor.h"

richTextEditor::richTextEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::richTextEditor)
{
    ui->setupUi(this);
    timeout = new QTimer(this);
    fade = new QTimer(this);
    timeout->setInterval(3000);
    ui->point->setCurrentIndex(1);
    this->setWindowFlags(Qt::Popup);
    this->setWindowOpacity(0.50);
    cp1 = new colorPicker(this);
    cp2 = new colorPicker(this);
    ui->textColor->setColor(Qt::black);
    ui->backgroundColor->setColor(Qt::white);

    connect(ui->textColor,SIGNAL(leftButtonClicked()),cp1,SLOT(show()),Qt::QueuedConnection);
    connect(ui->textColor,SIGNAL(midButtonClicked(const QColor&)),this,SLOT(setForegroundColor(const QColor&)),Qt::QueuedConnection);
    connect(ui->backgroundColor,SIGNAL(leftButtonClicked()),cp2,SLOT(show()),Qt::QueuedConnection);
    connect(ui->backgroundColor,SIGNAL(midButtonClicked(const QColor&)),this,SLOT(setBackgroundColor(const QColor&)),Qt::QueuedConnection);


    connect(cp1,SIGNAL(newColor(const QColor&)),this,SLOT(setForegroundColor(const QColor&)),Qt::QueuedConnection);
    connect(cp1,SIGNAL(newColor(const QColor&)),ui->textColor,SLOT(setColor(const QColor&)),Qt::QueuedConnection);
    connect(cp2,SIGNAL(newColor(const QColor&)),this,SLOT(setBackgroundColor(const QColor&)),Qt::QueuedConnection);
    connect(cp2,SIGNAL(newColor(const QColor&)),ui->backgroundColor,SLOT(setColor(const QColor&)),Qt::QueuedConnection);

    connect(ui->fontComboBox,SIGNAL(currentFontChanged(QFont)),parent,SLOT(setFont(QFont)),Qt::QueuedConnection);
    connect(ui->fontComboBox,SIGNAL(textHighlighted(const QString &)),parent,SLOT(setFont(const QString &)),Qt::QueuedConnection);
    connect(ui->fontComboBox,SIGNAL(activated(int)),this,SLOT(reGainFocus()),Qt::QueuedConnection);
    connect(ui->point,SIGNAL(currentTextChanged(QString)),parent,SLOT(setPoint(QString)),Qt::QueuedConnection);
    connect(ui->point,SIGNAL(textHighlighted(QString)),parent,SLOT(setPoint(QString)),Qt::QueuedConnection);
    connect(ui->point,SIGNAL(activated(int)),this,SLOT(reGainFocus()),Qt::QueuedConnection);
    connect(ui->bold,SIGNAL(toggled(bool)),parent,SLOT(setBold(bool)),Qt::QueuedConnection);
    connect(ui->toUpper,SIGNAL(toggled(bool)),parent,SLOT(setUpper(bool)),Qt::QueuedConnection);
    connect(ui->italic,SIGNAL(toggled(bool)),parent,SLOT(setItalic(bool)),Qt::QueuedConnection);
    connect(ui->underline,SIGNAL(toggled(bool)),parent,SLOT(underline(bool)),Qt::QueuedConnection);
    connect(ui->strike,SIGNAL(toggled(bool)),parent,SLOT(strike(bool)),Qt::QueuedConnection);
    connect(ui->highlight,SIGNAL(toggled(bool)),parent,SLOT(highLight(bool)),Qt::QueuedConnection);

    connect(ui->clearFormat,SIGNAL(clicked(bool)),parent,SLOT(reset()),Qt::QueuedConnection);
    connect(ui->clearFormat,SIGNAL(clicked(bool)),this,SLOT(resetFont()),Qt::QueuedConnection);
    connect(ui->clear,SIGNAL(clicked(bool)),parent,SLOT(deleteSelectedText()),Qt::QueuedConnection);
    connect(ui->SelectAll,SIGNAL(clicked(bool)),parent,SLOT(selectAll()),Qt::QueuedConnection);
    connect(ui->undo,SIGNAL(clicked(bool)),parent,SLOT(undo()),Qt::QueuedConnection);
    connect(ui->redo,SIGNAL(clicked(bool)),parent,SLOT(redo()),Qt::QueuedConnection);
    connect(parent,SIGNAL(undoAvailable(bool)),ui->undo,SLOT(setEnabled(bool)),Qt::QueuedConnection);
    connect(parent,SIGNAL(redoAvailable(bool)),ui->redo,SLOT(setEnabled(bool)),Qt::QueuedConnection);
    connect(this,SIGNAL(insertChar(QString)),parent,SLOT(insertChar(QString)),Qt::QueuedConnection);
    connect(ui->cut,SIGNAL(clicked(bool)),parent,SLOT(cut()),Qt::QueuedConnection);
    connect(ui->copy,SIGNAL(clicked(bool)),parent,SLOT(copy()),Qt::QueuedConnection);
    connect(ui->paste,SIGNAL(clicked(bool)),parent,SLOT(paste()),Qt::QueuedConnection);
    connect(this,SIGNAL(deleteText()),parent,SLOT(deleteSelectedText()),Qt::QueuedConnection);
    connect(ui->alignRight,SIGNAL(clicked(bool)),parent,SLOT(alignRight()),Qt::QueuedConnection);
    connect(ui->alignCenter,SIGNAL(clicked(bool)),parent,SLOT(alignCenter()),Qt::QueuedConnection);
    connect(ui->alignLeft,SIGNAL(clicked(bool)),parent,SLOT(alignLeft()),Qt::QueuedConnection);
    connect(timeout,SIGNAL(timeout()),this,SLOT(fadeout()),Qt::QueuedConnection);
    connect(timeout,SIGNAL(timeout()),timeout,SLOT(stop()),Qt::QueuedConnection);
    connect(ui->fontComboBox,SIGNAL(highlighted(int)),this,SLOT(noFadeOut()),Qt::QueuedConnection);
    connect(ui->point,SIGNAL(highlighted(int)),this,SLOT(noFadeOut()),Qt::QueuedConnection);
    connect(ui->serachOnline,SIGNAL(clicked()),this,SLOT(searchGoogle()),Qt::QueuedConnection);
    connect(this,SIGNAL(setPointPlusOne()),parent,SLOT(setPointPlusOne()),Qt::QueuedConnection);
    connect(this,SIGNAL(setPointMinusOne()),parent,SLOT(setPointMinusOne()),Qt::QueuedConnection);
    connect(this,SIGNAL(redFlagHighLight()),parent,SLOT(redFlagHighLight()),Qt::QueuedConnection);
    connect(this,SIGNAL(greenFlagHighLight()),parent,SLOT(greenFlagHighLight()),Qt::QueuedConnection);
    connect(this,SIGNAL(blueFlagHighLight()),parent,SLOT(blueFlagHighLight()),Qt::QueuedConnection);

    connect(fade,SIGNAL(timeout()),this,SLOT(decreaseOpacity()),Qt::QueuedConnection);

    installEventFilter(this);
}

void richTextEditor::syncFontPoint(QString font, int point, bool bold, bool italic, bool underLine, bool strike, bool highlight, bool alignLeft, bool alignCenter, bool alignRight, bool upper)
{
    if ( font != "" )
    {
        ui->fontComboBox->setCurrentFont(QFont(font));
    }
    ui->point->setCurrentText(QString::number(point));

    ui->bold->setChecked(bold);
    ui->italic->setChecked(italic);
    ui->underline->setChecked(underLine);
    ui->strike->setChecked(strike);
    ui->highlight->setChecked(highlight);
    ui->alignLeft->setChecked(alignLeft);
    ui->alignCenter->setChecked(alignCenter);
    ui->alignRight->setChecked(alignRight);
    ui->toUpper->setChecked(upper);
}

richTextEditor::~richTextEditor()
{ 
    removeEventFilter(this);
    delete cp1;
    delete cp2;
    delete fade;
    delete timeout;
    delete ui;
}

void richTextEditor::setBackgroundColor(const QColor &color)
{
    emit setBGcolor(color);
}

void richTextEditor::setForegroundColor(const QColor &color)
{
    emit setFGcolor(color);
}

void richTextEditor::resetFont()
{
    mSettings& settings = mSettings::instance();
    mSettings::defaultFont defaultfont = settings.getDefaultFont();

    QFont defaultFont = QFont(defaultfont.fontName);
    double defaultFontPoint = defaultfont.fontSize;
    bool defaultBold = defaultfont.fontBold;

    ui->fontComboBox->setCurrentFont(defaultFont);
    ui->point->setCurrentText(QString::number(defaultFontPoint));

    ui->bold->toggle();
    ui->bold->setChecked(defaultBold);

    ui->italic->setChecked(false);
    ui->underline->setChecked(false);
    ui->strike->setChecked(false);
    ui->highlight->setChecked(false);
    ui->toUpper->setChecked(false);

}

void richTextEditor::fadeout()
{
    fade->setInterval(100);
    fade->start();
}

void richTextEditor::decreaseOpacity()
{
    setWindowOpacity(this->windowOpacity()-0.05);
    if (windowOpacity() == qreal(0.00))
    {
        hide();
        setWindowOpacity(1.00);
        fade->stop();
        timeout->stop();
    }

}

void richTextEditor::noFadeOut()
{

    setWindowOpacity(1.0);
    fade->stop();
    timeout->stop();

}

void richTextEditor::reGainFocus()
{
    this->setFocus(Qt::OtherFocusReason);
}

void richTextEditor::searchGoogle()
{
    QString selected_text = emit getSelectedText();
    QString engineUrl = "https://scholar.google.com.eg/scholar?q=%1";
    QString url = QString(engineUrl).arg(selected_text);
    QDesktopServices::openUrl(QUrl(url));
}

void richTextEditor::mouseMoveEvent(QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    move(event->globalPosition().toPoint() - QPoint(x_cord,y_cord));
#else
    move( event->globalX() - x_cord , event->globalY() - y_cord );
#endif

    QWidget::mouseMoveEvent(event);
}

void richTextEditor::mousePressEvent(QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    x_cord = event->pos().x();
    y_cord = event->pos().y();
#else
    x_cord = event->x();
    y_cord = event->y();
#endif
    QWidget::mousePressEvent(event);
}

void richTextEditor::keyPressEvent(QKeyEvent *event)
{   
    setWindowOpacity(1.00);
    timeout->stop();
    fade->stop();

    bool isAltModifier = event->modifiers().testFlag(Qt::KeyboardModifier::AltModifier);
    bool isCTRLModifier = event->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier);
    bool isCTRL= (event->key() == Qt::Key_Control);


    if(isCTRL)
    {
        event->ignore();
        hide();
        return;
    }


    if(isAltModifier)
    {
        switch (event->key()) {
        case Qt::Key_Backslash:
            emit redFlagHighLight();
            return;
            break;
        case Qt::Key_Slash:
            emit greenFlagHighLight();
            return;
            break;
        case Qt::Key_Bar:
            emit blueFlagHighLight();
            return;
            break;
        default:
            event->ignore();
            return;
            break;
        }
    }

    switch (event->key())
    {
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Down:
    case Qt::Key_Up:
        hide();
        break;
    case Qt::Key_Control:
    case Qt::Key_Escape:
    case Qt::Key_Tab:
    case Qt::Key_Backtab:
    case Qt::Key_CapsLock:
    case Qt::Key_Shift:
    case Qt::Key_Alt:
    case Qt::Key_Insert:
    case Qt::Key_Home:
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
    case Qt::Key_End:
    case Qt::Key_F1:
    case Qt::Key_F2:
    case Qt::Key_F3:
    case Qt::Key_F4:
    case Qt::Key_F5:
    case Qt::Key_F6:
    case Qt::Key_F7:
    case Qt::Key_F8:
    case Qt::Key_F9:
    case Qt::Key_F10:
    case Qt::Key_F11:
    case Qt::Key_F12:
    case Qt::Key_Menu:
    case Qt::Key_VolumeDown:
    case Qt::Key_VolumeUp:
    case Qt::Key_VolumeMute:
    case Qt::Key_Play:
    case Qt::Key_Pause:
    case Qt::Key_AudioForward:
    case Qt::Key_AudioRewind:
    case Qt::Key_AudioRepeat:
    case Qt::Key_BrightnessAdjust:
    case Qt::Key_unknown:
        event->ignore();
        break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        hide();
        emit deleteText();
        break;
    default:
        if(!isAltModifier && !isCTRLModifier)
        {
            emit insertChar(event->text());
            hide();
        }
        break;
    }

    QWidget::keyPressEvent(event);
}

void richTextEditor::keyReleaseEvent(QKeyEvent *event)
{
    bool isSHIFT = (event->key() == Qt::Key_Shift);
    if(isSHIFT)
    {
        hide();
        emit clearSelection();
    }
    QWidget::keyPressEvent(event);
}

bool richTextEditor::eventFilter(QObject *o, QEvent *e)
{

    if ( cp1->isVisible()|| cp2->isVisible())
        return QWidget::eventFilter(o,e);

    if (e->type() == QEvent::Enter)
    {
        setWindowOpacity(1.00);
        timeout->stop();
        fade->stop();
    }
    if (e->type() == QEvent::Leave)
    {
        setWindowOpacity(0.50);
        timeout->start();
    }
    return QWidget::eventFilter(o,e);
}
