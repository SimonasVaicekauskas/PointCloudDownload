#include "image_exchangeServer.h"
#include "fastrtps/fastrtps_all.h"
#include "micmac.h"
#include <iostream>
#include <fstream>

air_server::air_server():
mp_operation_sub(nullptr),
mp_result_pub(nullptr),
mp_participant(nullptr),
mp_resultdatatype(nullptr),
mp_operationdatatype(nullptr),
m_n_served(0),
m_operationsListener(nullptr),
m_resultsListener(nullptr)
{
  m_operationsListener.mp_up = this;
  m_resultsListener.mp_up = this;
}

air_server::~air_server()
{
  if(mp_participant!=nullptr)
  {
    Domain::removeParticipant(mp_participant);
  }
  if(mp_resultdatatype!=nullptr)
    delete(mp_resultdatatype);
  if(mp_operationdatatype!=nullptr)
    delete(mp_operationdatatype);
}

void air_server::serve()
{
  cout << "Server running (ENTER to stop)" << endl;
  std::cin.ignore();
}

bool air_server::init()
{
  //CREATE RTPSParticipant
  ParticipantAttributes PParam;
//  PParam.rtps.defaultSendPort = 10042;
  PParam.rtps.builtin.domainId = 0;
  PParam.rtps.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;
//  PParam.rtps.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
  PParam.rtps.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
  PParam.rtps.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
//  PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
//  PParam.rtps.sendSocketBufferSize = 8712;
//  PParam.rtps.listenSocketBufferSize = 17424;
  PParam.rtps.setName("server_RTPSParticipant");

  mp_participant = Domain::createParticipant(PParam);
  if(mp_participant == nullptr)
    return false;

  //REGISTER TYPES
  mp_resultdatatype = new image_requestPubSubType();
  mp_operationdatatype = new image_responsePubSubType();

  Domain::registerType(mp_participant, mp_resultdatatype);
  Domain::registerType(mp_participant, mp_operationdatatype);

  // DATA PUBLISHER
  PublisherAttributes PubDataparam;
/*
  Locator_t loc1;
  loc1.port = 7555;
  PubDataparam.unicastLocatorList.push_back(loc1);
  Locator_t loc2;
  loc2.port = 7556;
  PubDataparam.unicastLocatorList.push_back(loc2);
  Locator_t loc3;
  loc3.port = 7557;
  PubDataparam.unicastLocatorList.push_back(loc3);
  Locator_t loc4;
  loc4.port = 7558;
  PubDataparam.unicastLocatorList.push_back(loc4);
*/
  PubDataparam.topic.topicDataType = "airvision::contracts::image_response";
  PubDataparam.qos.m_publishMode.kind = ASYNCHRONOUS_PUBLISH_MODE;
  PubDataparam.topic.topicKind = NO_KEY;
  PubDataparam.topic.topicName = "image_response";
//  ThroughputControllerDescriptor slowPublisherThroughputController{300000, 1000}; //Limit to 300kb per second
//  PubDataparam.terminalThroughputController = slowPublisherThroughputController;
/*
  PubDataparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
  PubDataparam.topic.historyQos.depth = 200;
  PubDataparam.topic.resourceLimitsQos.max_samples = 200;
  PubDataparam.topic.resourceLimitsQos.allocated_samples = 200; // magic line, breaks system()
*/
  PubDataparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS; // BEST_EFFORT_RELIABILITY_QOS;

  mp_result_pub = Domain::createPublisher(mp_participant,PubDataparam,(PublisherListener*)&this->m_resultsListener);
  if(mp_result_pub == nullptr)
    return false;

  //DATA SUBSCRIBER
  SubscriberAttributes SubDataparam;
//  Locator_t loc;
//  loc.port = 7555;
//  PubDataparam.unicastLocatorList.push_back(loc);
  SubDataparam.topic.topicDataType = "airvision::contracts::image_request";
  SubDataparam.topic.topicKind = NO_KEY;
  SubDataparam.topic.topicName = "image_request";
/*
  SubDataparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
  SubDataparam.topic.historyQos.depth = 200;
  SubDataparam.topic.resourceLimitsQos.max_samples = 200;
  SubDataparam.topic.resourceLimitsQos.allocated_samples = 200;
*/
  SubDataparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS; //BEST_EFFORT_RELIABILITY_QOS;

  mp_operation_sub = Domain::createSubscriber(mp_participant,SubDataparam,(SubscriberListener*)&this->m_operationsListener);
  if(mp_operation_sub == nullptr)
    return false;

  return true;
}
/************************************************************************************************************************/
void air_server::send_pointcloud(short commandStatus)
{   
    airvision::contracts::image_response st;
    st.status(commandStatus); 
    if(commandStatus == 0){
     mp_result_pub->write(&st);
    } 
    if(commandStatus == 1){
      mp_result_pub->write(&st);
    }
    if(commandStatus == 2){
      mp_result_pub->write(&st);
    } 
    if(commandStatus == 3){
      mp_result_pub->write(&st);
    }

    if(commandStatus == 4){ 
    std::ifstream input;
    input.open("/home/simas/PointCloudDownload/air/example.ply",std::ios::binary);
    std::vector<char> data((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
    st.data(data);
    mp_result_pub->write(&st);
    input.close();
    cout << "Point cloud sent!"<< endl;  
    } 

   // else {
   //   cout << "Unknown status";
   // }







  /*
    airvision::contracts::image_response st;
    std::ifstream input;
    input.open("/home/simas/PointCloudDownload/air/example.ply",std::ios::binary);
    std::vector<char> data((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
    st.data(data);
    mp_result_pub->write(&st);
    input.close();
    cout << "Point cloud sent!"<< endl;
    */
}
/************************************************************************************************************************/
void air_server::run_micmac()
{   
  short commandStatus;
  std::string line;
  int counter=0;
  std::ifstream myfile ("/home/simas/PointCloudDownload/air/commands.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      
      if(exec(line.c_str()).compare("")){
        send_pointcloud(commandStatus);
        commandStatus ++;
    }
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 



/*
  short commandStatus;
  std::string emptyString = "";
  if(exec("/home/simas/scripts/wait_one.sh").compare("")){

    commandStatus = 0;
    send_pointcloud(commandStatus);

  }
  if(exec("/home/simas/scripts/wait_two.sh").compare("")) {

    commandStatus = 1;
    send_pointcloud(commandStatus);

  } 
    if(exec("/home/simas/scripts/wait_two.sh").compare("")) {

    commandStatus = 6;
    send_pointcloud(commandStatus);

  }
  else {
    cout << "Something went wrong with first command" << endl;
  }

*/



  //exec("/home/simas/scripts/wait_one.sh");
  //exec("/home/simas/scripts/wait_two.sh");
  //exec("/home/simas/scripts/wait_one.sh");
  //exec("/home/simas/scripts/wait_two.sh");
 // cout << "veikia" << endl;
 // send_pointcloud();



//  exec("/home/simas/scripts/wait_two.sh");
   // cout << "runing micmac" << endl;
  // exec("~/micmac/bin/SetExif  .*jpg F35=20 F=4.52 Cam=GoProVideoLM);
  //   exec("~/micmac/bin/Tapioca MulScale .*jpg 250 700");
  //  exec("~/micmac/bin/Tapas FishEyeEqui .*jpg Out=Cal1");
  //  exec("~/micmac/bin/Tapas Figee .*jpg InCal=Cal1 Out=Ori");
  //  exec("~/micmac/bin/AperiCloud .*jpg Ori-Ori Out=PosCams.ply");
      
}
void air_server::send_image()
{   

}

// ==================== listeners ====================== //

void air_server::OperationListener::onNewDataMessage(Subscriber* sub)
{
  airvision::contracts::image_request st;
  if(mp_up->mp_operation_sub->takeNextData(&st, &m_sampleInfo))
  {
	if(m_sampleInfo.sampleKind == ALIVE);{
   // exec("/home/simas/scripts/wait_one.sh");
   //  exec("/home/simas/scripts/wait_two.sh");
     mp_up->run_micmac();
  //  mp_up->send_pointcloud();
	}	





	
  }else{ 		
	 std::cout << "Not working" << std::endl;
  }


//-----------------------------------------------------------------------------------//

  /*if(mp_up->mp_operation_sub->takeNextData(&st, &m_sampleInfo))
  {
    if(m_sampleInfo.sampleKind == ALIVE)
    {
      cout << "sample received" << endl;
      cout << st.image_date() << " " << st.image_time() << endl;
    //  mp_up->send_image(st.index(), st.image_date(), st.image_time(), st.length(), st.fps_a(), st.fps_b(), st.image_width(), st.image_height());
    }
  }*/ 
}

void air_server::OperationListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
{
  if(info.status == MATCHED_MATCHING)
  {
    std::cout << "subscription mached" << std::endl;
  }
  else
  {
    std::cout << "subscription unmached" << std::endl;
  }
}

void air_server::ResultListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
{
  if(info.status == MATCHED_MATCHING)
  {
    std::cout << "publication mached" << std::endl;
  }
  else
  {
    std::cout << "publication unmached" << std::endl;
  }
}


