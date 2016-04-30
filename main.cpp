#include <QCoreApplication>
#include "HttpServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	HttpServer s;
	
	return a.exec();
}

