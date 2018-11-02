#ifndef OPENSPLICE_ISOCXX_PSM
#define OPENSPLICE_ISOCXX_PSM
#endif
#ifndef CCPP_LISTENERDATA_H
#define CCPP_LISTENERDATA_H

#include "ListenerData.h"
#undef OS_API
#include "ListenerDataDcps.h"
#undef OS_API

#include <orb_abstraction.h>
#include "ListenerDataDcps_impl.h"

#endif /* CCPP_LISTENERDATA_H */

#ifdef LISTENERDATA_DCPS_TYPESUPPORT_DEFINED
#ifndef LISTENERDATA_DCPS_HPP_
#define LISTENERDATA_DCPS_HPP_
#include "dds/dds.hpp"

REGISTER_TOPIC_TRAITS(::ListenerData::Msg)

#endif
#endif
