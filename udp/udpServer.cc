#include"udpServer.hpp"

int main()
{
  udpServer* up = new udpServer();
  up->initServer();
  up->start();

  delete up;
}
