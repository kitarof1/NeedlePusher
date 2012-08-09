#include <stdio.h>
#include <stdlib.h>
#include <QApplication>

#include <iostream>
#include "Galil.h"

void GalilWelcome();

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  GalilWelcome();

  Galil* GalilBoard = new Galil();
  if ( GalilBoard->DiscoverGalilBoards() )
    {
    GalilBoard->ChooseGalilBoard();
    std::cerr << "__________________________________________" << std::endl
              << "               Galil Terminal             " << std::endl
              << "__________________________________________" << std::endl
              << std::endl;

    std::cerr << "Configuring..." << std::endl;
    GalilBoard->SendCommand("BAA");
    GalilBoard->SendCommand("BMA=4096");
    GalilBoard->SendCommand("BXA=-3");
    GalilBoard->SendCommand("KIA=0.17");
    GalilBoard->SendCommand("SPA=2000");
    GalilBoard->SendCommand("PRA=8192");


    while(1)
      {
      std::string command;
      std::cerr << "> ";
      std::cin >> command;
      std::cerr << command << "...";

      if(!command.compare("exit"))
        {
        if( GalilBoard->SendCommand("exit") )
          {
          std::cerr << "OK" << std::endl;
          break;
          }
        }

      if ( GalilBoard->SendCommand(command.c_str()) )
        {
        std::cerr << "OK";
        GalilBoard->BoardReply.chop(2);
        if(!GalilBoard->BoardReply.isEmpty())
          {
          std::cerr << " - Data: " << GalilBoard->BoardReply.data();
          }
        std::cerr << std::endl;
        }
      else
        {
        std::cerr << "ERROR" << std::endl;
        }
      }
    }

  return 0;
}

void GalilWelcome()
{
  std::cerr << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl;

  std::cerr << "\t      ===================================================" << std::endl
            << "\t      **                                               **" << std::endl
            << "\t      **                                               **" << std::endl
            << "\t      **              GALIL  CONTROLLER                **" << std::endl
            << "\t      **                 version 1.0                   **" << std::endl
            << "\t      **         Laurent Chauvin, SNR, BWH             **" << std::endl
            << "\t      **                                               **" << std::endl
            << "\t      ===================================================" << std::endl;

  std::cerr << std::endl
            << std::endl
            << std::endl
            << std::endl
            << std::endl;
}
