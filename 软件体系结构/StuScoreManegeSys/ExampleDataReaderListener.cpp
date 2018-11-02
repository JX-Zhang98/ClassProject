#include "ExampleDataReaderListener.hpp"
#include <fstream>
namespace examples { namespace dcps { namespace Listener { namespace isocpp {

ExampleDataReaderListener::ExampleDataReaderListener() : data_received_(false),
                                                         deadline_expired_(false) {}

ExampleDataReaderListener::~ExampleDataReaderListener() {}

void ExampleDataReaderListener::on_requested_deadline_missed(
    dds::sub::DataReader<ListenerData::Msg>& the_reader,
    const dds::core::status::RequestedDeadlineMissedStatus& status)
{
    std::cout << "\n=== [ExampleDataReaderListener::on_requested_deadline_missed] : triggered" << std::endl;
    std::cout << "\n=== [ExampleDataReaderListener::on_requested_deadline_missed] : stopping" << std::endl;
    deadline_expired_ = true;
}


void ExampleDataReaderListener::on_data_available(dds::sub::DataReader<ListenerData::Msg>& dr)
{
    dds::sub::LoanedSamples<ListenerData::Msg> samples = dr.take();
    if((*samples.begin()).info().valid())
    {
		ofstream sou("source.csv", ios::app);//×·¼ÓÐ´Èë
        std::cout << "\n=== [ExampleDataReaderListener::on_data_available] - samples.length() : " << samples.length() << std::endl;
        for (dds::sub::LoanedSamples<ListenerData::Msg>::const_iterator sample = samples.begin();
             sample < samples.end();
             ++sample)
        {
			if (!sample->data().message().compare("File send finished!Please go on to deal with them!"))
				/*sourceRecvFini = true;*/
				break;
			else
			{
				sou << sample->data().message() << endl;
				std::cout << "=== [Subscriber] message received :" << std::endl;
				std::cout << "    userID  : " << sample->data().userID() << std::endl;
				std::cout << "    Message : \"" << sample->data().message() << "\"" << std::endl;
			}
			data_received_ = true;
        }
		sou.close();
    }
}

}}}}
