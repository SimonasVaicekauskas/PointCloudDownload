#include "image_exchangeServer.h"

//#include <fastrtps/utils/RTPSLog.h>
#include <fastrtps/Domain.h>

using namespace eprosima;

#if defined(__LITTLE_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = LITTLEEND;
#elif defined (__BIG_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = BIGEND;
#endif

#if defined(_WIN32)
#define COPYSTR strcpy_s
#else
#define COPYSTR strcpy
#endif

int main(int argc, char** argv)
{
 air_server server;
 server.init();
 server.serve();

 return 0;
}




