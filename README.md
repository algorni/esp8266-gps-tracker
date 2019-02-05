# esp8266-gps-tracker
A simple ESP8266 GPS Tracker feeding Azure IoT Hub

## License

MIT


## IoT Hub Data format

'''

05/02/2019 11:49:21> Device: [gps00000], Data:[{"Latitude":44.430326667000003, "Longitude":8.838939000000000, "SatInView":3, "Time":10492100, "hDoP":46.930000}]
05/02/2019 11:49:24> Device: [gps00000], Data:[{"Latitude":44.430290167000003, "Longitude":8.838958667000000, "SatInView":3, "Time":10492400, "hDoP":46.930000}]
05/02/2019 11:49:29> Device: [gps00000], Data:[{"Latitude":44.430244999999999, "Longitude":8.839005332999999, "SatInView":3, "Time":10492900, "hDoP":46.930000}]
05/02/2019 11:49:32> Device: [gps00000], Data:[{"Latitude":44.430188999999999, "Longitude":8.839048000000000, "SatInView":3, "Time":10493200, "hDoP":46.930000}]
05/02/2019 11:49:38> Device: [gps00000], Data:[{"Latitude":44.430033833000003, "Longitude":8.839197833000000, "SatInView":3, "Time":10493800, "hDoP":46.930000}]
05/02/2019 11:49:41> Device: [gps00000], Data:[{"Latitude":44.430001333000000, "Longitude":8.839238667000000, "SatInView":3, "Time":10494100, "hDoP":46.930000}]
05/02/2019 11:49:42> Device: [gps00000], Data:[{"Latitude":44.430008667000003, "Longitude":8.839233500000001, "SatInView":3, "Time":10494200, "hDoP":46.930000}]
05/02/2019 11:49:45> Device: [gps00000], Data:[{"Latitude":44.430051499999998, "Longitude":8.839195833000000, "SatInView":3, "Time":10494500, "hDoP":46.930000}]
05/02/2019 11:49:55> Device: [gps00000], Data:[{"Latitude":44.430271500000003, "Longitude":8.838995499999999, "SatInView":3, "Time":10495500, "hDoP":46.930000}]
05/02/2019 11:49:56> Device: [gps00000], Data:[{"Latitude":44.430298833000002, "Longitude":8.838970333000001, "SatInView":3, "Time":10495600, "hDoP":46.930000}]
05/02/2019 11:49:59> Device: [gps00000], Data:[{"Latitude":44.430368999999999, "Longitude":8.838924000000000, "SatInView":3, "Time":10495900, "hDoP":46.930000}]
05/02/2019 11:50:02> Device: [gps00000], Data:[{"Latitude":44.430425499999998, "Longitude":8.838891167000000, "SatInView":3, "Time":10500200, "hDoP":46.930000}]
05/02/2019 11:50:04> Device: [gps00000], Data:[{"Latitude":44.430455166999998, "Longitude":8.838872000000000, "SatInView":3, "Time":10500400, "hDoP":46.930000}]
05/02/2019 11:50:07> Device: [gps00000], Data:[{"Latitude":44.430512499999999, "Longitude":8.838848833000000, "SatInView":3, "Time":10500700, "hDoP":46.930000}]
05/02/2019 11:50:09> Device: [gps00000], Data:[{"Latitude":44.430537500000000, "Longitude":8.838835832999999, "SatInView":3, "Time":10500900, "hDoP":46.930000}]
05/02/2019 11:50:12> Device: [gps00000], Data:[{"Latitude":44.430581666999998, "Longitude":8.838823832999999, "SatInView":3, "Time":10501200, "hDoP":46.930000}]
05/02/2019 11:50:15> Device: [gps00000], Data:[{"Latitude":44.430622333000002, "Longitude":8.838809832999999, "SatInView":3, "Time":10501500, "hDoP":46.930000}]
05/02/2019 11:50:18> Device: [gps00000], Data:[{"Latitude":44.430638999999999, "Longitude":8.838800833000001, "SatInView":3, "Time":10501800, "hDoP":46.930000}]
05/02/2019 11:50:19> Device: [gps00000], Data:[{"Latitude":44.430645333000001, "Longitude":8.838806333000001, "SatInView":3, "Time":10501900, "hDoP":46.930000}]
05/02/2019 11:50:24> Device: [gps00000], Data:[{"Latitude":44.430675166999997, "Longitude":8.838830166999999, "SatInView":3, "Time":10502400, "hDoP":46.930000}]
05/02/2019 11:50:26> Device: [gps00000], Data:[{"Latitude":44.430684167000003, "Longitude":8.838839667000000, "SatInView":3, "Time":10502600, "hDoP":46.930000}]
05/02/2019 11:50:29> Device: [gps00000], Data:[{"Latitude":44.430686332999997, "Longitude":8.838854667000000, "SatInView":3, "Time":10502900, "hDoP":46.930000}]
05/02/2019 11:50:32> Device: [gps00000], Data:[{"Latitude":44.430703667000003, "Longitude":8.838875667000000, "SatInView":3, "Time":10503200, "hDoP":46.930000}]
05/02/2019 11:50:34> Device: [gps00000], Data:[{"Latitude":44.430810667000003, "Longitude":8.838832500000001, "SatInView":3, "Time":10503400, "hDoP":46.930000}]
05/02/2019 11:50:35> Device: [gps00000], Data:[{"Latitude":44.430864667000002, "Longitude":8.838817000000001, "SatInView":3, "Time":10503500, "hDoP":46.930000}]
05/02/2019 11:50:36> Device: [gps00000], Data:[{"Latitude":44.430908000000002, "Longitude":8.838805000000001, "SatInView":3, "Time":10503600, "hDoP":46.930000}]
05/02/2019 11:50:46> Device: [gps00000], Data:[{"Latitude":44.430828333000001, "Longitude":8.838897333000000, "SatInView":3, "Time":10504600, "hDoP":46.930000}]
05/02/2019 11:50:47> Device: [gps00000], Data:[{"Latitude":44.430812332999999, "Longitude":8.838902500000000, "SatInView":3, "Time":10504700, "hDoP":46.930000}]
05/02/2019 11:50:49> Device: [gps00000], Data:[{"Latitude":44.430795000000003, "Longitude":8.838919499999999, "SatInView":3, "Time":10504900, "hDoP":46.930000}]
05/02/2019 11:50:58> Device: [gps00000], Data:[{"Latitude":44.430733332999999, "Longitude":8.838973666999999, "SatInView":3, "Time":10505800, "hDoP":46.930000}]
05/02/2019 11:51:00> Device: [gps00000], Data:[{"Latitude":44.430713500000003, "Longitude":8.838981499999999, "SatInView":3, "Time":10510000, "hDoP":46.930000}]
05/02/2019 11:51:03> Device: [gps00000], Data:[{"Latitude":44.430659333000001, "Longitude":8.838994667000000, "SatInView":3, "Time":10510300, "hDoP":46.930000}]
05/02/2019 11:51:07> Device: [gps00000], Data:[{"Latitude":44.430569667000000, "Longitude":8.839018666999999, "SatInView":3, "Time":10510700, "hDoP":46.930000}]
05/02/2019 11:51:08> Device: [gps00000], Data:[{"Latitude":44.430547167000000, "Longitude":8.839024999999999, "SatInView":3, "Time":10510800, "hDoP":46.930000}]
05/02/2019 11:51:11> Device: [gps00000], Data:[{"Latitude":44.430587332999998, "Longitude":8.839051832999999, "SatInView":3, "Time":10511100, "hDoP":46.930000}]
05/02/2019 11:51:14> Device: [gps00000], Data:[{"Latitude":44.430741333000000, "Longitude":8.839087833000001, "SatInView":3, "Time":10511400, "hDoP":46.930000}]
05/02/2019 11:51:16> Device: [gps00000], Data:[{"Latitude":44.430721833000000, "Longitude":8.839089832999999, "SatInView":3, "Time":10511600, "hDoP":46.930000}]
05/02/2019 11:51:17> Device: [gps00000], Data:[{"Latitude":44.430720000000001, "Longitude":8.839093000000000, "SatInView":3, "Time":10511700, "hDoP":46.930000}]

'''


## Acknowledgement
This is heavily inspired by [Azure IoT C Client samples](https://github.com/Azure/azure-iot-sdk-c).
