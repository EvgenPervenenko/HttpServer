#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QSharedPointer>

class TCPConnection;

class HttpServer : public QObject
{
	Q_OBJECT
public:
	explicit HttpServer();
	
private Q_SLOTS:
	void ProcessPacket();
	
private:
	QSharedPointer<TCPConnection> _connection;
};

#endif // HTTPSERVER_H
