#include "HttpServer.h"
#include "TCPConnection.h"
#include <QDebug>

HttpServer::HttpServer()
{
  _connection = QSharedPointer<TCPConnection>::create();
  connect( _connection.data(), &TCPConnection::Recieve,
           this, &HttpServer::ProcessPacket );
}

void HttpServer::ProcessPacket()
{
  qDebug() << "Loaded";
}
