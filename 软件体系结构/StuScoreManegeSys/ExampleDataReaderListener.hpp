#ifndef __EXAMPLEDATAREADERLISTENER_H__
#define __EXAMPLEDATAREADERLISTENER_H__

#include <iostream>
#include "ListenerData_DCPS.hpp"

namespace examples { namespace dcps { namespace Listener { namespace isocpp {

/**
 * @addtogroup examplesdcpsListenerisocpp
 */
/** @{*/
/** @file */

class ExampleDataReaderListener :   public virtual dds::sub::DataReaderListener<ListenerData::Msg>, public virtual dds::sub::NoOpDataReaderListener<ListenerData::Msg>
{
public:
    ExampleDataReaderListener();
    virtual ~ExampleDataReaderListener();

    virtual void on_requested_deadline_missed(
        dds::sub::DataReader<ListenerData::Msg>& the_reader,
        const dds::core::status::RequestedDeadlineMissedStatus& status);

    virtual void on_data_available(dds::sub::DataReader<ListenerData::Msg>& the_reader);

    /** Is set to true when the listener has been notified of
     * ExampleDataReaderListener::on_data_available and has read some data */
    bool data_received_;

    /** Is set to true when the listener has been notified of
     * ExampleDataReaderListener::on_requested_deadline_missed  */
    bool deadline_expired_;
};

/** @}*/

}}}}

#endif
