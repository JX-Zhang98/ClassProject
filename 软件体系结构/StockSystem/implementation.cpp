#include "implementation.hpp"
#include "common/example_utilities.h"
#include <fstream>
#include <sstream>
#include "ContentFilteredTopicData_DCPS.hpp"
#include <ctime>
#define random(x) (rand()%x)

namespace {
    const unsigned int write_loop_count = 20;
}

namespace examples {
#ifdef GENERATING_EXAMPLE_DOXYGEN
GENERATING_EXAMPLE_DOXYGEN /* workaround doxygen bug */
#endif
namespace dcps { 
namespace ContentFilteredTopic {
namespace isocpp  {
	//publisher  和 sub
int publisher(int argc, char *argv[])
{
    int result = 0;
    try
    {
        /** A dds::domain::DomainParticipant is created for the default domain. */
        dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());

        /** The Durability::Transient policy is specified as a dds::topic::qos::TopicQos
         * so that even if the subscriber does not join until after the sample is written
         * then the DDS will still retain the sample for it. The Reliability::Reliable
         * policy is also specified to guarantee delivery. */
        dds::topic::qos::TopicQos topicQos
             = dp.default_topic_qos()
                << dds::core::policy::Durability::Transient()
                << dds::core::policy::Reliability::Reliable();

        /** A dds::topic::Topic is created for our sample type on the domain participant. */
        dds::topic::Topic<StockMarket::Trans> topic(dp, "StockTrackerExclusive", topicQos);

        /** A dds::pub::Publisher is created on the domain participant. */
        std::string name = "ContentFilteredTopic example";
        dds::pub::qos::PublisherQos pubQos
            = dp.default_publisher_qos()
                << dds::core::policy::Partition(name);
        dds::pub::Publisher pub(dp, pubQos);

        /** The dds::pub::qos::DataWriterQos is derived from the topic qos and the
         * WriterDataLifecycle::ManuallyDisposeUnregisteredInstances policy is
         * specified as an addition. This is so the publisher can optionally be run (and
         * exit) before the subscriber. It prevents the middleware default 'clean up' of
         * the topic instance after the writer deletion, this deletion implicitly performs
         * DataWriter::unregister_instance */
        dds::pub::qos::DataWriterQos dwqos = topic.qos();
        dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();

        /** A dds::pub::DataWriter is created on the Publisher & Topic with the modififed Qos. */
        dds::pub::DataWriter<StockMarket::Trans> dw(pub, topic, dwqos);

        /** Two samples are created */
        StockMarket::Trans geQuote(12.00f,"GE");

        StockMarket::Trans msftQuote(25.00f, "MSFT");

        /** Update sample data and write data each second for 20 seconds */
        for (unsigned int i = 0; i < write_loop_count; i++)
        {
            geQuote.typee() += 0.5f;
            msftQuote.typee() += 1.5f;
            std::cout << "=== [ContentFilteredTopicDataPublisher] sends 2 stockQuotes : (GE, "
                      << geQuote.info() << ") (MSFT, " << msftQuote.typee() << ")" << std::endl;
            dw << geQuote;
            dw << msftQuote;
            exampleSleepMilliseconds(1000);
        }

        /** A signal to terminate is sent to the subscriber */
        geQuote.typee() = -1;
        msftQuote.typee() = -1;
        dw << geQuote;
        dw << msftQuote;
        /* A short sleep ensures time is allowed for the sample to be written to the network.
        If the example is running in *Single Process Mode* exiting immediately might
        otherwise shutdown the domain services before this could occur */
        exampleSleepMilliseconds(1000);
    }
    catch (const dds::core::Exception& e)
    {
        std::cerr << "ERROR: Exception: " << e.what() << std::endl;
        result = 1;
    }
    return result;
}
int subscriber(int argc, char *argv[])
{
    int result = 0;
    try
    {
        /** A check is performed to determine if a subscription string has been supplied to the program as an
         *  argument a string value of GE will subscribe to stocks from GE and a string value of MSFT will subscribe
         *  to stocks from MSFT. Failing to provide a string will cause the program to exit. */
        if(argc < 2)
        {
            std::cerr << "*** [ContentFilteredTopicDataSubscriber] Subscription string not specified" << std::endl;
            std::cerr << "*** usage : ContentFilteredTopicDataSubscriber <subscription_string>" << std::endl;
            return  - 1;
        }

        std::string requested_ticker = argv[1];

        /** A domain participant and topic are created identically as in
         the ::publisher */
        dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
        dds::topic::qos::TopicQos topicQos = dp.default_topic_qos()
                                                    << dds::core::policy::Durability::Transient()
                                                    << dds::core::policy::Reliability::Reliable();
        dds::topic::Topic<StockMarket::Trans> topic(dp, "StockTrackerExclusive", topicQos);

        /** A dds::sub::Subscriber is created on the domain participant. */
        std::string name = "ContentFilteredTopic example";
        dds::sub::qos::SubscriberQos subQos
            = dp.default_subscriber_qos()
                << dds::core::policy::Partition(name);
        dds::sub::Subscriber sub(dp, subQos);

        /** The dds::sub::qos::DataReaderQos are derived from the topic qos */
        dds::sub::qos::DataReaderQos drqos = topic.qos();

        /** A dds::topic::ContentFilteredTopic is created filtered on the stock ticker supplied to the
         * program as an argument */
        std::stringstream ss;
        ss << "ticker = '" << requested_ticker << "'";
        dds::topic::Filter filter(ss.str());
        dds::topic::ContentFilteredTopic<StockMarket::Trans> cftopic(topic, "CFStockTrackerExclusive", filter);

        /** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
        dds::sub::DataReader<StockMarket::Trans> dr(sub, cftopic, drqos);

        /** An attempt to take samples is made repeatedly until a stock with a price of -1 is received,
         * or sixty seconds have elapsed. */
        bool terminate_sample_received = false;
        unsigned int correct_quote_count = 0;
        for (unsigned int count = 0; count < write_loop_count * 10 && !terminate_sample_received; ++count)
        {
            dds::sub::LoanedSamples<StockMarket::Trans> samples = dr.take();
            for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
                 sample < samples.end();
                 ++sample)
            {
				sample->info().timestamp().sec();
                if(sample->info().valid())
                {
                    if (sample->data().typee() == -1)
                    {
                        terminate_sample_received = true;
                        break;
                    }
                    std::cout << "=== [ContentFilteredTopicDataSubscriber] receives stockQuote :  ("
                    << sample->data().info() << ", " << sample->data().typee() << ")" << std::endl;

                    if (requested_ticker == sample->data().info())
                        ++correct_quote_count;
                    else
                    {
                        std::cerr << "=== [ContentFilteredTopicDataSubscriber] Unexpected quote received for "
                                  << sample->data().info() << std::endl;
                        result = 1;
                    }
                }
            }
            exampleSleepMilliseconds(900);
			
        }

        /** The results are confirmed to be as expected */
        if (terminate_sample_received)
        {
            std::cout << "=== [ContentFilteredTopicDataSubscriber] Market Closed." << std::endl;
            if (correct_quote_count != (requested_ticker == "GE" || requested_ticker == "MSFT" ? write_loop_count : 0))
            {
                std::cerr << "=== [ContentFilteredTopicDataSubscriber] Incorrect quote count." << std::endl;
                result = 1;
            }
        }
        else
        {
            std::cerr << "=== [ContentFilteredTopicDataSubscriber] Timed out waiting for close signal." << std::endl;
            result = 1;
        }
    }
    catch (const dds::core::Exception& e)
    {
        std::cerr << "ERROR: Exception: " << e.what() << std::endl;
        result = 1;
    }
    return result;
}

int Midware()
{//中间件，负责接收和发送全部操作。
	//保存股市active，各个股的active
	
	dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topic
		= dp.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();

	//创建发送器 Mid2Event
	dds::topic::Topic<StockMarket::Trans> topic_Mid2Event(dp, "Mid2Event", topic);
	std::string name_Mid2Event = "Mid2Event";
	dds::pub::qos::PublisherQos pubQos_Mid2Event
		= dp.default_publisher_qos()
		<< dds::core::policy::Partition(name_Mid2Event);
	dds::pub::Publisher pub_Mid2Event(dp, pubQos_Mid2Event);
	dds::pub::qos::DataWriterQos dwqos_Mid2Event = topic_Mid2Event.qos();
	dwqos_Mid2Event << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
	dds::pub::DataWriter<StockMarket::Trans> dw_Mid2Event(pub_Mid2Event, topic_Mid2Event, dwqos_Mid2Event);
	//创建接收器 Event2Mid
	dds::topic::Topic<StockMarket::Trans> topic_Event2Mid(dp, "Event2Mid", topic);
	std::string name_Event2Mid = "Event2Mid";
	dds::sub::qos::SubscriberQos subQos_Event2Mid
		= dp.default_subscriber_qos()
		<< dds::core::policy::Partition(name_Event2Mid);
	dds::sub::Subscriber sub_Event2Mid(dp, subQos_Event2Mid);
	dds::sub::qos::DataReaderQos drqos_Event2Mid = topic_Event2Mid.qos();
	dds::sub::DataReader<StockMarket::Trans> dr_Event2Mid(sub_Event2Mid, topic_Event2Mid, drqos_Event2Mid);


	//创建发送器 Mid2Client
	dds::topic::Topic<StockMarket::Trans> topic_Mid2Client(dp, "Mid2Client", topic);
	std::string name_Mid2Client = "Mid2Client";
	dds::pub::qos::PublisherQos pubQos_Mid2Client
		= dp.default_publisher_qos()
		<< dds::core::policy::Partition(name_Mid2Client);
	dds::pub::Publisher pub_Mid2Client(dp, pubQos_Mid2Client);
	dds::pub::qos::DataWriterQos dwqos_Mid2Client = topic_Mid2Client.qos();
	dwqos_Mid2Client << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
	dds::pub::DataWriter<StockMarket::Trans> dw_Mid2Client(pub_Mid2Client, topic_Mid2Client, dwqos_Mid2Client);
	//创建接收器
	dds::topic::Topic<StockMarket::Trans> topic_Client2Mid(dp, "Client2Mid", topic);
	std::string name_Client2Mid = "Client2Mid";
	dds::sub::qos::SubscriberQos subQos_Client2Mid
		= dp.default_subscriber_qos()
		<< dds::core::policy::Partition(name_Client2Mid);
	dds::sub::Subscriber sub_Client2Mid(dp, subQos_Client2Mid);
	dds::sub::qos::DataReaderQos drqos_Client2Mid = topic_Client2Mid.qos();
	dds::sub::DataReader<StockMarket::Trans> dr_Client2Mid(sub_Client2Mid, topic_Client2Mid, drqos_Client2Mid);

	//创建接收器 Mar2Mid
	dds::topic::Topic<StockMarket::Trans> topic_Market2Mid(dp, "Market2Mid", topic);
	std::string name_Market2Mid = "Market2Mid";
	dds::sub::qos::SubscriberQos subQos_Market2Mid
		= dp.default_subscriber_qos()
		<< dds::core::policy::Partition(name_Market2Mid);
	dds::sub::Subscriber sub_Market2Mid(dp, subQos_Market2Mid);
	dds::sub::qos::DataReaderQos drqos_Market2Mid = topic_Market2Mid.qos();
	dds::sub::DataReader<StockMarket::Trans> dr_Market2Mid(sub_Market2Mid, topic_Market2Mid, drqos_Market2Mid);

	bool marketActive=1,extractStock=0;//从交易所传过来的信息中提取股票名，存在stockActive[][0]中，[][1]表示状态
	string stockActive[5][2];//暂定五只股票

	while (1)
	{
		//检查交易所方面的信息
		dds::sub::LoanedSamples<StockMarket::Trans> samples = dr_Market2Mid.take();
		for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
			sample < samples.end();
			++sample)
		{
			if (sample->info().valid())
			{
				if (!extractStock)//还没提取出信息
				{
					string tmpstr = sample->data().info();
					// -> ->从tmp中提取出所有股票的名字到stockActive[][0]中 <-<-
				}
				cout << "== Message from Market ==" << endl
					<< sample->data().info() << endl
					<< "Sent it to Client" << endl;
				StockMarket::Trans broat2Client(1, sample->data().info());
				dw_Mid2Client << broat2Client;
			}
		}
		//检查客户端方面的信息
		dds::sub::LoanedSamples<StockMarket::Trans> samples = dr_Client2Mid.take();
		for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
			sample < samples.end();
			++sample)
		{
			if (sample->info().valid())
			{
				cout << "== Message from Client ==" << endl
					<< sample->data().info() << endl;
				//检查交易是否能够成功
				bool succes = 1;
				if (marketActive == false)
				{
					StockMarket::Trans ret(4, "当前处于闭市，请稍后");
					cout << "return to Client :" << endl << "当前处于闭市，请稍后" << endl;
					dw_Mid2Event << ret;
					succes = 0;
				}
				else //检查单只股票是否能够交易
				{
					int i = 0;
					for (i = 0; i < 5; i++)
					{
						//                 ->-> 通过传过来的信息，提取购买股票的名字   <-<-
						if (!stockActive[i][0].compare("这里提取购买股票的名字"))
						{
							if (!stockActive[i][1].compare("false"))
							{
								StockMarket::Trans ret(4, "该股票暂停交易");
								cout << "return to Client :" << endl << "该股票暂停交易" << endl;
								dw_Mid2Event << ret;
								succes = 0;
								break;
							}
						}
					}
				}
				if(succes)   // (成功)
				{
					StockMarket::Trans tmp(5, sample->data().info());
					dw_Mid2Event << tmp;
					StockMarket::Trans ret(4, "成功！");
					dw_Mid2Event << ret;
				}
			}
		}

		//检查事件发布者的信息
		dds::sub::LoanedSamples<StockMarket::Trans> samples = dr_Event2Mid.take();
		for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
			sample < samples.end();
			++sample)
		{
			if (sample->info().valid())
			{
				cout << "== Message from Eventor ==" << endl
					<< sample->data().info() << endl;
				if (sample->data().typee() == 8)
				{//市场信息
					string information;
					if (!sample->data().info().compare("Market closed"))
					{
						marketActive = false;
						information = "股市关闭，20秒后继续交易";
					}
					else
					{
						marketActive = true;
						information = "股市开启，可以继续交易";
					}
					StockMarket::Trans notice(9, information);
					dw_Mid2Client << notice;
					cout << "Message has sent to client: " << endl;
					cout << information<< endl;
				}
				else if (sample->data().typee() == 7)
				{//某只股票要暂停或开放
					string payload;
					int n = stoi(sample->data().info());
					stockActive[n][1] = stockActive[n][1].compare("false") == 0 ? "true" : "false";
					payload = "股票：" + stockActive[n][0];
					payload += stockActive[n][1].compare("false") == 0 ? "暂停交易" : "继续交易";
					StockMarket::Trans notice(9, payload);
					dw_Mid2Client << notice;
					cout << "Message has sent to client: " << endl;
					cout << payload << endl;
				}
				else if (sample->data().typee() == 6)
				{//发布总行情
					string payload;
					cout << "Message has sent to client: " << endl << sample->data().info() << endl;
					StockMarket::Trans notice(9, sample->data().info());
					dw_Mid2Client << notice;
				}

				
			}
		}
	}

	return 0;
}

int Market()
{//创建发送装置，将股票信息发送出去
	//运行在交易所，本地保存着股票文件
	dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topicQos
		= dp.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();
	dds::topic::Topic<StockMarket::Trans> topic(dp, "Market2Mid", topicQos);
	std::string name = "Market2Mid";
	dds::pub::qos::PublisherQos pubQos
		= dp.default_publisher_qos()
		<< dds::core::policy::Partition(name);
	dds::pub::Publisher pub(dp, pubQos);
	dds::pub::qos::DataWriterQos dwqos = topic.qos();
	dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
	dds::pub::DataWriter<StockMarket::Trans> dw(pub, topic, dwqos);
	exampleSleepMilliseconds(1000);
	Exchange market;
	market.importStock("stockInfo.txt");
	while (1)
	{
		market.adjustStocks();//random股市随机变动
		string allStock,tmpstr;
		int i = 0;
		for (i = 0; i < market.cont; i++)
		{//将内存中全部的股票写到allstock中，一次性发送出去
			allStock += market.stocks[i].stockID;
			allStock += ";";
			allStock += market.stocks[i].name;
			allStock += ";";
			allStock += to_string(market.stocks[i].pricee);
			allStock += ";";
			allStock += time(0) + ";";//这里增加了一个时间戳
			allStock += market.stocks[i].details;
			allStock += "|";
		}
		StockMarket::Trans msg(0.0,allStock);
		dw << msg;
		cout << "=== [Stock Market] ==="<<endl
			<< "message type:"<<msg.typee() <<endl
			<< "message content:" <<msg.info() << endl;
		Sleep(5);//每五秒发送一次
	}

	return 0;
}

int Event()
{//事件发布者,本地当前目录存储行情文件
	//创建发送器
	dds::domain::DomainParticipant dp_send(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topicQos_send
		= dp_send.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();
	dds::topic::Topic<StockMarket::Trans> topic_send(dp_send, "Event2Mid", topicQos_send);
	std::string name_send = "Event2Mid";
	dds::pub::qos::PublisherQos pubQos
		= dp_send.default_publisher_qos()
		<< dds::core::policy::Partition(name_send);
	dds::pub::Publisher pub(dp_send, pubQos);
	dds::pub::qos::DataWriterQos dwqos = topic_send.qos();
	dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
	dds::pub::DataWriter<StockMarket::Trans> dw(pub, topic_send, dwqos);
	//创建接收器
	dds::domain::DomainParticipant dp_read(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topicQos_read
		= dp_read.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();
	dds::topic::Topic<StockMarket::Trans> topic_read(dp_read, "Mid2Event", topicQos_read);
	std::string name_read = "Mid2Event";
	dds::sub::qos::SubscriberQos subQos
		= dp_read.default_subscriber_qos()
		<< dds::core::policy::Partition(name_read);
	dds::sub::Subscriber sub(dp_read, subQos);
	dds::sub::qos::DataReaderQos drqos = topic_read.qos();
	dds::sub::DataReader<StockMarket::Trans> dr(sub, topic_read, drqos);
	int RussianRoulette;
	long long TimeRound = 0;
	while (1)
	{
		TimeRound++;
		dds::sub::LoanedSamples<StockMarket::Trans> samples = dr.take();
		for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
			sample < samples.end();
			++sample)
		{
			if (sample->info().valid())
			{//有行情信息进来，追加写到文件里
				ofstream Quotation("Quotation.txt", ios::app);
				Quotation << sample->data().info() << "|" << time(0) << endl;
				//时间弄得不知道对不对
				Quotation.close();
			}
		}
		RussianRoulette = random(50);
		if (TimeRound%100 == 0)
		{//闭市
			StockMarket::Trans MarketChange(8, "Market closed");
			dw << MarketChange;
			//每次闭市发送当交易日全部交易
			ifstream MarketDetail("Quotation.txt");
			string payload,tmpstr;
			while (getline(MarketDetail, tmpstr))
				payload += tmpstr;
			StockMarket::Trans allQuo(6,payload);
			dw << allQuo;
			exampleSleepMilliseconds(20000);//暂定20s
			StockMarket::Trans MarketChange(8, "Market open");
			dw << MarketChange;
			
		}
		else if (RussianRoulette == 25)
		{//随便挑一个股翻转状态。
			RussianRoulette = random(5);
			StockMarket::Trans StockChange(7, to_string(RussianRoulette));
			dw << StockChange;
		}
		exampleSleepMilliseconds(2000);
	}
	return 0;
}

int Client()
{
	string username, password,tmpstr;
	User tmp;
	//这里通过界面获得用户名和密码
	tmpstr = tmp.checkLogin(username, password);
	//界面显示tmpstr(返回值)
	while(tmpstr.compare("登录成功!"))
	{
		//通过界面重新获得用户名和密码,for example:
		username = "hello";
		password = "world";
		tmpstr = tmp.checkLogin(username, password);
		//界面显示tmpstr(返回值)
	}
	User logining(username + ".txt");
	Stock containt[100];
	//创建接收器
	dds::domain::DomainParticipant dp_read(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topicQos_read
		= dp_read.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();
	dds::topic::Topic<StockMarket::Trans> topic_read(dp_read, "Mid2Client", topicQos_read);
	std::string name_read = "Mid2Client";
	dds::sub::qos::SubscriberQos subQos
		= dp_read.default_subscriber_qos()
		<< dds::core::policy::Partition(name_read);
	dds::sub::Subscriber sub(dp_read, subQos);
	dds::sub::qos::DataReaderQos drqos = topic_read.qos();
	dds::sub::DataReader<StockMarket::Trans> dr(sub, topic_read, drqos);
	/************************************************************/
	//这里开始多线程，一边持续接收股票信息，一边响应按钮槽函数
	//接收股票信息的
	int received = 0, success = 0;//标记买卖信息是否收到，是否成功
	while (1)
	{
		dds::sub::LoanedSamples<StockMarket::Trans> samples = dr.take();
		for (dds::sub::LoanedSamples<StockMarket::Trans>::const_iterator sample = samples.begin();
			sample < samples.end();
			++sample)
		{
			
			if (sample->info().valid())
			{
				if (sample->data().typee() == 4)//返回得买卖结果的信息
				{
					received = 1;
					if (sample->data().info().compare("成功！"))
						success = 1;//在另一个进程进行扣款
					// -> 弹窗显示收到的字符串 <-
				}
				else if (sample->data().typee() == 1)//显示在界面上的
				{
					//界面上对sample->data().info进行解析，
									// -> -> 存储在containt数组里面   <- <-
									//在界面上显示那一堆东西
					cout << sample->data().info() << endl;

				}
				else//通知，公告
				{
					//在公告栏显示公告内容
					cout << sample->data().info() << endl;
				}
			}
		}
	}
	//////////响应槽函数的

	//on click BUY
	{
		//获取股票名字，数量
		string buyName;
		int num;
		for (int i = 0;; i++)
		{
			if (containt[i].name.compare(buyName) == 0)
			{
				if (containt[i].pricee * num <= logining.cash)
				{
					logining.buy(buyName, num);
					while (!received);
					if (success)
					{
						int j;
						logining.cash -= containt[i].pricee * num;
						for (j = 0; j < logining.holdNum; j++)
						{
							if (logining.hold[j].stockName.compare(buyName) == 0)
								logining.hold[j].number += num;
						}
						if (j == logining.holdNum)//新购
						{
							logining.holdNum++;
							logining.hold[j].stockName = buyName;
							logining.hold[j].number = num;
						}
						//刷新界面
					}
				}
				else
				{
					//界面显示“余额不足，你买个锤子！”
					break;
				}
			}
		}
	

	}
	//on click SELL
	{
		//获取股票名字，数量
		string buyName;
		int num;
		for (int i = 0;; i++)
		{
			if (logining.hold[i].stockName.compare(buyName) == 0)
			{
				if (logining.hold[i].number >= num)
				{
					logining.sell(buyName, num);
					while (!received);
					if (success)
					{
						for (int j = 0; j < logining.holdNum; j++)
						{
							if (containt[i].name.compare(buyName) == 0)
								logining.cash += containt[i].pricee * num;
						}
						//刷新界面
					}
				}
				else
				{
					//界面显示“你想卖多少啊，也不瞧瞧自己有几个”
					break;
				}
			}
		}
	}



	return 0;
}

string User::checkLogin(string userName, string password)
{
	ifstream userFile(userName + ".txt");
	if (!userFile)
		return "用户不存在！";
	string tmpstr;
	getline(userFile, tmpstr);
	getline(userFile, tmpstr);
	if (password.compare(tmpstr))
		return "密码错误！";
	return "登录成功!";
}

void User::buy(string stockname, int number)
{//只向交易所发送交易信息，不负责接收,和股票信息一起进行接收
	sendMsg(name, stockname, number,2);
}

void User::sell(string stockname, int number)
{
	sendMsg(name, stockname, number, 3);
}
void User::sendMsg(string username, string stockname, int num,int tYpe)
{
	dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
	dds::topic::qos::TopicQos topicQos
		= dp.default_topic_qos()
		<< dds::core::policy::Durability::Transient()
		<< dds::core::policy::Reliability::Reliable();
	dds::topic::Topic<StockMarket::Trans> topic(dp, "Client2Mid", topicQos);
	std::string name = "Client2Mid";
	dds::pub::qos::PublisherQos pubQos
		= dp.default_publisher_qos()
		<< dds::core::policy::Partition(name);
	dds::pub::Publisher pub(dp, pubQos);
	dds::pub::qos::DataWriterQos dwqos = topic.qos();
	dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
	dds::pub::DataWriter<StockMarket::Trans> dw(pub, topic, dwqos);
	exampleSleepMilliseconds(1000);
	string payload = name + ";" + stockname + ";" + to_string(num);
	StockMarket::Trans msg(tYpe, payload);
}
void User::saveUser(string path)
{
	ofstream fileName(path);
	fileName << name << endl;
	fileName << password << endl;
	fileName << cash << endl;
	fileName << holdNum << endl;
	fileName << careNum << endl;
	for (int i = 0; i < holdNum; ++i)
	{
		if (hold[i].number)//有则写入进去
			fileName << hold[i].stockName << ':' << hold[i].number << endl;
	}
	for (int i = 0; i < careNum; ++i)
	{
		fileName << care[i] << endl;
	}
}
User::User(string path)
{
	int pos, len;
	string str;
	string StockNum;
	ifstream fileName(path);
	//name
	getline(fileName, name);
	getline(fileName, password);
	getline(fileName, str);
	cash = stof(str);
	getline(fileName, str);
	holdNum = stoi(str);
	getline(fileName, str);
	careNum = stoi(str);

	for (int i = 0; i < holdNum; ++i)
	{
		getline(fileName, str);
		pos = str.find(":");
		len = str.length();
		StockNum = str.substr(pos + 1, len);
		hold[i].number = stoi(StockNum);
		hold[i].stockName = str.substr(0, pos);
	}
	for (int i = 0; i < careNum; ++i)
		getline(fileName, care[i]);
}
Having::Having()
{
	stockName = "";
	number = 0;
}

float Stock::getPrice()
{
	return pricee;
}

float Stock::setPrice(float newPrice)
{
	pricee =newPrice;
	return pricee;
}

float Stock::increase(float range)//上涨range%
{
	pricee *= 1 + range/100;
	return pricee;
}

Exchange::Exchange()
{
	cont = 0;
}

void Exchange::importStock(string filename)
{//从文件中将全部股票加载入market中
	int i = 0;
	ifstream stockFile(filename);
	Stock tmp;
	string tmpstr;
	while (getline(stockFile, tmpstr))
	{
		i++;
		switch (i%4)
		{
		case 1:
			tmp.stockID = tmpstr;
			break;
		case 2:
			tmp.name = tmpstr;
			break;
		case 3:
			tmp.pricee = stof(tmpstr);
			break;
		case 0:
			tmp.details = tmpstr;
			break;
		default:
			break;
		} 
		if (i % 4 == 0)
			stocks.push_back(tmp);
	}
	cont = i / 4;	
}


void Exchange::saveStocks()
{
	//程序关闭时运行
	ofstream stockInfo("stockInfo.txt");
	for (int i = 0; i < cont; i++)
	{//将所有股票的信息全部存入文件中保存。
		stockInfo << stocks[i].stockID << endl;
		stockInfo << stocks[i].name << endl;
		stockInfo << stocks[i].pricee << endl;
		stockInfo << stocks[i].details << endl;
	}
}

void Exchange::adjustStocks()
{
	srand((int)time(0));
	for (int i = 0; i < cont; i++)
	{
		float range = random(1000) / 100.0 - 5;
		stocks[i].increase(range);
	}
}



}
}
}
}

EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_ContentFilteredTopic_publisher, examples::dcps::ContentFilteredTopic::isocpp::publisher)
EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_ContentFilteredTopic_subscriber, examples::dcps::ContentFilteredTopic::isocpp::subscriber)
