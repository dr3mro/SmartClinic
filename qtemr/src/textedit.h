// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QAbstractItemView>
#include <QApplication>
#include <QCompleter>
#include <QFuture>
#include <QFutureWatcher>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QScrollBar>
#include <QTextEdit>
#include <QtConcurrent/QtConcurrentRun>

#include "msettings.h"
#include "richtexteditor.h"
#include "wm_texteditcompleterloader.h"

class QCompleter;
class TextEdit : public QTextEdit {
  Q_OBJECT
 public:
  explicit TextEdit(QWidget *parent = nullptr);
  bool findRemoveText(QString text);
  QCompleter *completer() const;
  void cleanCompleterMemory();
  QStringListModel *model;
  void setInkFont(QString font);
  virtual ~TextEdit();

 protected:
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void focusInEvent(QFocusEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);

 public slots:
  void setCompleter();
  void updateCompleter();
  void setFont(const QFont &font);
  void setFont(const QString &font);
  void setPoint(const QString &p);
  void setCurrentSize(int p);
  void setBold(bool normal);
  void setUpper(bool normal);
  void setItalic(bool normal);
  void underline(bool normal);
  void strike(bool normal);
  void highLight(bool normal);
  void reset();
  void alignRight();
  void alignCenter();
  void alignLeft();
  void deleteSelectedText();
  void insertChar(QString str);
  void makeEditable(bool b);
  QString getSelectedText();
  void setPointPlusOne();
  void setPointMinusOne();
  void redFlagHighLight();
  void greenFlagHighLight();
  void blueFlagHighLight();
  void setFlagHighLight(const QColor &color);
  void clear();

 private slots:
  void insertCompletion(const QString &completion);
  void showRichTextToolBox();
  void setForegroundColor(const QColor &color);
  void setBackgroundColor(const QColor &color);
  void createRichTextToolBox();
  void setDefaultFont();
  void completerLoader();
  void removeFromCompleter(int row);
  void isSelectionChanged();
  void clearSelection();
  void false2autoSelected();

 private:
  QCompleter *completar;
  QWidget *parent;
  QString textUnderCursor() const;
  QFuture<QStringList> future;
  QFutureWatcher<QStringList> watcher;
  wm_texteditCompleterLoader *worker;
  int pointSize = 10;
  richTextEditor *rt;
  QFont defaultFont;
  double DefaultPointSize;
  bool defaultBold;
  QString inkFont;
  bool isSelectionStyled = false;
  bool isAutoSelection = false;
  bool needReset = false;
  bool lastKeyPressedisSpace = false;
  QString WindowName;
  mSettings &settings = mSettings::instance();
 signals:
  void removeItemFromCompleter(QString, int);
  void fontFamilyChanged(QString fontName);
  void fontPointChanged(QString point);
  void fontBoldChanged(bool isBold);
};

#endif  // TEXTEDIT_H
