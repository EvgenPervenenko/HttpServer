#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSharedPointer>
#include <QBuffer>
#include <QTcpServer>
#include <QThreadPool>

class TcpConnectionPrivate;
class ThreadManager;

class TCPConnection : public QTcpServer
{
	Q_OBJECT
public:
	TCPConnection();
	~TCPConnection();

protected:
	virtual void incomingConnection(qintptr handle) override;
	
Q_SIGNALS:
	void Recieve();
	
private:
	QVector<TcpConnectionPrivate * > _clients;
	QHostAddress _ip;
	quint16 _port;
	quint8 _serverStatus;
	ThreadManager *_threadManager;
	QMap<int, QThread *> _threadPool;
	
};

#endif // CONNECTION_H
