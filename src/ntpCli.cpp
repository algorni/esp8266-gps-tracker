#include <time.h>
#include <Arduino.h>

// Times before 2010 (1970 + 40 years) are invalid
#define MIN_EPOCH 40 * 365 * 24 * 3600

void InitUtcTime() {  
   time_t epochTime;

   Serial.println("Fetching NTP epoch time.");
   configTime(0, 0, "pool.ntp.org", "time.nist.gov");

   delay(3000);

   while (true) {
       epochTime = time(NULL);

       if (epochTime < MIN_EPOCH) {
           Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
           delay(2000);
       } else {
           Serial.print("Fetched NTP epoch time is: ");
           Serial.println(epochTime);
           break;
       }
   }
}

