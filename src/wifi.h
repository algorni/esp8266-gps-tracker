#ifndef __wifi
#define __wifi

#include <ESP8266WiFi.h>
#include <configStorage.h>

bool ConnectWiFiAP(SystemConfiguration configuration);
void StartAPMode();

#endif