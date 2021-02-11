// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) :
    QTextEdit(parent),
    model(new QStringListModel(this)),
    completar(new QCompleter(this)),
    parent(parent),
    worker(new wm_texteditCompleterLoader),
    WindowName(parent->window()->objectName())

{
    createRichTextToolBox();
    setDefaultFont();
    completar->setWidget(this);
    completar->setCompletionMode(QCompleter::PopupCompletion);
    completar->setCaseSensitivity(Qt::CaseInsensitive);
    connect(completar, SIGNAL(activated(QString)),this, SLOT(insertCompletion(QString)),Qt::UniqueConnection);
    connect(this,SIGNAL(selectionChanged()),this,SLOT(false2autoSelected()));

    if ( WindowName == "visitsBox")
        connect(parent->window(),SIGNAL(onVisitBoxClose()),completar->popup(),SLOT(hide()),Qt::UniqueConnection);

    completar->popup()->setAlternatingRowColors(true);

    if(WindowName!="printDrugs")
        setToolTip(QString("<html>"
                           "<h3><center>Please Read Me!</center></h3>"
                           "<table>"
                           "<tr><td>- [CTRL + 0] to insert ±</td></tr>"
                           "<tr><td>- [CTRL + .] to insert • </td><td>- [CTRL + +] to increase font size.</td></tr>"
                           "<tr><td>- [CTRL + ,] to insert ◾ </td><td>- [CTRL + -] to decrease font size.</td></tr>"
                           "<tr><td>- [CTRL + →] to insert → </td><td>- [CTRL + ↑] to insert ↑</td></tr>"
                           "<tr><td>- [CTRL + ←] to insert ← </td><td>- [CTRL + ↓] to insert ↓</td></tr>"
                           "<tr><td>- [ALT + /] to set Green flag.</td><td>- [ALT + |] to set Blue flag.</td></tr>"
                           "<tr><td>- [ALT + \\] to set Red flag.</td><td>- [CTRL + R][SHIFT+2SPACES] to reset formating.</td></tr>"
                           "</table></html>"));

    connect(&watcher,SIGNAL(finished()),this,SLOT(completerLoader()));
    connect(parent->window(),SIGNAL(loadCompleters()),this,SLOT(setCompleter()));
    connect(this,SIGNAL(selectionChanged()),this,SLOT(isSelectionChanged()));
    if ( WindowName == "MainWindow" || WindowName == "visitsBox")
    {
        connect (this,SIGNAL(removeItemFromCompleter(QString,int)),parent->window(),SLOT(removeItemFromDictionary(QString,int)));
        connect (parent->window(),SIGNAL(removeFromCompleter(int)),this,SLOT(removeFromCompleter(int)));
        connect(parent->window(),SIGNAL(updateTextFont()),this,SLOT(setDefaultFont()));
    }

    if ( WindowName == "addSiblings")
    {
        connect(parent->window(),SIGNAL(updateTextFont()),this,SLOT(setDefaultFont()));
        return;
    }

    if ( WindowName == "drugExapnder")
    {
        return;
    }
    if ( WindowName == "printDrugs" ||
         WindowName == "surgicalNoteEditor" ||
         WindowName == "DietEditor" )
        return;

    connect(parent->window(),SIGNAL(reloadCompleter()),this,SLOT(updateCompleter()));
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));

}

bool TextEdit::findRemoveText(QString text)
{
    moveCursor(QTextCursor::Start);
    if (find (QRegExp(QString("^%1:.*$").arg(text))))
    {
        textCursor().removeSelectedText();
        textCursor().deletePreviousChar();
        return true;
    }
    return false;
}

void TextEdit::setCompleter()
{
    future = QtConcurrent::run(worker,&wm_texteditCompleterLoader::work);
    watcher.setFuture(future);
}

void TextEdit::setFont(QFont font)
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setFont(font);
    fmt.setFontPointSize(pointSize);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setFont(QString font)
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setFont(QFont(font,pointSize));
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setPoint(QString p)
{
    pointSize = p.toInt();
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setFontPointSize(pointSize);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;

}

void TextEdit::setCurrentSize(int p)
{
    pointSize = p;
    isSelectionStyled=true;
}

void TextEdit::updateCompleter()
{
    setCompleter();
}

QCompleter *TextEdit::completer() const
{
    return completar;
}

void TextEdit::cleanCompleterMemory()
{
    model->removeRows(0,model->rowCount());
}

void TextEdit::setInkFont(QString font)
{
    inkFont = font;
}

void TextEdit::deleteSelectedText()
{
    QTextCursor tc = textCursor();
    tc.removeSelectedText();
    setTextCursor(tc);
    return;
}

void TextEdit::insertChar(QString str)
{
    QTextCursor tc = textCursor();
    QRegExp r("[\\n|\\r|\\s]");


    if ( r.exactMatch(str) || isSelectionStyled )
        tc.clearSelection();

    tc.insertText(str);
    setTextCursor(tc);
    needReset = true;
}

void TextEdit::makeEditable(bool b)
{
    setReadOnly(!b);
}

QString TextEdit::getSelectedText()
{
    return textCursor().selectedText();
}

void TextEdit::setPointPlusOne()
{
    setPoint(QString::number( ( pointSize >= 36 ) ? 36:pointSize+1));
    isSelectionStyled=true;
}

void TextEdit::setPointMinusOne()
{
    setPoint(QString::number( ( pointSize <= 8 ) ? 8:pointSize-1));
    isSelectionStyled=true;
}

void TextEdit::redFlagHighLight()
{
    setFlagHighLight(Qt::red);
    isSelectionStyled=true;
}

void TextEdit::greenFlagHighLight()
{
    setFlagHighLight(Qt::darkGreen);
    isSelectionStyled=true;
}

void TextEdit::blueFlagHighLight()
{
    setFlagHighLight(Qt::blue);
    isSelectionStyled=true;
}

void TextEdit::setFlagHighLight(QColor color)
{
    QTextCharFormat fmt;
    fmt.setBackground(color);
    fmt.setFontWeight(QFont::Bold);
    fmt.setForeground(Qt::white);
    fmt.setFontCapitalization(QFont::AllUppercase);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::clear()
{
    reset();
    isSelectionStyled = false;
    QTextEdit::clear();
}

void TextEdit::createRichTextToolBox()
{
    rt = new richTextEditor(this);
    connect(rt,SIGNAL(setFGcolor(QColor)),this,SLOT(setForegroundColor(QColor)));
    connect(rt,SIGNAL(setBGcolor(QColor)),this,SLOT(setBackgroundColor(QColor)));
    connect(rt,SIGNAL(getSelectedText()),this,SLOT(getSelectedText()));
    connect(rt,SIGNAL(clearSelection()),this,SLOT(clearSelection()));
}

void TextEdit::setDefaultFont()
{
    mSettings::textboxFont textboxFont = settings.getTextboxFont();
    defaultFont = QFont(textboxFont.fontName);
    DefaultPointSize = textboxFont.fontSize;
    defaultBold = textboxFont.fontBold;
    setStyleSheet(QString("QTextEdit{font:%1 %2pt \"%3\";}").arg(defaultBold? "bold":"").arg(DefaultPointSize).arg(defaultFont.toString()));
    setFont(defaultFont);
    setFontPointSize(DefaultPointSize);
    setFontWeight( ( defaultBold )? QFont::Bold:QFont::Normal);
    isSelectionStyled = false;
}

void TextEdit::completerLoader()
{
    model->setStringList(future.result());
    completar->setModel(model);
}

void TextEdit::removeFromCompleter(int row)
{
    model->removeRow(row);
}

void TextEdit::isSelectionChanged()
{
    isSelectionStyled=false;
}

void TextEdit::clearSelection()
{
    if(isAutoSelection)
    {
        QTextCursor tc = textCursor();
        tc.clearSelection();
        setTextCursor(tc);
    }
}

void TextEdit::false2autoSelected()
{
    isAutoSelection = false;
}

TextEdit::~TextEdit()
{
    watcher.waitForFinished();
    delete worker;
    delete completar;
    delete rt;
    delete model;
}

void TextEdit::insertCompletion(const QString& completion)
{
    if (completar->widget() != this)
        return;
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    tc.insertText(completion);
    setTextCursor(tc);
}

QString TextEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void TextEdit::showRichTextToolBox()
{
    if( !this->isReadOnly())// && !QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
    {
        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::WordUnderCursor);
        int point =  static_cast<int> (cursor.charFormat().fontPointSize());
        QString font;

        if ( objectName() == "Roshetta" )
            font = inkFont;
        else
            font = cursor.charFormat().fontFamily();

        bool bold =  ( cursor.charFormat().fontWeight() == QFont::Bold )? true:false;
        bool italic = cursor.charFormat().fontItalic();
        bool underLine = cursor.charFormat().fontUnderline();
        bool strike = cursor.charFormat().fontStrikeOut();
        bool highlight = ( cursor.charFormat().background() == Qt::yellow)? true:false;
        bool alignLeft = ( cursor.blockFormat().alignment() == Qt::AlignLeft) ? true:false;
        bool alignCenter = ( cursor.blockFormat().alignment() == Qt::AlignCenter) ? true:false;
        bool alignRight = ( cursor.blockFormat().alignment() == Qt::AlignRight) ? true:false;
        bool upper = ( cursor.charFormat().fontCapitalization() == QFont::AllUppercase )? true:false;
        rt->syncFontPoint(font,point,bold,italic,underLine,strike,highlight,alignLeft,alignCenter,alignRight,upper);
        QPoint pos = viewport()->mapToGlobal(QPoint(cursorRect().x(),cursorRect().y()+15));
        rt->move(pos);
        rt->show();
        isSelectionStyled=false;
    }
}

void TextEdit::highLight(bool normal)
{
    QTextCharFormat fmt;
    fmt.setBackground(normal ? Qt::yellow:Qt::transparent);
    fmt.setForeground(Qt::black);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setBold(bool normal)
{
    QTextCharFormat fmt;
    fmt.setFontWeight( normal ? QFont::Bold:QFont::Normal);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setUpper(bool normal)
{
    QTextCharFormat fmt;
    fmt.setFontCapitalization(normal ? QFont::Capitalization::AllUppercase:QFont::Capitalization::AllLowercase);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::underline(bool normal)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(normal ? true:false);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::reset()
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setFont(defaultFont);
    fmt.setFontPointSize(DefaultPointSize);
    fmt.setForeground(Qt::black);
    fmt.setFontWeight(defaultBold? QFont::Black:QFont::Normal);
    fmt.setBackground(Qt::transparent);
    fmt.setFontStrikeOut(false);
    fmt.setFontUnderline(false);
    fmt.setFontItalic(false);
    fmt.setFontCapitalization(QFont::Capitalization::MixedCase);
    mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}


void TextEdit::alignRight()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat fmt = cursor.blockFormat();
    fmt.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::alignCenter()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat fmt = cursor.blockFormat();
    fmt.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(fmt);
    isSelectionStyled=true;

}

void TextEdit::alignLeft()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat fmt = cursor.blockFormat();
    fmt.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setForegroundColor(QColor color)
{
    QTextCharFormat fmt;
    QTextCursor cursor = this->textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setForeground(color);
    this->mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setBackgroundColor(QColor color)
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setBackground(color);
    this->mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::setItalic(bool normal)
{
    QTextCharFormat fmt;
    fmt.setFontItalic( normal ? true:false);
    this->mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::strike(bool normal)
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(normal ? true:false);
    this->mergeCurrentCharFormat(fmt);
    isSelectionStyled=true;
}

void TextEdit::focusInEvent(QFocusEvent *e)
{
    if (completar)
        completar->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void TextEdit::mouseReleaseEvent(QMouseEvent *e)
{
    int selectedTextLength = textCursor().selectedText().length();
    if ( selectedTextLength > 0 )
        emit showRichTextToolBox();
    QTextEdit::mouseReleaseEvent(e);
}

void TextEdit::mousePressEvent(QMouseEvent *e)
{
    if (completar && completar->popup()->isVisible())
    {
        completar->popup()->hide();
    }

    if ( e->button() == Qt::RightButton)
    {
        QTextCursor c =  textCursor();
        if(c.selectedText().length() <= 0)
        {
            c =  cursorForPosition(e->pos());
            c.select(QTextCursor::WordUnderCursor);
        }
        setTextCursor(c);
    }

    QTextEdit::mousePressEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    bool isCTRL = e->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier);
    bool isALT = e->modifiers().testFlag(Qt::KeyboardModifier::AltModifier);

    if(isALT)
        completar->popup()->hide();

    switch (e->key())
    {
    case Qt::Key_Space:
        if(lastKeyPressedisSpace && e->modifiers() == Qt::ShiftModifier)
        {
            textCursor().deletePreviousChar();
            reset();
        }
        lastKeyPressedisSpace=true;
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(!isReadOnly())
            reset();
        break;
    default:
        lastKeyPressedisSpace=false;
        break;
    }

    if (completar && completar->popup()->isVisible()) {
        if ( e->modifiers() == Qt::SHIFT && e->key() == Qt::Key_Delete )
        {
            QAbstractProxyModel *t_proxyModel = static_cast<QAbstractProxyModel*> (completar->popup()->model());
            QString currentText = completar->popup()->currentIndex().data(Qt::DisplayRole).toString();
            int ChildRow =  completar->popup()->selectionModel()->currentIndex().row();
            int ParentRow = t_proxyModel->mapToSource(t_proxyModel->index(ChildRow,0)).row();
            emit removeItemFromCompleter(currentText,ParentRow);
            ChildRow = (ChildRow==0)? 0:ChildRow-1;
            QItemSelectionModel* sm = static_cast<QItemSelectionModel*> (completar->popup()->selectionModel());
            sm->select(completar->completionModel()->index(ChildRow,0), QItemSelectionModel::Select);
            completar->popup()->setCurrentIndex(t_proxyModel->index(ChildRow,0));

        }

        // The following keys are forwarded by the completer to the widget
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }


    if ( isCTRL )
    {
        switch (e->key()) {
        case Qt::Key_Equal:
            setPointPlusOne();
            return;
            break;
        case Qt::Key_Minus:
            setPointMinusOne();
            return;
            break;
        case Qt::Key_Period:
            textCursor().clearSelection();
            insertHtml("&#9679;&#160;");
            return;
            break;
        case Qt::Key_Comma:
            textCursor().clearSelection();
            insertHtml("&#9632;&#160;");
            return;
            break;
        case Qt::Key_Right:
            textCursor().clearSelection();
            insertHtml("&#8594;");
            return;
            break;
        case Qt::Key_Up:
            textCursor().clearSelection();
            insertHtml("&#8593;");
            return;
            break;
        case Qt::Key_Down:
            textCursor().clearSelection();
            insertHtml("&#8595;");
            return;
            break;
        case Qt::Key_Left:
            textCursor().clearSelection();
            insertHtml("&#8592;");
            return;
            break;
        case Qt::Key_R:
            reset();
            break;
        case Qt::Key_0:
            textCursor().clearSelection();
            insertHtml("&#177;");
            break;
        default:
            break;
        }
    }

    if ( isALT)
    {
        QTextCursor crsr = textCursor();

        if(crsr.selectedText().length() <= 0)
        {
            crsr.select(QTextCursor::WordUnderCursor);
            setTextCursor(crsr);
            isAutoSelection = true;
        }

        if (crsr.selectedText().length() > 0 && completar != nullptr && ! completar->popup()->isVisible())
            showRichTextToolBox();
        isSelectionStyled = false;
        return;
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (completar == nullptr|| !isShortcut) // dont process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (completar == nullptr|| (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut  && ( isReadOnly()|| hasModifier || e->text().isEmpty()|| completionPrefix.length() < 2
                          || eow.contains(e->text().right(1) ))) {
        completar->popup()->hide();
        return;
    }

    if (completionPrefix != completar->completionPrefix()) {
        completar->setCompletionPrefix(completionPrefix);
        completar->popup()->setCurrentIndex(completar->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(completar->popup()->sizeHintForColumn(0)
                + completar->popup()->verticalScrollBar()->sizeHint().width());
    completar->complete(cr); // popup it up!
}

void TextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if (!completar->popup()->isVisible() && !rt->isVisible() && textCursor().selectedText().length() > 0 )
    {
        switch (e->key())
        {
        case Qt::Key_Shift:
        case Qt::Key_Control:
            emit showRichTextToolBox();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (e->key())
        {
        case Qt::Key_Space:
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
            if(needReset)
                reset();
            break;
        default:
            break;
        }
    }
    needReset=false;
    QTextEdit::keyReleaseEvent(e);
}
