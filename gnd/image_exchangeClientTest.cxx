#include "image_exchangeClientTest.h"
#include "fastrtps/utils/TimeConversion.h"

gnd_clientTest::gnd_clientTest() {
  m_client.init();
}

gnd_clientTest::~gnd_clientTest() {

}

void gnd_clientTest::run()
{
  while(!m_client.isReady())
  {
    eClock::my_sleep(100);
  }

  std::cout << "sending message" << endl;
  m_client.send_message();
}

