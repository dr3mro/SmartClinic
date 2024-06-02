// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mpatientfilter.h"

mPatientFilter::mPatientFilter(QWidget *parent) {
  validator.setRegularExpression(QRegularExpression("^\\S(.*\\S)?$"));
  setValidator(&validator);

  QAction *filterToggleAction = this->addAction(
      QIcon(":/ionicons/more"), QLineEdit::ActionPosition::TrailingPosition);

  filterToggleAction->setCheckable(true);

  connect(filterToggleAction, SIGNAL(toggled(bool)), parent,
          SLOT(showHideFilters(bool)));
  connect(this, SIGNAL(toggleFilters(bool)), filterToggleAction,
          SLOT(setChecked(bool)));
}

void mPatientFilter::keyPressEvent(QKeyEvent *ke) {
  switch (ke->key()) {
    case Qt::Key_Down:
      emit focusPatientTable();
      break;
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
      if (ke->modifiers() == Qt::CTRL) emit toggleFilters(true);
      break;
    default:
      break;
  }
  QLineEdit::keyPressEvent(ke);
}
