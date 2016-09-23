#ifndef VIDEO_EXCHANGESERVER_H_
#define VIDEO_EXCHANGESERVER_H_

#include "image_exchangePubSubTypes.h"

#include "fastrtps/fastrtps_fwd.h"
#include "fastrtps/subscriber/SampleInfo.h"

#include "fastrtps/publisher/PublisherListener.h"
#include "fastrtps/subscriber/SubscriberListener.h"

using namespace eprosima;
using namespace fastrtps;

using namespace airvision::contracts;
using namespace airvision;

class air_server {
  friend class OperationListener;
  friend class ResultListener;
public:
  air_server();
  virtual ~air_server();
  bool init();
  void serve();
  void send_pointcloud(short stat);
  void send_image();
  void run_micmac();
  //air_server* mp_up;
	/******/
  //void send_message(string msg);
private:
  Subscriber* mp_operation_sub;
  Publisher* mp_result_pub;
  Participant* mp_participant;
  image_requestPubSubType* mp_resultdatatype;
  image_responsePubSubType* mp_operationdatatype;
public:
  uint32_t m_n_served;
  class OperationListener:public SubscriberListener
  {
  public:
    OperationListener(air_server* up):mp_up(up){}
    ~OperationListener(){}
    air_server* mp_up;
    void onSubscriptionMatched(Subscriber* sub,MatchingInfo& info);
    void onNewDataMessage(Subscriber*sub);
    image_responsePubSubType m_operation;
    SampleInfo_t m_sampleInfo;
    image_request m_result;
  }m_operationsListener;

  class ResultListener:public PublisherListener
  {
  public:
    ResultListener(air_server* up):mp_up(up){}
    ~ResultListener(){}
    air_server* mp_up;
    void onPublicationMatched(Publisher* pub,MatchingInfo& info);
  }m_resultsListener;
};

#endif

