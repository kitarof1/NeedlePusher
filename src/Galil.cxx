#include <iostream>
#include <sstream>
#include <QtGui>
#include <QtNetwork>
#include <string.h>
#include "Galil.h"

const int DiscoveryPort = 18888;
const int ComPort = 18889;

Galil::Galil(QWidget *parent) : QDialog(parent)
{
  this->MulticastAddress = QHostAddress("239.255.19.56");
  this->MulticastSocket = new QUdpSocket(this);
  this->MulticastSocket->bind(DiscoveryPort);
}

Galil::~Galil()
{
  this->CloseConnection();
}



int Galil::DiscoverGalilBoards()
{
  std::cerr << std::endl;
  std::cerr << "Board \t  IP Address  \t    Port " << std::endl;
  std::cerr << "------------------------------------" << std::endl;

  do{
  QByteArray datagram = "\r";
  if( this->MulticastSocket->writeDatagram(datagram.data(), datagram.size(), this->MulticastAddress, DiscoveryPort) == -1)
    {
    std::cerr << "Error: Cannot send discovery packet" << std::endl;
    }
  }while(!this->MulticastSocket->waitForReadyRead(1500));

  this->ReceivingData();
  return 1;
}

void Galil::ReceivingData()
{
  while(this->MulticastSocket->hasPendingDatagrams())
    {
    QByteArray datagram;
    QHostAddress *SenderIPAddress = new QHostAddress();
    quint16 port_number;
    datagram.resize(this->MulticastSocket->pendingDatagramSize());
    this->MulticastSocket->readDatagram(datagram.data(), datagram.size(), SenderIPAddress, &port_number);
    this->GalilBoardsVector.push_back(SenderIPAddress);
    std::cerr << "#" << this->GalilBoardsVector.size()-1
              << "\t  " << SenderIPAddress->toString().toStdString()
              << "\t    " << port_number << std::endl;

    // Close connection
    QByteArray closeConnectionDatagram = "IHS=>-1\r";
    if( this->MulticastSocket->writeDatagram(closeConnectionDatagram.data(), closeConnectionDatagram.size(), *SenderIPAddress, port_number) == -1)
      {
      std::cerr << "Error: Couldn't close socket" << std::endl;
      }

    }
  std::cerr << "------------------------------------" << std::endl;
}

void Galil::ChooseGalilBoard()
{
  int galilBoardChoosed = 0;
  std::cerr << std::endl << std::endl;

  // Automatically connect if only 1 board detected
  if(this->GalilBoardsVector.size() != 1)
    {
    std::cerr << "Connect to Galil Board #: ";
    std::cin >> galilBoardChoosed;
    }
  else
    {
    std::cerr << "Single board detected." << std::endl
              << "Automatic connection." << std::endl;
    }

  if(galilBoardChoosed < this->GalilBoardsVector.size())
    {
    std::cerr << "Connecting to " << this->GalilBoardsVector[galilBoardChoosed]->toString().toStdString() << "...";
    this->ConnectBoard(*(this->GalilBoardsVector[galilBoardChoosed]));
    }
}

void Galil::ConnectBoard(QHostAddress GalilAddress)
{
  // Create connection
  this->GBoardSocket = new QTcpSocket(this);
  this->GBoardSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
  this->GBoardSocket->connectToHost(GalilAddress, ComPort);
  this->GBoardSocket->waitForConnected();
  if(this->GBoardSocket->isOpen())
    {
    std::cerr << "OK" << std::endl;
    // Get Revision
    if ( this->SendCommand("\x12\x16") )
      {
      this->BoardReply.chop(2);
      std::cerr << std::endl << "Revision detected: " << this->BoardReply.data() << std::endl;
      }
    }
  else
    {
    std::cerr << "Error: Not connected" << std::endl;
    }
}

int Galil::SendCommand(const char* command)
{
  if(!strcmp(command,"exit"))
    {
    this->CloseConnection();
    return 1;
    }

  std::string commandCompleted(command);
  commandCompleted += "\r";
  QByteArray ComToSend(commandCompleted.c_str());
  if( this->GBoardSocket->bytesAvailable() == 0)
    {
    if( this->GBoardSocket->write(ComToSend) == -1)
      {
      std::cerr << "Error: Could not send command" << std::endl;
      return 0;
      }

    this->GBoardSocket->flush();
    if ( this->GBoardSocket->waitForReadyRead(10000) )
      {
      this->ReadReply();
      if(this->BoardReply.endsWith(":"))
        {

        // If command is BGA, we ask position until motor stop moving
        if(!strcmp(command,"BGA"))
          {
          do
            {
            if( this->SendCommand("TPA") )
              {
              this->BoardReply.chop(2);
              std::cerr << "Position: " << this->BoardReply.data() << std::endl;
              if( this->SendCommand("MG_BGA") )
                {
                this->BoardReply.chop(3);
                }
              }
            }while(this->BoardReply.toDouble());
          }

        return 1;
        }
      }
    }
  else
    {
    this->ReadReply();
    std::cerr << "DataAvailable:" << this->BoardReply.data() << std::endl;
    }
  return 0;
}

void Galil::ReadReply()
{
  this->BoardReply.clear();
  this->BoardReply.resize(this->GBoardSocket->bytesAvailable());
  this->BoardReply = this->GBoardSocket->readAll();
}

void Galil::CloseConnection()
{
  if(this->GBoardSocket->isOpen())
    {
    if ( this->SendCommand("IHS=>-1") )
      {
      this->GBoardSocket->close();
      }
    }
}
