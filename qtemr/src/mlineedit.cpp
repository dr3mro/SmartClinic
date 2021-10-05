// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mlineedit.h"

mLineEdit::mLineEdit(QWidget *parent):QLineEdit(parent),
    parent(parent),
    model(new QStringListModel(this)),
    windowName(parent->window()->objectName())
{

    connect(&watcher,SIGNAL(finished()),this,SLOT(completerLoader()));
}

void mLineEdit::makeEditable(bool b)
{
    setReadOnly(!b);
}

void mLineEdit::addUniqueItem2Model(QString item,QString objName)
{
    if ( objectName() != objName )
        return;
    if(!model->stringList().contains(item,Qt::CaseInsensitive))
    {
        model->insertRow(model->rowCount());
        QModelIndex index = model->index(model->rowCount()-1);
        model->setData(index, item);
    }
}

mLineEdit::~mLineEdit()
{
    watcher.waitForFinished();
    delete mcompleter;
    delete model;
}

bool mLineEdit::isCompleterPopupVisible()
{
    return completer()->popup()->isVisible();
}

void mLineEdit::toggleonTextChangedSignal(bool c)
{
    if (windowName != "visitsBox" )
        return;

    if ( c )
    {
        connect(this,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(onTextChanged()));
        connect(this,SIGNAL(editingFinished()),this,SLOT(onTextChanged()));
    }
    else
    {
        disconnect (this,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(onTextChanged()));
        disconnect (this,SIGNAL(editingFinished()),this,SLOT(onTextChanged()));
    }
}

void mLineEdit::completerLoader()
{
    autoCompleteStringList = future.result();
    model->setStringList(autoCompleteStringList);
    toggleonTextChangedSignal(false);

    if(mcompleter==nullptr)
        mcompleter = new  mCompleter(this,delimeter,model);
    else
        mcompleter->putModel(model);

    toggleonTextChangedSignal(true);
    emit completerLoaded();
}

void mLineEdit::onTextChanged()
{
    emit reportCompleterPopUpVisibility(isCompleterPopupVisible());
}

void mLineEdit::setDefaultFont()
{
    font = settings.getTextboxFont();
    QFont mFont = QFont(font.fontName);
    double mFontSize = font.fontSize;
    bool mFontBold = font.fontBold;

    mFont.setBold(mFontBold);
    mFont.setPointSize(mFontSize);

    setStyleSheet(QString("QLineEdit{font:%1 %2pt \"%3\";}")
                  .arg(mFontBold? "bold":"")
                  .arg(mFontSize)
                  .arg(font.fontName));

    setFont(mFont);
}


void mLineEdit::keyPressEvent(QKeyEvent *e)
{
    if ( e->modifiers() == Qt::SHIFT && e->key() == Qt::Key_Delete &&
         tableName != "expander")
    {
        QPoint pos = mcompleter->popup()->pos();
        QAbstractProxyModel *t_proxyModel = (QAbstractProxyModel*) mcompleter->popup()->model();
        QString currentText = mcompleter->popup()->currentIndex().data(Qt::DisplayRole).toString();
        int ChildRow =  mcompleter->popup()->selectionModel()->currentIndex().row();
        int ParentRow = t_proxyModel->mapToSource(t_proxyModel->index(ChildRow,0)).row();
        emit removeFromCompleter(ParentRow);
        emit removeItemFromCompleter(currentText,tableName);
        ChildRow = (ChildRow==0)? 0:ChildRow-1;
        QItemSelectionModel* sm = (QItemSelectionModel*) mcompleter->popup()->selectionModel();
        sm->select(mcompleter->completionModel()->index(0,0), QItemSelectionModel::Select);
        mcompleter->popup()->setCurrentIndex(t_proxyModel->index(ChildRow,0));
        QRect rect;
        rect.setSize(mcompleter->popup()->size());
        mcompleter->complete(rect);
        mcompleter->popup()->move(pos);
    }

    switch (e->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
        mcompleter->popup()->hide();
        break;
    default:
        break;
    }
    QLineEdit::keyPressEvent(e);
}
