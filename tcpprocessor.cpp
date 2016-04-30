#include "tcpprocessor.h"
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QThread>
#include <QTimerEvent>
#include <QUuid>

static const int TimeOut = 30000;

TCPProcessor::TCPProcessor(QTcpSocket *socket,
                           std::function<void ()> timeOutCallbackFunction,
                           QObject *parent) :
  QObject( parent )
, _socket( socket )
, _timeOutCallbackFunction( timeOutCallbackFunction )
, _fileName( QUuid::createUuid().toString() )
, _isHeaderRecived( false )
, _timerId( 0 )
{
  startTimer( TimeOut );//time out
}

TCPProcessor::~TCPProcessor()
{
  qDebug() << "TCPProcessor::~TCPProcessor()";
}

void TCPProcessor::ProcessDatagramm()
{
  if ( _socket == nullptr )
    return;

  killTimer( _timerId );
  //  const quint8 CountEmptyStrings = 2;
  //  int counterEmptyStrings( 0 );
  while( _socket->bytesAvailable() > 0 )
    {
      if( _isHeaderRecived == false )
        {
          QByteArray line = _socket->readLine();
          QString stringLine( line );
          stringLine = stringLine.trimmed();

          if ( stringLine.isEmpty() )
              _isHeaderRecived = true;

          continue;
        }

      //      if ( ++counterEmptyStrings != CountEmptyStrings )
      //        continue;

      ProcessData( _socket->readAll() );
    }

  startTimer( TimeOut );
}

void TCPProcessor::timerEvent(QTimerEvent *event)
{
  killTimer( event->timerId() );

  if ( _socket )
    {
      QTextStream os( _socket );
      os.setAutoDetectUnicode(true);
      os << "HTTP/1.1 200 Ok\r\n"
            "content-type: text/html; charset=\"utf-8\"\r\n"
            "server: HttpServer\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<h1>Saved!</h1>\n"
         << QDateTime::currentDateTime().toString().toUtf8() << "\n";

    }

  _timeOutCallbackFunction();
}

void TCPProcessor::ProcessData( const QByteArray &data )
{
  QFile file( _fileName + ".txt" );
  if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) )
    qDebug() << "File not opened!";
  else
    {
      file.write( data );
      file.close();
    }
}
