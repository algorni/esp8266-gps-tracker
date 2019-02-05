#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gpsManager.h"


static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

//this is the callback which will be executed and to which will be provided the GPSPosition struct with the update
//the struct is defined in the .h file
GPSPositionCallback __gpsCallBack;

GPSPosition __latestPosition;

void StartGPS(GPSPositionCallback callBack)
{
    Serial.println("Starting Receiving Serial data from GPS...");

    __gpsCallBack = callBack;

    ss.begin(GPSBaud);

    Serial.println("Serial port opened properly.");
}

void StopGPS()
{
    Serial.println("Stopping listening from SW Serial");

    ss.stopListening();

    __gpsCallBack = NULL;

    Serial.println("Stopping done");
}

void checkPositionUpdateFromGPS()
{
  if (gps.location.isValid())
  {
    if (gps.location.isUpdated())
    {
      int satInView = gps.satellites.value();
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
      float altitude = gps.altitude.meters();
      double hdop = gps.hdop.hdop();

/*
      Serial.print(F("\nLocation: ")); 
      Serial.print(latitude, 6);
      Serial.print(F(","));
      Serial.print(longitude, 6);
      Serial.print(F(" - sat in view: "));
      Serial.print(satInView, 6);
      Serial.print(F(" - hdop: "));
      Serial.print(hdop, 6);
      Serial.print(F(" - altitude: "));
      Serial.print(altitude, 6);
      Serial.println();
*/

      GPSPosition gpsPosition;
      
      gpsPosition.Lat = latitude;
      gpsPosition.Lon = longitude;
      gpsPosition.SatInView = satInView;
      gpsPosition.hDoP = hdop;
      gpsPosition.Altitude = altitude;

      if ( __gpsCallBack != NULL)
      {
        __latestPosition = gpsPosition;
        __gpsCallBack(gpsPosition);
      }
    }
  }
  else
  {
      //no GPS FIX
      Serial.print("X");
  }
}



GPSPosition GetLatestPosition()
{
    return __latestPosition;
}

void PeriodicallyProcessGPSData()
{
    //Serial.println("Reading GPS Serial data");

    //check for incoming GPS DATA
    while (ss.available() > 0)
    {
        char serialChar = ss.read();

        //Serial.print(serialChar);

        if (gps.encode(serialChar))
        {
            checkPositionUpdateFromGPS();
        }
    }    

    //Serial.println();

    //if system boots for more than 10 seconds and no data....
    if (millis() > 10000 && gps.charsProcessed() < 10)
    {
        Serial.println(F("No GPS detected: check wiring."));
    }
}
