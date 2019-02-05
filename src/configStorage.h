#ifndef __configStorage
#define __configStorage

#include <WString.h>
#include <configuration.h>


bool InitializeSPIFFS();
void EndSPIFFS();

bool LoadConfig(SystemConfiguration* configuration);
void SaveConfig(SystemConfiguration configuration);
void FormatStorage();

bool LoadConfigString(String& jsonString);
void SaveConfig(String configString);
bool CheckConfiguration();

#endif