#include "FS.h"
#include "configStorage.h"
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

bool isMounted = false;

void FormatStorage()
{
    //clean FS, for testing
    SPIFFS.format();
}

bool InitializeSPIFFS()
{
    if (!isMounted)
    {
      if (SPIFFS.begin()) 
      {
        Serial.println("mounted file system");

        return true;
      }
      else
      {
        Serial.println("failed to mount FS");

        return false;
      }
    }
    else
    {
      Serial.println("file system already mounted");
      return true;
    }
}

void EndSPIFFS()
{
  if (isMounted)
  {
    FSInfo fsInfo;
    SPIFFS.info(fsInfo);

    Serial.print("Total FFS size: ");
    Serial.print(fsInfo.totalBytes);
    Serial.print("\r\nUsed Space: ");
    Serial.print(fsInfo.usedBytes);
    Serial.print("\r\n");

    SPIFFS.end();
  }
  else
  {
    Serial.println("file system already unmounted");
  }
}


//TO BE REVIEWD
void SaveConfig(SystemConfiguration configuration)
{
      Serial.println("saving config");
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();

      //serialize into the JSON the actual parameters
      json["AzureIoTHubConnectionString"] = configuration.AzureIoTHubConnectionString;
      json["ReportingEnabled"] = configuration.ReportingEnabled;
      json["ReportingPeriod"] = configuration.ReportingPeriod;
      json["WiFiKey"] = configuration.WiFiKey;
      json["WiFiSSID"] = configuration.WiFiSSID;

      File configFile = SPIFFS.open("/config.json", "w");

      if (!configFile) {
        Serial.println("failed to open config file for writing");
      }

      json.printTo(Serial);
      json.printTo(configFile);
      configFile.flush();
      configFile.close();

      //end save
      Serial.println("saving done");
}

//OK
void SaveConfig(String configString)
{
    Serial.println("saving config");

    File configFile = SPIFFS.open("/config.json", "w");

    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    configFile.print(configString);
    configFile.flush();
    configFile.close();

    //end save
    Serial.println("saving done");
}

//it checks if the configuraiton json is there and is properly formatted as JSON
bool CheckConfiguration()
{
  bool ok = false;

  if (SPIFFS.exists("/config.json")) {
    //REDUCED CHECK Just if exist to reduce memory pressure
    //file exists, reading and loading
    //Serial.println("reading config file");
    //File configFile = SPIFFS.open("/config.json", "r");
    //if (configFile) {
    //  Serial.println("opened config file");
    //  size_t size = configFile.size();
      // Allocate a buffer to store contents of the file.
    //  std::unique_ptr<char[]> buf(new char[size]);
    //  configFile.readBytes(buf.get(), size);

    //  DynamicJsonBuffer jsonBuffer;
    //  JsonObject& json = jsonBuffer.parseObject(buf.get());
    //  json.printTo(Serial);

    //  if (json.success()) {
    //    Serial.println("\nparsed json");
        ok = true;
    //  }
    //}
  }
  
  return ok;
}

//TO BE CHECKED
bool LoadConfigString(String& jsonString)
{
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        jsonString = configFile.readString();
      }

      return true;
    }

    return false;
}

bool LoadConfig(SystemConfiguration* configuration)
{
    bool ret = false;

    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");

        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);

        if (json.success()) {
          Serial.println("\nParsed json -- Now creating the SystemConfiguration");

          configuration->ReportingEnabled = atoi(json["ReportingEnabled"]); 
          configuration->ReportingPeriod = atoi(json["ReportingPeriod"]); 

          String AzureIoTHubConnectionString = json["AzureIoTHubConnectionString"].as<String>();
          strncpy(configuration->AzureIoTHubConnectionString, AzureIoTHubConnectionString.c_str(), AzureIoTHubConnectionString.length() + 1);
         
          String WiFiSSID = json["WiFiSSID"].as<String>();
          strncpy(configuration->WiFiSSID, WiFiSSID.c_str(), WiFiSSID.length() + 1);

          String WiFiKey = json["WiFiKey"].as<String>();
          strncpy(configuration->WiFiKey, WiFiKey.c_str(), WiFiKey.length() + 1);
  
          ret = true;

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
        buf.release();
      }
    }

   return ret;
}

