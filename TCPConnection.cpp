#include "TCPConnection.h"
#include "TCPConnectionPrivate.h"
#include "ThreadManager.h"

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
  
  _threadManager = new ThreadManager( this );
}

TCPConnection::~TCPConnection()
{}

void TCPConnection::incomingConnection(qintptr handle)
{
  qDebug() << "New connection!";
  auto *connection = new TcpConnectionPrivate( handle );
  QThread *thread = _threadManager->GetThread();
  connection->moveToThread( thread );
  _clients.push_back( connection );
  
  connect( connection, &TcpConnectionPrivate::SocketClosed, 
           _threadManager, &ThreadManager::SocketClosed );
  
  QMetaObject::invokeMethod(connection,
  "Run",
  Qt::QueuedConnection);
}
