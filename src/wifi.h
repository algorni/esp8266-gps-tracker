#ifndef __wifi
#define __wifi

#include <ESP8266WiFi.h>
#include <configStorage.h>

void ConnectWiFiAP(SystemConfiguration configuration);
void StartAPMode();

#endif