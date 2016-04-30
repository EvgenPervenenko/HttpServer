#include "TCPConnection.h"
#include "TCPConnectionPrivate.h"
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>
#include <QApplication>

TCPConnection::TCPConnection() :
  _ip( QHostAddress::Any )
, _port( 80 )
, _serverStatus( 0 )
{
  if ( !listen(QHostAddress::Any, _port) && _serverStatus == 0 )
    qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(errorString());
  else
    {
      _serverStatus = 1;
      qDebug() << "TCPSocket listen on port : " << _port;
      qDebug() << "Server started";
    }
}

TCPConnection::~TCPConnection()
{
}

void TCPConnection::incomingConnection(qintptr handle)
{
  qDebug() << "New connection!";
  auto *connection = new TcpConnectionPrivate( handle );
  QThread *thread = new QThread(connection);
  connection->moveToThread( thread );
  connect(thread, SIGNAL( started() ), connection, SLOT( run() ));
  _clients.push_back( connection );
  thread->start();
}

