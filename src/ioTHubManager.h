#ifndef __iotHubManager
#define __iotHubManager

//Microsoft Azure IoT Hub libraries
#include "AzureIoTHub.h"
//#include <AzureIoTProtocol_MQTT.h>
#include <WString.h>
#include "gpsManager.h"
#include <configuration.h>

void InitializeIoTHubConnection(SystemConfiguration systemConfig);
void SendGPSData(GPSPosition gpsPositionUpdate);
void DoIoTHubClientWork();

#endif