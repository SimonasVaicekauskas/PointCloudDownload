#ifndef IMAGE_EXCHANGECLIENT_H_
#define IMAGE_EXCHANGECLIENT_H_

#include "image_exchangePubSubTypes.h"

#include "fastrtps/fastrtps_fwd.h"
#include "fastrtps/subscriber/SampleInfo.h"

#include "fastrtps/publisher/PublisherListener.h"
#include "fastrtps/subscriber/SubscriberListener.h"

using namespace eprosima;
using namespace fastrtps;

using namespace airvision;
using namespace airvision::contracts;

class gnd_client {
public:
  gnd_client();
  virtual ~gnd_client();
  Publisher* mp_operation_pub;
  Subscriber* mp_result_sub;
  Participant* mp_participant;
  bool init();
  void send_message();
  bool isReady();
private:
  image_request m_operation;
  image_response m_result;
  SampleInfo_t m_sampleInfo;

  void resetResult();
  image_responsePubSubType* mp_resultdatatype;
  image_requestPubSubType* mp_operationdatatype;

  class OperationListener:public PublisherListener
  {
  public:
    OperationListener(gnd_client* up):mp_up(up){}
    ~OperationListener(){}
    gnd_client* mp_up;
    void onPublicationMatched(Publisher* pub,MatchingInfo& info);
  }m_operationsListener;
  class ResultListener:public SubscriberListener
  {
  public:
    ResultListener(gnd_client* up):mp_up(up){}
    ~ResultListener(){}
    gnd_client* mp_up;
    void onSubscriptionMatched(Subscriber* sub,MatchingInfo& info);
    void onNewDataMessage(Subscriber* sub);
  }m_resultsListener;
  bool m_isReady;
  int m_operationMatched;
  int m_resultMatched;
};

#endif /* EPROSIMACLIENT_H_ */

