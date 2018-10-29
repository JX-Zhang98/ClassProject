#ifndef OPENSPLICE_ISOCXX_PSM
#define OPENSPLICE_ISOCXX_PSM
#endif
#ifndef CCPP_CONTENTFILTEREDTOPICDATA_H
#define CCPP_CONTENTFILTEREDTOPICDATA_H

#include "ContentFilteredTopicData.h"
#undef OS_API
#include "ContentFilteredTopicDataDcps.h"
#undef OS_API

#include <orb_abstraction.h>
#include "ContentFilteredTopicDataDcps_impl.h"

#endif /* CCPP_CONTENTFILTEREDTOPICDATA_H */

#ifdef CONTENTFILTEREDTOPICDATA_DCPS_TYPESUPPORT_DEFINED
#ifndef CONTENTFILTEREDTOPICDATA_DCPS_HPP_
#define CONTENTFILTEREDTOPICDATA_DCPS_HPP_
#include "dds/dds.hpp"

REGISTER_TOPIC_TRAITS(::StockMarket::Stock)

#endif
#endif
