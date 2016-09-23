#include "image_exchangeClientTest.h"

using namespace eprosima;
using namespace fastrtps;

int main(int argc, char** argv)
{
  gnd_clientTest clienttest;

  clienttest.run();


  std::cout << "press to exit" << std::endl;
  std::cin.ignore();

  return 0;
}

