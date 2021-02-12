// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PCH_H
#define PCH_H

#endif // PCH_H
// Add C includes here




// Add C++ includes here


#if defined __cplusplus



#include <QtConcurrentRun>
#if defined _DEBUG && MEMLEAK == 2
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#endif 

#include <QVector>
#include <QThread>
#include <QPair>
#include <QString>
#include <QValidator>
#include <QFrame>
#include <QSpacerItem>
#include <QSqlTableModel>
#include <QFutureWatcher>
#include <QDialog>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtConcurrent>
#include <QFuture>
#include <QCompleter>
#include <QList>
#include <QMainWindow>
#include <QEvent>
#include <QSystemTrayIcon>
#include <QLocale>
#include <QGraphicsBlurEffect>
#include <QShortcut>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFontComboBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVersionNumber>
#include <QGraphicsDropShadowEffect>
#include <QRegExpValidator>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QToolBar>
#include <QPushButton>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QSound>
#include <QImage>
#include <QPixmap>
#include <QBuffer>
#include <QImageReader>
#include <QDesktopWidget>
#include <QRect>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QTableView>
#include <QItemDelegate>
#include <QLineEdit>
#include <QFile>
#include <QFileInfo>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QTimer>
#include <QUrl>
#include <QStringListModel>
#include <QDesktopServices>
#include <QtNetwork/QTcpSocket>
#include <QWidget>
#include <QToolButton>
#include <QColor>
#include <QGridLayout>
#include <QDate>
#include <QCoreApplication>
#include <QEventLoop>
#include <QMovie>
#include <QCloseEvent>
#include <QStyledItemDelegate>
#include <QHeaderView>
#include <QRegExp>
#include <QScrollBar>
#include <QIcon>
#include <QFileSystemWatcher>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QComboBox>
#include <QFileDialog>
#include <QMenu>
#include <QTextEdit>
#include <QAction>
#include <QApplication>
#include <QCalendarWidget>
#include <QObject>
#include <QTextStream>
#include <QStandardItemModel>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QDir>
#include <QSettings>
#include <QCryptographicHash>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>


#include "3rdparty/zip/zconf.h"
#include "3rdparty/zip/zipreader.h"
#include "3rdparty/zip/zipwriter.h"
#include "3rdparty/zip/zlib.h"
#include "windowmanager.h"
#include "mdebug.h"
#include "mdialog.h"
#include "switch.h"
#include "mship.h"
#include "wm_mship.h"
#include "email.h"
#include "regapp.h"
#include "3rdparty/smtp/smtp.h"
#include "errorlogviewer.h"

#include <string>
#include <set>
#include <map>
#include <memory>
#include <vector>
#include <unordered_map>
#include <array>
#include <bitset>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <type_traits>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <condition_variable>

#endif

