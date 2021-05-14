#include"udpClient.hpp"


int main()
{
  udpClient uc;
  uc.initClient();
  uc.start();

  return 0;
}
