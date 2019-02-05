#include <ESP8266WiFi.h>
#include <configStorage.h>
#include <wifi.h>

//details for the soft AP mode
const char *ap_ssid = "GPS Tracker";
const char *ap_password = "config1234";


bool ConnectWiFiAP(SystemConfiguration configuration)
{
    //just hard code the connection to the Wi Fi right now...
    Serial.println("Connecting to WiFi...");

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(false);
    WiFi.setAutoReconnect(true);
    // Connect to WiFi network
    WiFi.begin(configuration.WiFiSSID, configuration.WiFiKey);

    uint64_t start = millis();

    // Wait for connection
    while ((WiFi.status() != WL_CONNECTED)) {
        
        delay(500);
        Serial.print(".");

        //gives a timeout of 30 seconds before timeouting...
        if (millis() - start > 30000) 
        {
             WiFi.disconnect(false); 
             return false; 
        }
    }

    Serial.println(".");
    Serial.print("Connected to ");
    Serial.println(configuration.WiFiSSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    return true;
}

//it start the AP Mode for the device
void StartAPMode()
{
    WiFi.persistent(false);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid,ap_password);
    
    Serial.println();
    Serial.print("Server IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("Server MAC address: ");
    Serial.println(WiFi.softAPmacAddress());
}

