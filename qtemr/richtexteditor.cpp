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

    connect(ui->textColor,SIGNAL(leftButtonClicked()),cp1,SLOT(show()));
    connect(ui->textColor,SIGNAL(midButtonClicked(QColor)),this,SLOT(setForegroundColor(QColor)));
    connect(ui->backgroundColor,SIGNAL(leftButtonClicked()),cp2,SLOT(show()));
    connect(ui->backgroundColor,SIGNAL(midButtonClicked(QColor)),this,SLOT(setBackgroundColor(QColor)));


    connect(cp1,SIGNAL(newColor(QColor)),this,SLOT(setForegroundColor(QColor)));
    connect(cp1,SIGNAL(newColor(QColor)),ui->textColor,SLOT(setColor(QColor)));
    connect(cp2,SIGNAL(newColor(QColor)),this,SLOT(setBackgroundColor(QColor)));
    connect(cp2,SIGNAL(newColor(QColor)),ui->backgroundColor,SLOT(setColor(QColor)));

    connect(ui->fontComboBox,SIGNAL(currentFontChanged(QFont)),parent,SLOT(setFont(QFont)));
    connect(ui->fontComboBox,SIGNAL(highlighted(QString)),parent,SLOT(setFont(QString)));
    connect(ui->fontComboBox,SIGNAL(activated(int)),this,SLOT(reGainFocus()));
    connect(ui->point,SIGNAL(currentTextChanged(QString)),parent,SLOT(setPoint(QString)));
    connect(ui->point,SIGNAL(highlighted(QString)),parent,SLOT(setPoint(QString)));
    connect(ui->point,SIGNAL(activated(int)),this,SLOT(reGainFocus()));
    connect(ui->bold,SIGNAL(toggled(bool)),parent,SLOT(setBold(bool)));
    connect(ui->toUpper,SIGNAL(toggled(bool)),parent,SLOT(setUpper(bool)));
    connect(ui->italic,SIGNAL(toggled(bool)),parent,SLOT(setItalic(bool)));
    connect(ui->underline,SIGNAL(toggled(bool)),parent,SLOT(underline(bool)));
    connect(ui->strike,SIGNAL(toggled(bool)),parent,SLOT(strike(bool)));
    connect(ui->highlight,SIGNAL(toggled(bool)),parent,SLOT(highLight(bool)));

    connect(ui->clearFormat,SIGNAL(clicked(bool)),parent,SLOT(reset()));
    connect(ui->clearFormat,SIGNAL(clicked(bool)),this,SLOT(resetFont()));
    connect(ui->clear,SIGNAL(clicked(bool)),parent,SLOT(deleteSelectedText()));
    connect(ui->SelectAll,SIGNAL(clicked(bool)),parent,SLOT(selectAll()));
    connect(ui->undo,SIGNAL(clicked(bool)),parent,SLOT(undo()));
    connect(ui->redo,SIGNAL(clicked(bool)),parent,SLOT(redo()));
    connect(parent,SIGNAL(undoAvailable(bool)),ui->undo,SLOT(setEnabled(bool)));
    connect(parent,SIGNAL(redoAvailable(bool)),ui->redo,SLOT(setEnabled(bool)));
    connect(this,SIGNAL(insertChar(QString)),parent,SLOT(insertChar(QString)));
    connect(ui->cut,SIGNAL(clicked(bool)),parent,SLOT(cut()));
    connect(ui->copy,SIGNAL(clicked(bool)),parent,SLOT(copy()));
    connect(ui->paste,SIGNAL(clicked(bool)),parent,SLOT(paste()));
    connect(this,SIGNAL(deleteText()),parent,SLOT(deleteSelectedText()));
    connect(ui->alignRight,SIGNAL(clicked(bool)),parent,SLOT(alignRight()));
    connect(ui->alignCenter,SIGNAL(clicked(bool)),parent,SLOT(alignCenter()));
    connect(ui->alignLeft,SIGNAL(clicked(bool)),parent,SLOT(alignLeft()));
    connect(timeout,SIGNAL(timeout()),this,SLOT(fadeout()));
    connect(timeout,SIGNAL(timeout()),timeout,SLOT(stop()));
    connect(ui->fontComboBox,SIGNAL(highlighted(int)),this,SLOT(noFadeOut()),Qt::QueuedConnection);
    connect(ui->point,SIGNAL(highlighted(int)),this,SLOT(noFadeOut()),Qt::QueuedConnection);
    connect(ui->serachOnline,SIGNAL(clicked()),this,SLOT(searchGoogle()));
    connect(this,SIGNAL(setPointPlusOne()),parent,SLOT(setPointPlusOne()));
    connect(this,SIGNAL(setPointMinusOne()),parent,SLOT(setPointMinusOne()));
    connect(this,SIGNAL(redFlagHighLight()),parent,SLOT(redFlagHighLight()));
    connect(this,SIGNAL(greenFlagHighLight()),parent,SLOT(greenFlagHighLight()));
    connect(this,SIGNAL(blueFlagHighLight()),parent,SLOT(blueFlagHighLight()));

    connect(fade,SIGNAL(timeout()),this,SLOT(decreaseOpacity()));

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

void richTextEditor::setBackgroundColor(QColor color)
{
    emit setBGcolor(color);
}

void richTextEditor::setForegroundColor(QColor color)
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
    if (windowOpacity() == 0.00)
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
    QString selected_text = getSelectedText();
    QString engineUrl = "https://scholar.google.com.eg/scholar?q=%1";
    QString url = QString(engineUrl).arg(selected_text);
    QDesktopServices::openUrl(QUrl(url));
}

void richTextEditor::mouseMoveEvent(QMouseEvent *event)
{
    move( event->globalX() - x_cord , event->globalY() - y_cord );
    QWidget::mouseMoveEvent(event);
}

void richTextEditor::mousePressEvent(QMouseEvent *event)
{
    x_cord = event->x();
    y_cord = event->y();
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
        emit hide();
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
        emit hide();
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
