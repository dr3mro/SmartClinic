// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "singleinstance.h"

SingleInstance::SingleInstance(QObject *parent) : QObject(parent) {
  Q_UNUSED(parent)
  connect(&mServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

SingleInstance::~SingleInstance() { mServer.close(); }

void SingleInstance::listen(QString name) {
  mServer.removeServer(name);
  if (!mServer.isListening()) mServer.listen(name);
  // mDebug() << "Listening for: " << name;
  if (!mServer.isListening()) mDebug() << mServer.errorString();
}

bool SingleInstance::hasPrevious(QString name, QStringList arg) {
  // mDebug() << "Checking for previous instance...";

  QLocalSocket socket;
  socket.connectToServer(name, QLocalSocket::ReadWrite);

  if (socket.waitForConnected()) {
    // mDebug() << "Sending args to previous instance...";
    QByteArray buffer;

    foreach (QString item, arg) {
      buffer.append(item.toUtf8() + "\n");
    }
    socket.write(buffer);
    socket.waitForBytesWritten();
    return true;
  }

  // mDebug() << socket.errorString();

  return false;
}

void SingleInstance::newConnection() {
  emit newInstance();
  // mDebug() << "New connection loading...";
  mSocket = mServer.nextPendingConnection();
  connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void SingleInstance::readyRead() {
  //    mDebug() << "READ!!";
  //    mDebug() << "Arg = " << mSocket->readAll();
  emit doAction();
  mSocket->deleteLater();
}
