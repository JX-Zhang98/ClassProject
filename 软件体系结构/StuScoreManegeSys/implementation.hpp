
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

#include "common/example_export.h"
#include <iostream>
namespace examples {
namespace dcps {
namespace HelloWorld {
namespace isocpp  {
    OS_EXAMPLE_IMPL_EXPORT int publisher(std::string topicc, std::string namee);
    OS_EXAMPLE_IMPL_EXPORT int subscriber(std::string topicc, std::string namee);
	OS_EXAMPLE_IMPL_EXPORT int broadcastCenter();
	OS_EXAMPLE_IMPL_EXPORT int display();
	OS_EXAMPLE_IMPL_EXPORT int dealwith();
}
}
}
}
