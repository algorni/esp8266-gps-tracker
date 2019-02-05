#ifndef __configuration
#define __configuration

#include <WString.h>

//Define the Configuration struct for this system
typedef struct SystemConfiguration
{
    char AzureIoTHubConnectionString[192];
    int ReportingEnabled; //0 or 1
    int ReportingPeriod;
    char WiFiSSID[32];
    char WiFiKey[32];
} SystemConfiguration;

#endif