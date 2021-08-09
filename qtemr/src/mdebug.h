// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MDEBUG_H
#define MDEBUG_H

#endif // MDEBUG_H
#include <QDebug>

#define mDebug() QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug()
