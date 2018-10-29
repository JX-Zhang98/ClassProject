#include "implementation.hpp"
#include "common/example_utilities.h"
#include <fstream>
#include <sstream>
#include "ContentFilteredTopicData_DCPS.hpp"
#define random(x) (rand()%x)

namespace {
    const unsigned int write_loop_count = 20;
}

namespace examples {
#ifdef GENERATING_EXAMPLE_DOXYGEN
GENERATING_EXAMPLE_DOXYGEN /* workaround doxygen bug */
#endif
namespace dcps { namespace ContentFilteredTopic {
namespace isocpp  {

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
        dds::topic::Topic<StockMarket::Stock> topic(dp, "StockTrackerExclusive", topicQos);

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
        dds::pub::DataWriter<StockMarket::Stock> dw(pub, topic, dwqos);

        /** Two samples are created */
        StockMarket::Stock geQuote("GE", 12.00f);

        StockMarket::Stock msftQuote("MSFT", 25.00f);

        /** Update sample data and write data each second for 20 seconds */
        for (unsigned int i = 0; i < write_loop_count; i++)
        {
            geQuote.price() += 0.5f;
            msftQuote.price() += 1.5f;
            std::cout << "=== [ContentFilteredTopicDataPublisher] sends 2 stockQuotes : (GE, "
                      << geQuote.price() << ") (MSFT, " << msftQuote.price() << ")" << std::endl;
            dw << geQuote;
            dw << msftQuote;
            exampleSleepMilliseconds(1000);
        }

        /** A signal to terminate is sent to the subscriber */
        geQuote.price() = -1;
        msftQuote.price() = -1;
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
        dds::topic::Topic<StockMarket::Stock> topic(dp, "StockTrackerExclusive", topicQos);

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
        dds::topic::ContentFilteredTopic<StockMarket::Stock> cftopic(topic, "CFStockTrackerExclusive", filter);

        /** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
        dds::sub::DataReader<StockMarket::Stock> dr(sub, cftopic, drqos);

        /** An attempt to take samples is made repeatedly until a stock with a price of -1 is received,
         * or sixty seconds have elapsed. */
        bool terminate_sample_received = false;
        unsigned int correct_quote_count = 0;
        for (unsigned int count = 0; count < write_loop_count * 10 && !terminate_sample_received; ++count)
        {
            dds::sub::LoanedSamples<StockMarket::Stock> samples = dr.take();
            for (dds::sub::LoanedSamples<StockMarket::Stock>::const_iterator sample = samples.begin();
                 sample < samples.end();
                 ++sample)
            {
                if(sample->info().valid())
                {
                    if (sample->data().price() == -1)
                    {
                        terminate_sample_received = true;
                        break;
                    }
                    std::cout << "=== [ContentFilteredTopicDataSubscriber] receives stockQuote :  ("
                    << sample->data().ticker() << ", " << sample->data().price() << ")" << std::endl;

                    if (requested_ticker == sample->data().ticker())
                        ++correct_quote_count;
                    else
                    {
                        std::cerr << "=== [ContentFilteredTopicDataSubscriber] Unexpected quote received for "
                                  << sample->data().ticker() << std::endl;
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

bool User::buy(string stockID, int number)
{//ֻ���������ͽ�����Ϣ����������գ�������Ϣ��
	//�������ť�󵯳�������Ϣ�򣬵õ�����Ĺ�Ʊ��Ϣ,ͨ���������ôκ�����

	bool result;
	try
	{
		dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
		dds::topic::qos::TopicQos topicQos
			= dp.default_topic_qos()//������ô��ɶ���Լӿ촫���ٶȣ��ʺ���
			<< dds::core::policy::Durability::Transient()
			<< dds::core::policy::Reliability::Reliable();
		/*������Ҫ���б�ʶ��˫����Ҫ����һ��*/
		dds::topic::Topic<StockMarket::BuyInfo> topic(dp, "StockTrackerExclusive", topicQos);
		std::string name = "ContentFilteredTopic example";
		/************************************/
		dds::pub::qos::PublisherQos pubQos
			= dp.default_publisher_qos()
			<< dds::core::policy::Partition(name);
		dds::pub::Publisher pub(dp, pubQos);
		dds::pub::qos::DataWriterQos dwqos = topic.qos();
		dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
		dds::pub::DataWriter<StockMarket::BuyInfo> dw(pub, topic, dwqos);
		
		StockMarket::BuyInfo buyAsk(id,stockID,number);
		cout << "ask to buy :" << endl << "user:  " << id << endl <<
			"stock:  " << stockID << endl << "number :  " << number << endl;
		dw << buyAsk;
		exampleSleepMilliseconds(100);
	}
	catch (const dds::core::Exception& e)
	{
		std::cerr << "ERROR: Exception: " << e.what() << std::endl;
		result = 1;
	}
	return result;
}

bool User::sell(string stockID, int number)
{
	bool result;
	try
	{
		dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
		dds::topic::qos::TopicQos topicQos
			= dp.default_topic_qos()//������ô��ɶ���Լӿ촫���ٶȣ��ʺ���
			<< dds::core::policy::Durability::Transient()
			<< dds::core::policy::Reliability::Reliable();
		/*������Ҫ���б�ʶ��˫����Ҫ����һ��*/
		dds::topic::Topic<StockMarket::BuyInfo> topic(dp, "StockTrackerExclusive", topicQos);
		std::string name = "ContentFilteredTopic example";
		/************************************/
		dds::pub::qos::PublisherQos pubQos
			= dp.default_publisher_qos()
			<< dds::core::policy::Partition(name);
		dds::pub::Publisher pub(dp, pubQos);
		dds::pub::qos::DataWriterQos dwqos = topic.qos();
		dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
		dds::pub::DataWriter<StockMarket::SellInfo> dw(pub, topic, dwqos);

		StockMarket::SellInfo sellAsk(id, stockID, number);
		cout << "ask to sell :" << endl << "user:  " << id << endl <<
			"stock:  " << stockID << endl << "number :  " << number << endl;
		dw << sellAsk;
		exampleSleepMilliseconds(100);
	}
	catch (const dds::core::Exception& e)
	{
		std::cerr << "ERROR: Exception: " << e.what() << std::endl;
		result = 1;
	}
	return result;
}

User User::FlushInfo()
{//���շ��������͵��û���Ϣ��
	bool result;
	try
	{
		dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
		dds::topic::qos::TopicQos topicQos
			= dp.default_topic_qos()//������ô��ɶ���Լӿ촫���ٶȣ��ʺ���
			<< dds::core::policy::Durability::Transient()
			<< dds::core::policy::Reliability::Reliable();
		/*������Ҫ���б�ʶ��˫����Ҫ����һ��*/
		dds::topic::Topic<StockMarket::BuyInfo> topic(dp, "StockTrackerExclusive", topicQos);
		std::string name = "ContentFilteredTopic example";
		/************************************/
		dds::pub::qos::PublisherQos pubQos
			= dp.default_publisher_qos()
			<< dds::core::policy::Partition(name);
		dds::pub::Publisher pub(dp, pubQos);
		dds::pub::qos::DataWriterQos dwqos = topic.qos();
		dwqos << dds::core::policy::WriterDataLifecycle::AutoDisposeUnregisteredInstances();
		dds::pub::DataWriter<StockMarket::UserInfo> dw(pub, topic, dwqos);

		StockMarket::UserInfo userInfoAsk(id, stockID, number);
		cout << "ask to sell :" << endl << "user:  " << id << endl <<
			"stock:  " << stockID << endl << "number :  " << number << endl;
		dw << sellAsk;
		exampleSleepMilliseconds(100);
	}
	catch (const dds::core::Exception& e)
	{
		std::cerr << "ERROR: Exception: " << e.what() << std::endl;
		result = 1;
	}
	return result;
}

Having::Having()
{
	stockID = "";
	number = 0;
}

void Stock::StockClose()
{
	active = false;
}

void Stock::StockOpen()
{
	active = true;
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

float Stock::increase(float range)
{
	pricee *= 1 + range/100;
	return pricee;
}

Exchange* Exchange::getInstance()
{//����Ψһ����
	return singleInstance;
}

void Exchange::stopEx()
{
	active = 0;
}

void Exchange::goEx()
{
	active = 1;
}

string Exchange::toBuy(int userID, string stockID, int num)
{
	//�������Ƿ��㹻
	string tmpPath = "User\\" + to_string(userID);
	User tmpUser(tmpPath);
	Stock* tmpStock;
	int i = 0,flag=0;
	for (i = 0; i < cont; i++)
	{
		if (!stocks[i].stockID.compare(stockID))
		{
			tmpStock = &stocks[i];
			break;
		}
	}
	if (tmpStock->reminder < num)
		return "��Ʊ�������㣬����ٹ�������";
	if (tmpUser.cash < num*tmpStock->pricee)
		return "���㣬�뼰ʱ��ֵ";
	//�ܹ��ɹ�����
	tmpUser.cash -= num * tmpStock->pricee;
	tmpStock->reminder -= num;
	for (i = 0; i < tmpUser.holdNum; i++)
	{
		if (!tmpUser.hold[i].stockID.compare(stockID))
		{
			tmpUser.hold[i].number += num;
			flag = 1;//�ҵ������й�Ʊ
			break;
		}
	}
	if (!flag)//û���ҵ����й�Ʊ
	{
		tmpUser.hold[tmpUser.holdNum++].stockID = stockID;
		tmpUser.hold[tmpUser.holdNum++].number = num;
	}
	tmpUser.saveUser(tmpPath);
	return "����ɹ���";
}

string Exchange::toSell(int userID, string stockID, int num)
{
	string tmpPath = "User\\" + to_string(userID);
	User tmpUser(tmpPath);
	Stock* tmpStock;
	int i = 0, flag = 0;
	for (i = 0; i < cont; i++)
	{
		if (!stocks[i].stockID.compare(stockID))
		{
			tmpStock = &stocks[i];
			break;
		}
	}
	for (i = 0; i < tmpUser.holdNum; i++)
	{
		if (!tmpUser.hold[i].stockID.compare(stockID)&& !tmpUser.hold[i].number)
		{
			flag = 1;//�����ֹ�Ʊ
			if (tmpUser.hold[i].number < num)
				return "�����������㣬������ȷ�ϳ���������";
			tmpUser.hold[i].number -= num;//�����Ż�����������==0��������˳��У�holdnum--��
			tmpUser.cash += num * tmpStock->pricee;
			tmpStock->reminder += num;
		}
	}
	if (!flag)
		return "δ���д˹�Ʊ��������ȷ�ϡ�";

}

vector <Stock> Exchange::getInfo()
{
	vector <Stock> allStockInfo;
	for (int i = 0; i < cont; i++)
	{
		allStockInfo.push_back(stocks[i]);
	}
	return allStockInfo;
}

User Exchange::checkLogin(string userName, string password)
{//��¼�ɹ�֮���û���Ϣ����
	string tmpPath = "User\\" + userName;
	User tmpUser(tmpPath);
	ifstream userFile(tmpPath);
	string passHash;
	getline(userFile, passHash);
	if (!passHash.compare(password))
		return tmpUser;
	User emptyUser;
	return emptyUser;
}

void Exchange::saveStocks()
{

	ofstream stockInfo("stocksInfo");
	for (int i = 0; i < cont; i++)
	{//�����й�Ʊ����Ϣȫ�������ļ��б��档
		stockInfo << stocks[i].stockID << endl;
		stockInfo << stocks[i].name << endl;
		stockInfo << stocks[i].details << endl;
		stockInfo << stocks[i].active << endl;
		stockInfo << stocks[i].pricee << endl;
		stockInfo << stocks[i].reminder << endl<<endl;
	}
}

void Exchange::importStocks()
{
	ifstream stockInfo("stocksInfo.txt");
	cont = 0;
	string tmpInfo;
	Stock tmpStock;
	while (1)
	{
		getline(stockInfo, tmpStock.stockID);
		getline(stockInfo, tmpStock.name);
		getline(stockInfo, tmpStock.details);
		getline(stockInfo, tmpInfo);
		tmpStock.active = (bool)stoi(tmpInfo);
		getline(stockInfo, tmpInfo);
		tmpStock.pricee = stof(tmpInfo);
		getline(stockInfo, tmpInfo);
		tmpStock.pricee = stoi(tmpInfo);
		stocks[cont++] = tmpStock;		
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
