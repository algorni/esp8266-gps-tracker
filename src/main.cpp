#include <FS.h>  
#include <Arduino.h>
#include "configStorage.h"
#include "wifi.h"
#include "ntpCli.h"
#include "gpsManager.h"
#include "ioTHubManager.h"
//#include "ledManager.h"
#include "localApi.h"

void gpsPositionCallback(GPSPosition position);
void connectionTimeoutCallback();

SystemConfiguration systemConfig;

bool systemConfigIsValid = false;

unsigned long lastSentPositionTimeStamp = 0;

void setup() {
      
  Serial.begin(115200);

  //StartBlinking(0.5);

  Serial.println("System Started");

  InitializeSPIFFS();

  //this is just for test.. 
  //FormatStorage();

  systemConfigIsValid = CheckConfiguration();

  if ( systemConfigIsValid )
  {
    LoadConfig(&systemConfig);

    Serial.println("Configuration was loaded properly...");

    bool connected = ConnectWiFiAP(systemConfig);

    if ( connected )
    {
      InitUtcTime();

      InitAPIServer();

      InitializeIoTHubConnection(systemConfig);
    
      StartGPS(gpsPositionCallback);

      //StartBlinking(1);
    }
    else
    {
      systemConfigIsValid = false;

      Serial.println("Wi Fi network not reachable. Starting in AP Mode...");

      //start the WiFi AP mode and start the API Server just for waiting for the confituration
      StartAPMode();

      InitAPIServer_ConfigMode();
    }
  }
  else
  {
    Serial.println("Configuration was not properly set. Starting in AP Mode...");

    //start the WiFi AP mode and start the API Server just for waiting for the confituration
    StartAPMode();

    InitAPIServer_ConfigMode();
  }
}

void loop() {

  if(systemConfigIsValid)
  {
    // put your main code here, to run repeatedly:
    Serial.print(".");
    delay(250);
    PeriodicallyProcessGPSData();
    DoIoTHubClientWork();
  }
  else
  {
    Serial.print("-");
    delay(250);
  }

  HandleClientRequest();
}

void gpsPositionCallback(GPSPosition position)
{
  Serial.println("position callback");
  //StartBlinking(0.05);

  unsigned long m = millis();
  unsigned long delta = m - lastSentPositionTimeStamp;
  unsigned long repPeriod = systemConfig.ReportingPeriod  * 1000.0;

  if ( delta > repPeriod)
  {
    Serial.println("G");

    lastSentPositionTimeStamp = m;

    SendGPSData(position);
  }
  else
  {
    Serial.println("O");
  }
}


