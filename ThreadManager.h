#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>
#include <QMap>

class ThreadManager : public QObject
{
	Q_OBJECT
public:
	ThreadManager(QObject *parent = nullptr);
	~ThreadManager();
	
	QThread *GetThread();
	
public Q_SLOTS:
	void SocketClosed( QThread * );
	
private:
	QMap<int, QThread *> _threadPool;
};

#endif // THREADMANAGER_H
