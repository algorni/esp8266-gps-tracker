# esp8266-gps-tracker
A simple ESP8266 GPS Tracker feeding Azure IoT Hub

## License
MIT

## Connectivity & initial configuration
Device rely on WiFi to connect to the Azure IoT Hub
On first boot it start in AP Mode:
SSID: GPS Tracker
PSK: config1234
It expose a REST API to se the device configuration.
Once configured and restarted the device attempt to connect to the WiFi Network.
**BE CAREFUL** a fallback strategy still need to be implemented.

## REST API

   **GET -  "deviceIp"/config**

It returns the actual device configuration.  E.g.:

    {
      "AzureIoTHubConnectionString": "your azure iot hub connection string",
      "ReportingEnabled": 1,
      "ReportingPeriod": 120,
      "WiFiSSID": "your ssid",
      "WiFiKey": "your psk"
    }

   **POST - "deviceIp"/config**
It update the device configuration.  The payload in the body is the same of the GET  method.

   **GET -  "deviceIp"/reboot**
 It reboot the device
 
   **GET -  "deviceIp"/position**
 It will return the lastest GPS position of the device


## IoT Hub Device 2 Cloud data format

    05/02/2019 11:49:21> Device: [gps00000], Data:[{"Latitude":44.430326667000003, "Longitude":8.838939000000000, "SatInView":3, "Time":10492100, "hDoP":46.930000}] 
    05/02/2019 11:49:24> Device: [gps00000], Data:[{"Latitude":44.430290167000003, "Longitude":8.838958667000000, "SatInView":3, "Time":10492400, "hDoP":46.930000}] 
    05/02/2019 11:49:29> Device: [gps00000], Data:[{"Latitude":44.430244999999999, "Longitude":8.839005332999999, "SatInView":3, "Time":10492900, "hDoP":46.930000}]



## Acknowledgement
This is heavily inspired by [Azure IoT C Client samples](https://github.com/Azure/azure-iot-sdk-c).
