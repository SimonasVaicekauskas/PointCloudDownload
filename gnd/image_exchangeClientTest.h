#ifndef IMAGE_EXCHANGECLIENTTEST_H_
#define IMAGE_EXCHANGECLIENTTEST_H_

#include "image_exchangeClient.h"
#include "fastrtps/utils/eClock.h"

using namespace eprosima::fastrtps;

class gnd_clientTest {
public:
  gnd_clientTest();
  virtual ~gnd_clientTest();
  gnd_client m_client;
  void run(void);

};

#endif

