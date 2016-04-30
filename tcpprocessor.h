#ifndef TCPPROCESSOR_H
#define TCPPROCESSOR_H

#include <QObject>
#include <QTcpSocket>
#include <functional>
#include <QSharedPointer>

class TCPProcessor : public QObject
{
  Q_OBJECT
public:
  explicit TCPProcessor(QTcpSocket *socket,
                        std::function<void ()> timeOutCallbackFunction,
                        QObject *parent = 0);
  ~TCPProcessor();

  void ProcessDatagramm();

protected:
  virtual void timerEvent(QTimerEvent *) override;

private:
  void ProcessData(const QByteArray &data);

private:
  QTcpSocket *_socket;
  std::function<void ()> _timeOutCallbackFunction;
  QString _fileName;
  bool _isHeaderRecived;
  int _timerId;
};

#endif // TCPPROCESSOR_H
