#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QSharedPointer>
#include <QRunnable>
#include <QReadWriteLock>

class TCPProcessor;

class TcpConnectionPrivate : public QObject
{
  Q_OBJECT
public:
  TcpConnectionPrivate(qintptr socketDescriptor, QObject *parent = nullptr);
  ~TcpConnectionPrivate();

Q_SIGNALS:
  void TimeOut();

private Q_SLOTS:
  void run();
  void ReadyRead();
  void ProcessTimeOut();

private:
  QTcpSocket *_socket;
  QSharedPointer<TCPProcessor> _processor;
  qintptr _socketDescriptor;
  bool _isTimeOut;

};
