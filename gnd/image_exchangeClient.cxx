#include "image_exchangeClient.h"

#include "fastrtps/fastrtps_all.h"

#include <fstream>

gnd_client::gnd_client():
mp_operation_pub(nullptr),
mp_result_sub(nullptr),
mp_participant(nullptr),
mp_resultdatatype(nullptr),
mp_operationdatatype(nullptr),
m_operationsListener(nullptr),
m_resultsListener(nullptr),
m_isReady(false),
m_operationMatched(0),
m_resultMatched(0)
{
  m_operationsListener.mp_up = this;
  m_resultsListener.mp_up = this;
}

gnd_client::~gnd_client()
{
  Domain::removeParticipant(mp_participant);
  if(mp_resultdatatype!=nullptr)
    delete(mp_resultdatatype);
  if(mp_operationdatatype!=nullptr)
    delete(mp_operationdatatype);
}

bool gnd_client::init()
{
  //CREATE RTPSParticipant
  ParticipantAttributes PParam;
  //PParam.rtps.defaultSendPort = 10042;
  PParam.rtps.builtin.domainId = 0;
  PParam.rtps.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;
//  PParam.rtps.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
  PParam.rtps.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
  PParam.rtps.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
//  PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
//  PParam.rtps.sendSocketBufferSize = 8712;
//  PParam.rtps.listenSocketBufferSize = 17424;
  PParam.rtps.setName( "client_RTPSParticipant");

  mp_participant = Domain::createParticipant(PParam);
  if(mp_participant == nullptr)
    return false;

  //REGISTER TYPES
  mp_operationdatatype = new image_requestPubSubType();
  mp_resultdatatype = new image_responsePubSubType();
  Domain::registerType(mp_participant,mp_operationdatatype);
  Domain::registerType(mp_participant,mp_resultdatatype);

  // DATA PUBLISHER
  PublisherAttributes PubDataparam;
  PubDataparam.topic.topicKind = NO_KEY;
  PubDataparam.topic.topicDataType = "airvision::contracts::image_request";
  PubDataparam.topic.topicName = "image_request";
/*
  PubDataparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
  PubDataparam.topic.historyQos.depth = 200;
  PubDataparam.topic.resourceLimitsQos.max_samples = 200;
  PubDataparam.topic.resourceLimitsQos.allocated_samples = 200;
*/
  PubDataparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS; //BEST_EFFORT_RELIABILITY_QOS;
  mp_operation_pub = Domain::createPublisher(mp_participant,PubDataparam,(PublisherListener*)&this->m_operationsListener);
  if(mp_operation_pub == nullptr)
    return false;

  //DATA SUBSCRIBER
  SubscriberAttributes SubDataparam;

/*  Locator_t loc1;
  loc1.port = 7555;
  SubDataparam.unicastLocatorList.push_back(loc1);
  Locator_t loc2;
  loc2.port = 7556;
  SubDataparam.unicastLocatorList.push_back(loc2);
  Locator_t loc3;
  loc3.port = 7557;
  SubDataparam.unicastLocatorList.push_back(loc3);
  Locator_t loc4;
  loc4.port = 7558;
  SubDataparam.unicastLocatorList.push_back(loc4);
*/

  SubDataparam.topic.topicDataType = "airvision::contracts::image_response";
  SubDataparam.topic.topicKind = NO_KEY;
  SubDataparam.topic.topicName = "image_response";
/*
  SubDataparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
  SubDataparam.topic.historyQos.depth = 200;
  SubDataparam.topic.resourceLimitsQos.max_samples = 200;
  SubDataparam.topic.resourceLimitsQos.allocated_samples = 200;
*/
  SubDataparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS; //BEST_EFFORT_RELIABILITY_QOS;

  mp_result_sub = Domain::createSubscriber(mp_participant,SubDataparam,(SubscriberListener*)&this->m_resultsListener);
  if(mp_result_sub == nullptr)
    return false;
  return true;
}

void gnd_client::send_message()
{
  while(m_operationsListener.mp_up->m_operationMatched == 0)
  {
    eClock::my_sleep(250);
  }
  airvision::contracts::image_request st;
  //st.index(10);
  mp_operation_pub->write(&st);
}

void gnd_client::OperationListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
{
  if(info.status == MATCHED_MATCHING)
  {
    std::cout << "publication matched" << std::endl;
    mp_up->m_operationMatched++;
  }
  else
  {
    std::cout << "publication unmatched" << std::endl;
    mp_up->m_operationMatched--;
  }
  mp_up->isReady();
}

void gnd_client::ResultListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
{
  if(info.status == MATCHED_MATCHING)
  {
    std::cout << "subscription matched" << std::endl;
    mp_up->m_resultMatched++;
  }
  else
  {
    std::cout << "subscription unmatched" << std::endl;
    mp_up->m_resultMatched--;
  }
  mp_up->isReady();
}

void gnd_client::ResultListener::onNewDataMessage(Subscriber* sub)
{
 // std::cout << "new data message received\n" << std::endl;
  airvision::contracts::image_response st;
  SampleInfo_t si;

  if(mp_up->mp_result_sub->takeNextData(&st, &si))
  {
    if(si.sampleKind == ALIVE)
    {
      if(st.status() == 0){
        cout << "First command is working\n" << endl;
      }
      if(st.status() == 1){
        cout << "Second command is working\n" << endl;
      }
      if(st.status() == 2){
        cout << "Third command is working\n" << endl;
      }
      if(st.status() == 3){
        cout << "Forth command is working\n" << endl;
      }
      
      if(st.status() == 4)
      {
      std::vector<char> data = st.data();
      std::string str = std::string(st.data().begin(),st.data().end());
      std::string filename = "/home/simas/PointCloudDownload/gnd/out.ply";
      std::ofstream output(filename, std::ofstream::binary);
      std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(output));
      std::cout <<" Point cloud written in : " + filename  << std::endl; 
      }
    }
    else
      {
        std::cout << "Unknown data received" << std::endl;
      }
  }
}

bool gnd_client::isReady()
{
  if(m_operationMatched == 1 && m_resultMatched == 1)
    m_isReady = true;
  else
    m_isReady = false;
  return m_isReady;
}

