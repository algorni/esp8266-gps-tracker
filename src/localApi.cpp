#include <ESP8266WebServer.h>
#include <configStorage.h>
#include <gpsManager.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

ESP8266WebServer server(80);

void handle_root() 
{
  server.send(200, "text/plain", 
  "Hello from the GPS Tracker\nGet Actual Position with /position or get-update configuration /config");
  delay(100);
}

void handle_getConfig()
{
    InitializeSPIFFS();
    String configString;
    LoadConfigString(configString);
    EndSPIFFS();

    server.send(200, "application/json", configString);
}

void handle_rebootRequest()
{
    server.send(200, "text/plain", "Rebooting in 2 seconds...");
    delay(2000);
    ESP.restart();
}

void handle_updateConfig()
{
      if (server.hasArg("plain")== false){ //Check if body received
            server.send(200, "text/plain", "Body not received");
            return;
      }

      String body = server.arg("plain");
 
      //now save the new configuration uploaded by the API as it it...  no super check here...
      InitializeSPIFFS();
      SaveConfig(body);
      EndSPIFFS();

      String message = "Config Saved:\n";
             message += body;
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}

void hangle_getPosition() { //Handler

    String message;
   
    GPSPosition latestPosition = GetLatestPosition();

    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    //serialize into the JSON the actual position
    json["Lat"] = latestPosition.Lat;
    json["Lon"] = latestPosition.Lon;
    json["SatInView"] = latestPosition.SatInView;
    json["hDoP"] = latestPosition.hDoP;
    json["Time"] = latestPosition.Time;

    json.printTo(message);

    server.send(200, "application/json", message);       //Response to the HTTP request
}



void InitAPIServer()
{
    server.on("/", handle_root);
    server.onNotFound(handle_root);

    server.on("/position",HTTP_GET, hangle_getPosition);
    server.on("/config",HTTP_GET, handle_getConfig);
    server.on("/config",HTTP_POST, handle_updateConfig);
    server.on("/reboot",HTTP_GET, handle_rebootRequest);

    server.begin();
    Serial.println("HTTP server started");
}

void InitAPIServer_ConfigMode()
{
    server.on("/", handle_root);
    server.onNotFound(handle_root);

    server.on("/config",HTTP_GET, handle_getConfig);
    server.on("/config",HTTP_POST, handle_updateConfig);
    server.on("/reboot",HTTP_GET, handle_rebootRequest);

    server.begin();
    Serial.println("HTTP server started config mode");
}

void HandleClientRequest()
{
    server.handleClient(); 
}
