#ifndef __gpsManager
#define __gpsManager

//Define the GPS Position structure
typedef struct GPSPosition
{
    int SatInView;
    double Lat; 
    double Lon;
    uint32 Time;
    float hDoP;
} GPSPosition;

//define a callback
typedef void (*GPSPositionCallback) (GPSPosition position);

void StartGPS(GPSPositionCallback callBack);
void PeriodicallyProcessGPSData();
void StopGPS();
GPSPosition GetLatestPosition();

#endif
