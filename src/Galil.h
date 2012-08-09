#ifndef GALILMULTICAST_H_
#define GALILMULTICAST_H

#include <QUdpSocket>
#include <QTcpSocket>
#include <QMutex>
#include <QHostAddress>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QUdpSocket;
class QHostAddress;
class QDialog;
QT_END_NAMESPACE

class Galil : public QDialog
{
  Q_OBJECT

 public:
  Galil(QWidget* parent = 0);
  ~Galil();
  int DiscoverGalilBoards();
  int SendCommand(const char* command);
  QByteArray BoardReply;
  void ChooseGalilBoard();
  void CloseConnection();

  private slots:
    void ReceivingData();
    void ReadReply();

 private:
    void ConnectBoard(QHostAddress GalilAddress);

 private:
    QUdpSocket* MulticastSocket;
    QTcpSocket* GBoardSocket;
    QHostAddress MulticastAddress;
    std::vector<QHostAddress*> GalilBoardsVector;
};

#endif
