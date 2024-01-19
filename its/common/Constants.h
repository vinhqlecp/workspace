#pragma once

#include <string>

const std::string LOC_TOPIC = "location_topic";
const std::string VEH_TOPIC = "vehicle_topic";

const std::string OBJ_TOPIC = "object_topic";

typedef enum InterfaceId {
	InterfaceId_Application = 0,
	InterfaceId_Management,
	InterfaceId_NetworkTransport,
	InterfaceId_Security,
	InterfaceId_Facility,

	InterfaceId_Max
} e_InterfaceId;
