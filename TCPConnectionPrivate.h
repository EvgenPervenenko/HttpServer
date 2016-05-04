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
  void SocketClosed( QThread * );
  
public Q_SLOTS:
  Q_INVOKABLE void Run();

private Q_SLOTS:
  void ReadyRead();
  void ProcessTimeOut();
  void Disconnected();

private:
  QTcpSocket *_socket;
  QSharedPointer<TCPProcessor> _processor;
  qintptr _socketDescriptor;
  bool _isTimeOut;
};
