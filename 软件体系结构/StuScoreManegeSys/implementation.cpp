
/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to  PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "implementation.hpp"
#include "common/example_utilities.h"

#include <iostream>
#include <fstream>
#include "HelloWorldData_DCPS.hpp"
using namespace std;
namespace examples {
#ifdef GENERATING_EXAMPLE_DOXYGEN
	GENERATING_EXAMPLE_DOXYGEN /* workaround doxygen bug */
#endif
		namespace dcps {
		namespace HelloWorld {

			/**
			 * @addtogroup examplesdcpsHelloWorldisocpp The ISO C++ DCPS API HelloWorld example
			 *
			 * This is a simple publisher and subscriber example. One sample is
			 * published, the sample is then read.
			 * Some non-default QoS are used to guarantee delivery and to allow
			 * the publisher to be optionally run before the subscriber.
			 * @ingroup examplesdcpsisocpp
			 */
			 /** @{*/
			 /** @dir */
			 /** @file */

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

						//exampleSleepMilliseconds(5000);
						//getchar();

						/** A sample is created and then written. */
						HelloWorldData::Msg msgInstance(1, "I have received your massage!");
						dw << msgInstance;

						cout << "=== [Publisher] writing a message containing :" << endl;
						cout << "    userID  : " << msgInstance.userID() << endl;
						cout << "    Message : \"" << msgInstance.message() << "\"" << endl;

						/* A short sleep ensures time is allowed for the sample to be written to the network.
						If the example is running in *Single Process Mode* exiting immediately might
						otherwise shutdown the domain services before this could occur */
						exampleSleepMilliseconds(5000);
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
				 * @return 0 if a sample is successfully read, 1 otherwise.
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

						/** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
						dds::sub::DataReader<HelloWorldData::Msg> dr(sub, topic, drqos);

						/** An attempt to take samples is made repeatedly until it succeeds,
						 * or sixty seconds have elapsed. */
						bool sampleReceived = false;
						int count = 0;
						do
						{
							dds::sub::LoanedSamples<HelloWorldData::Msg> samples = dr.take();
							for (dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator sample = samples.begin();
								sample < samples.end();
								++sample)
							{
								if (sample->info().valid())
								{
									cout << "=== [Subscriber] message received :" << endl;
									cout << "    userID  : " << sample->data().userID() << endl;
									cout << "    Message : \"" << sample->data().message() << "\"" << endl;
									if (!sample->data().message().compare("File send finished!Please go on to deal with them!"))
										sampleReceived = true;
								}
								/*********************************************************************/
								/********************** 这里进行文件处理******************************/
								/*********************************************************************/

							}
							//exampleSleepMilliseconds(100);
							++count;
						} while (!sampleReceived);

						if (!sampleReceived)
						{
							cerr << "ERROR: Waited for 60 seconds but no sample received" << endl;
							result = 1;
						}
					}
					catch (const dds::core::Exception& e)
					{
						cerr << "ERROR: Exception: " << e.what() << endl;
						result = 1;
					}
					return result;
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
						Sleep(3000);

						/**************************************************************************************/
						//待处理
						char filePath[100] = { 0 };
						puts("Please input the path of the file you want to send.");
						gets_s(filePath, 99);

						ifstream f;
						f.open(filePath);

						//udp 单次最大传输1472字节，所以按行读取。
						//这里进行读文件操作，获得msg的字符串string
						//创建一个test示例
						//HelloWorldData::Msg msgInstance(1, "test, 这是一个文件de content,,,，,。.！!￥");
						//待处理，假装完成了将文件内容转化为msg格式的操作
						/**************************************************************************************/


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

						bool finished = false;
						int count = 0;
						string tmpmsg;
						do
						{
							/**************************************************************************************/
						//待处理
						//这里进行读文件操作，获得msg的字符串string

							if (!getline(f, tmpmsg))
							{
								//给接收方发送结束信号，约定自定义生成
								HelloWorldData::Msg msgInstance(1, "File send finished!Please go on to deal with them!");
								dw << msgInstance;
								f.close();
								finished = 1;
							}
							HelloWorldData::Msg msgInstance(1, tmpmsg);

							if (finished)
							{
								dds::sub::LoanedSamples<HelloWorldData::Msg> samples = dr.take();
								for (dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator sample = samples.begin();
									sample < samples.end();
									++sample)
								{
									if (sample->info().valid())
									{
										cout << "=== [Subscriber] message received :" << endl;
										cout << "    userID  : " << sample->data().userID() << endl;
										cout << "    Message : \"" << sample->data().message() << "\"" << endl;

									}
									/****************************************************************************/
									/******************** 这里进行接收文件处理 **********************************/
									/****************************************************************************/
								}
								exampleSleepMilliseconds(100);
								++count;
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
						} while (count < 6000); // 等十分钟

					}
					catch (const dds::core::Exception& e)
					{
						cerr << "ERROR: Exception: " << e.what() << endl;
						result = 1;
					}
				}

			}
		}
	}
}

//EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_HelloWorld_publisher, examples::dcps::CenterMachine::isocpp::publisher)
//EXAMPLE_ENTRYPOINT(DCPS_ISOCPP_HelloWorld_subscriber, examples::dcps::CenterMachine::isocpp::subscriber)
