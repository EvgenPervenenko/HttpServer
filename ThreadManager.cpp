#include "ThreadManager.h"
#include <QDebug>

ThreadManager::ThreadManager(QObject *parent) :
    QObject( parent )
{
	for ( auto i = 0; i < QThread::idealThreadCount(); ++i )
	{
		QThread *t( new QThread( this ) );
		t->start();
		_threadPool.insertMulti( 0, t );
	}
}

ThreadManager::~ThreadManager()
{}

QThread *ThreadManager::GetThread()
{
	if ( _threadPool.isEmpty() )
		return nullptr;
		
	auto firstKey = _threadPool.firstKey();
	auto firstThread = _threadPool.take( firstKey );
	++firstKey;
	_threadPool.insertMulti( firstKey, firstThread );
	
	return firstThread;
}

void ThreadManager::SocketClosed(QThread *thread)
{
	auto key = _threadPool.key( thread );
	_threadPool.remove( key );
	--key;
	_threadPool.insert( key, thread );
}

