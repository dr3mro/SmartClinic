#ifndef MDEBUG_H
#define MDEBUG_H

#endif // MDEBUG_H
#include <QDebug>

#define mDebug() QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug()
