#include <ESP8266WiFi.h>
#include <configStorage.h>

//details for the soft AP mode
const char *ap_ssid = "GPS Tracker";
const char *ap_password = "config1234";


void ConnectWiFiAP(SystemConfiguration configuration)
{
    //just hard code the connection to the Wi Fi right now...
    Serial.println("Connecting to WiFi...");

    WiFi.mode(WIFI_STA);

    // Connect to WiFi network
    WiFi.begin(configuration.WiFiSSID, configuration.WiFiKey);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println(".");
    Serial.print("Connected to ");
    Serial.println(configuration.WiFiSSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

//it start the AP Mode for the device
void StartAPMode()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid,ap_password);

    Serial.println();
    Serial.print("Server IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("Server MAC address: ");
    Serial.println(WiFi.softAPmacAddress());
}