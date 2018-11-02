#include "implementation.hpp"
#include "common/example_utilities.h"

#include <iostream>
#include <fstream>
#include "HelloWorldData_DCPS.hpp"
#include "csv.h"
#include "ExampleDataReaderListener.hpp"

using namespace std;

namespace examples {
#ifdef GENERATING_EXAMPLE_DOXYGEN
	GENERATING_EXAMPLE_DOXYGEN /* workaround doxygen bug */
#endif
namespace dcps {
namespace HelloWorld {
namespace isocpp {

	/**
	 * This function performs the publisher role in this example.
	 * @return 0 if a sample is successfully written, 1 otherwise.
	 */
	int publisher(string topicc, string namee)
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
			dds::topic::Topic<HelloWorldData::Msg> topic(dp, topicc, topicQos);

			/** A dds::pub::Publisher is created on the domain participant. */
			string name = namee;
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
			dwqos << dds::core::policy::WriterDataLifecycle::ManuallyDisposeUnregisteredInstances();

			/** A dds::pub::DataWriter is created on the Publisher & Topic with the modififed Qos. */
			dds::pub::DataWriter<HelloWorldData::Msg> dw(pub, topic, dwqos);

			exampleSleepMilliseconds(3000);
			//getchar();

			/*读取result文件，将处理结果发送回中心机*/
			ifstream res("result.csv");
			bool finished = 0;
			string tmpmsg;
			int tmpid;
			do
			{
				//按行读取文件内容。
				if (!getline(res, tmpmsg))
				{
					//给接收方发送结束信号，约定自定义生成
					HelloWorldData::Msg msgInstance(1, "End of file processing results");
					dw << msgInstance;
					res.close();
					finished = 1;
				}
				HelloWorldData::Msg msgInstance(1, tmpmsg);

				//直到发送完
				if (!finished)
				{
					//Sleep(5000);
					dw << msgInstance;
					/*cout << "=== [Publisher] writing a message containing :" << endl;
					cout << "    userID  : " << msgInstance.userID() << endl;
					cout << "    Message : \"" << msgInstance.message() << "\"" << endl;*/
				}
				exampleSleepMilliseconds(100);
			} while (!finished); // 结果发送完毕

		}
		catch (const dds::core::Exception& e)
		{
			cerr << "ERROR: Exception: " << e.what() << endl;
			result = 1;
		}
		return result;
	}

	/**
	 * Runs the subscriber role of this example.
	 * @return 0 if a sample is successfully read, 1 other wise.
	 */
	int subscriber(string topicc, string namee)
	{
		int result = 0;
		try
		{
			/** A domain participant and topic are created identically as in
			 the ::publisher */
			dds::domain::DomainParticipant dp(org::opensplice::domain::default_id());
			dds::topic::qos::TopicQos topicQos = dp.default_topic_qos()
				<< dds::core::policy::Durability::Transient()
				<< dds::core::policy::Reliability::Reliable();
			dds::topic::Topic<HelloWorldData::Msg> topic(dp, topicc, topicQos);

			/** A dds::sub::Subscriber is created on the domain participant. */
			string name = namee;
			dds::sub::qos::SubscriberQos subQos
				= dp.default_subscriber_qos()
				<< dds::core::policy::Partition(name);
			dds::sub::Subscriber sub(dp, subQos);

			/** The dds::sub::qos::DataReaderQos are derived from the topic qos */
			dds::sub::qos::DataReaderQos drqos = topic.qos();

			/***********  Try to create a listener to deal with the   ******************************/
			ExampleDataReaderListener listener;
			//解决无定义标识符
			//1. 在类名ExampleDataReaderListener前面加namespace限定符
			//examples::dcps::Listener::isocpp::ExampleDataReaderListener listener;
			//2. 将此类定义复制到Helloword命名空间中来。
			dds::core::status::StatusMask mask;
			mask << dds::core::status::StatusMask::data_available()
				<< dds::core::status::StatusMask::requested_deadline_missed();
			//create a data reader with listener
			dds::sub::DataReader<HelloWorldData::Msg> dr(sub, topic, drqos, &listener, mask);
			std::cout << "=== [ListenerDataSubscriber] Ready ..." << std::endl;
			while (!listener.deadline_expired_)
			{
				exampleSleepMilliseconds(1000);//这里理论上应该睡很短时间就可以
			}
			result = !(listener.deadline_expired_ && listener.data_received_);

			//remove the listener
			dr.listener(0, dds::core::status::StatusMask::none());
			
			std::cout << "receive finished" << endl;
			/** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
			//dds::sub::DataReader<HelloWorldData::Msg> dr(sub, topic, drqos);

			/** An attempt to take samples is made repeatedly until it succeeds,
			 * or sixty seconds have elapsed. */
			
	//		bool sourceRecvFini = false;
	//		//创建接收到的源文件source.csv
	//		ofstream sou("source.csv");
	//		do
	//		{
	//			dds::sub::LoanedSamples<HelloWorldData::Msg> samples = dr.take();
	//			for (dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator sample = samples.begin();
	//				sample < samples.end();
	//				++sample)
	//			{
	//				if (sample->info().valid())
	//				{
	//					//可以不进行输出。
	//					/*cout << "=== [Subscriber] message received :" << endl;
	//					cout << "    userID  : " << sample->data().userID() << endl;
	//					cout << "    Message : \"" << sample->data().message() << "\"" << endl;*/
	//					if (!sample->data().message().compare("File send finished!Please go on to deal with them!"))
	//						sourceRecvFini = true;
	//					else
	//						sou << sample->data().message() << endl;
	//				}
	//			}
	//		} while (!sourceRecvFini);
	//		cout << "finish" << endl;
	//		if (!sourceRecvFini)
	//		{
	//			cerr << "ERROR: Waited for 60 seconds but no sample received" << endl;
	//			result = 1;
	//		}
		}
		catch (const dds::core::Exception& e)
		{
			cerr << "ERROR: Exception: " << e.what() << endl;
			result = 1;
		}
		return result;
	}
	int test()
	{
		cout << "new func add successful!";
		return 0;
	}
	int broadcastCenter()
	{
		int result = 0;
		try
		{
			/********** 以下部分创建信息发送结构 **********************************/
			/** A dds::domain::DomainParticipant is created for the default domain. */
			dds::domain::DomainParticipant dp_send(org::opensplice::domain::default_id());

			/** The Durability::Transient policy is specified as a dds::topic::qos::TopicQos
			 * so that even if the subscriber does not join until after the sample is written
			 * then the DDS will still retain the sample for it. The Reliability::Reliable
			 * policy is also specified to guarantee delivery. */
			dds::topic::qos::TopicQos topicQos_send
				= dp_send.default_topic_qos()
				<< dds::core::policy::Durability::Transient()
				<< dds::core::policy::Reliability::Reliable();

			dds::topic::Topic<HelloWorldData::Msg> topic_send(dp_send, "InitFile", topicQos_send);

			/** A dds::pub::Publisher is created on the domain participant. */
			string name_send = "File Init";
			dds::pub::qos::PublisherQos pubQos
				= dp_send.default_publisher_qos()
				<< dds::core::policy::Partition(name_send);
			dds::pub::Publisher pub(dp_send, pubQos);

			/** The dds::pub::qos::DataWriterQos is derived from the topic qos and the
			 * WriterDataLifecycle::ManuallyDisposeUnregisteredInstances policy is
			 * specified as an addition. This is so the publisher can optionally be run (and
			 * exit) before the subscriber. It prevents the middleware default 'clean up' of
			 * the topic instance after the writer deletion, this deletion implicitly performs
			 * DataWriter::unregister_instance */
			dds::pub::qos::DataWriterQos dwqos = topic_send.qos();
			dwqos << dds::core::policy::WriterDataLifecycle::ManuallyDisposeUnregisteredInstances();

			/** A dds::pub::DataWriter is created on the Publisher & Topic with the modififed Qos. */
			//dw 是发送器， dw << msgInstance 实现发送
			dds::pub::DataWriter<HelloWorldData::Msg> dw(pub, topic_send, dwqos);



			/*********************** 以下部分创建信息接收结构 ************************************/
			/** A domain participant and topic are created identically as in
			 the ::publisher */
			dds::domain::DomainParticipant dp_recv(org::opensplice::domain::default_id());
			dds::topic::qos::TopicQos topicQos_recv = dp_recv.default_topic_qos()
				<< dds::core::policy::Durability::Transient()
				<< dds::core::policy::Reliability::Reliable();
			dds::topic::Topic<HelloWorldData::Msg> topic_recv(dp_recv, "Reply", topicQos_recv);
			//topic和name由发送方决定，跟随发送方，两个都一致时能够接收到该信息。
			/** A dds::sub::Subscriber is created on the domain participant. */
			string name_recv = "msg got";
			dds::sub::qos::SubscriberQos subQos
				= dp_recv.default_subscriber_qos()
				<< dds::core::policy::Partition(name_recv);
			dds::sub::Subscriber sub(dp_recv, subQos);
			/** The dds::sub::qos::DataReaderQos are derived from the topic qos */
			dds::sub::qos::DataReaderQos drqos = topic_recv.qos();
			/** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
			dds::sub::DataReader<HelloWorldData::Msg> dr(sub, topic_recv, drqos);



			/**************************************************************************************/
			//获得需要处理的源文件
			char filePath[100] = { 0 };
			puts("Please input the path of the file you want to send.");
			Sleep(3000);//实践表明，创建dw后需要暂停片刻实现机器间识别，否则容易丢包
			
						
			//动一下		
			//gets_s(filePath, 99);
			strcpy(filePath, "E:\\大二下综测.csv");

			ifstream f;
			f.open(filePath);
			bool finished = false;
			int count = 0;
			string tmpmsg;
			int tmpid;
			//发送者使用userID = 0；三个处理机分别使用userID = 1， 2， 3
			//添加三个接受处理结果的文件
			ofstream out1("recv1.csv");
			ofstream out2("recv2.csv");
			ofstream out3("recv3.csv");
			do
			{
				//按行读取文件内容。
				if (!getline(f, tmpmsg))
				{
					//给接收方发送结束信号，约定自定义生成
					HelloWorldData::Msg msgInstance(0, "File send finished!Please go on to deal with them!");
					dw << msgInstance;
					f.close();
					finished = 1;
				}
				HelloWorldData::Msg msgInstance(0, tmpmsg);

				if (finished)
				{
					dds::sub::LoanedSamples<HelloWorldData::Msg> samples = dr.take();
					for (dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator sample = samples.begin();
						sample < samples.end();
						++sample)
					{
						if (sample->info().valid())
						{
							//可以不进行输出，最后在同一完成输出任务
							cout << "=== [Subscriber] message received :" << endl;
							cout << "    userID  : " << sample->data().userID() << endl;
							cout << "    Message : \"" << sample->data().message() << "\"" << endl;
							/****************************************************************************/
							/******************** 这里进行接收文件处理 **********************************/
							/****************************************************************************/
							tmpid = sample->data().userID();
							tmpmsg = sample->data().message();
							if (tmpid == 1)
							{
								//将信息加入文件1
								if (!tmpmsg.compare("End of file processing results"))
								{
									count++;//每收到一个结束，count++， 到3停止接收信息。
									continue;
								}
								out1 << tmpmsg << endl;
							}
							else if (tmpid == 2)
							{
								//将信息写入第二个文件
								if (!tmpmsg.compare("End of file processing results"))
								{
									count++;//每收到一个结束，count++， 到3停止接收信息。
									continue;
								}
								out2 << tmpmsg << endl;
							}
							else if (tmpid == 3)
							{
								//写入文件三
								if (!tmpmsg.compare("End of file processing results"))
								{
									count++;//每收到一个结束，count++， 到3停止接收信息。
									continue;
								}
								out3 << tmpmsg << endl;

							}
						}

					}
					exampleSleepMilliseconds(100);
				}
				//直到发送完
				if (!finished)
				{
					//Sleep(5000);
					dw << msgInstance;
					cout << "=== [Publisher] writing a message containing :" << endl;
					cout << "    userID  : " << msgInstance.userID() << endl;
					cout << "    Message : \"" << msgInstance.message() << "\"" << endl;
				}
				exampleSleepMilliseconds(10);
			} while (count < 1); // 三个文件全部处理完毕
			cout << "finish" << endl;
			out1.close();
			out2.close();
			out3.close();
		}
		catch (const dds::core::Exception& e)
		{
			cerr << "ERROR: Exception: " << e.what() << endl;
			result = 1;
		}
		return 0;
	}

	// display the result 
	int display()
	{
		string msg;
		ifstream out1("recv1.csv");
		cout << "The first condition: sort the students by ??? weight?" << endl;
		while (getline(out1, msg))
		{
			cout << msg << endl;
		}
		out1.close();
		ifstream out2("recv2.csv");
		cout << "The second condition: sort the students by ??? #####?" << endl;
		while (getline(out2, msg))
		{
			cout << msg << endl;
		}
		out2.close();
		ifstream out3("recv3.csv");
		cout << "The third condition, sort the student whitch stand the ???" << endl;
		while (getline(out3, msg))
		{
			cout << msg << endl;
		}
		out3.close();
		return 0;
	}

	int dealwith()
	{
		int result = 0;
		ifstream sou("source.csv", ios::in);
		ofstream res("result.csv", ios::out);
		/**************************************************************/
		/************在此函数中对csv文件进行处理，得到result.csv*******/
		/**************************************************************/
		vector<CSV>csv;
		Course course;

		int read_flag = 0;
		char buffer[10000];
		while (!sou.eof()) {
			sou.getline(buffer, 10000);

			string buf = buffer;
			if (buf == "")
				break;

			//前两行为课程信息
			if (read_flag == 0) {
				course.getCourseName(buf);
				read_flag++;
			}

			else if (read_flag == 1) {
				course.getCourseCredit(buf);
				read_flag++;
			}
			//后为学生信息
			else {
				CSV tmp(buf);
				csv.push_back(tmp);
			}

		}

		res << "name" << ',' << "ID" << ',' << "GPA" << endl;
		for (int i = 0; i < csv.size(); i++) {
			csv[i].getGPA(course);
			res << csv[i].name << ',' << csv[i].ID << ',' << csv[i].GPA << endl;
		}
		res.close();

		return result;
	}

}
}
}
}

//EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_HelloWorld_publisher, examples::dcps::CenterMachine::isocpp::publisher)
//EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_HelloWorld_subscriber, examples::dcps::CenterMachine::isocpp::subscriber)
