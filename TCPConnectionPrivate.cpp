#include "TCPConnectionPrivate.h"
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QThread>
#include "tcpprocessor.h"

TcpConnectionPrivate::TcpConnectionPrivate(qintptr socketDescriptor, QObject *parent) :
  QObject(parent),
  _socketDescriptor( socketDescriptor )
{
}

TcpConnectionPrivate::~TcpConnectionPrivate()
{
  qDebug() << "TcpConnectionPrivate::~TcpConnectionPrivate()";
  if (_socket)
          _socket->abort();
}

void TcpConnectionPrivate::run()
{
  _socket = new QTcpSocket( this );
  _socket->setSocketDescriptor( _socketDescriptor );
  _processor = QSharedPointer<TCPProcessor>(new TCPProcessor( _socket,
                                                              [&](){ProcessTimeOut();} ));

  connect( _socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()) );
  connect(_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void TcpConnectionPrivate::ReadyRead()
{
  _processor->ProcessDatagramm();
}

void TcpConnectionPrivate::ProcessTimeOut()
{
  qDebug() << "Time out";
  emit TimeOut();
  _socket->close();
}
