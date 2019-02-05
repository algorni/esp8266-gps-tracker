//Microsoft Azure IoT Hub libraries
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
//#include <AzureIoTUtility.h>

#include "gpsManager.h"
//#include "ledManager.h"
#include "configStorage.h"

#include "ioTHubManager.h"

// Define the Model for the GPS Tracking
BEGIN_NAMESPACE(GPSTrackerSystem);

DECLARE_MODEL(GPSTracker,
WITH_DATA(int, SatInView),
WITH_DATA(double, Latitude),
WITH_DATA(double, Longitude),
WITH_DATA(float, hDoP),
WITH_DATA(float, Altitude),
WITH_ACTION(TurnTrackingOn),
WITH_ACTION(TurnTrackingOff),
WITH_ACTION(SetTrackingFrequency, int, IntervalSeconds)
);

END_NAMESPACE(GPSTrackerSystem);

//the iot client (will be created in the setup method)
IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;

unsigned int messageTrackingId = 0;

EXECUTE_COMMAND_RESULT TurnTrackingOn(GPSTracker* device)
{
    (void)device;
    (void)printf("Turning GPS Tracking on.\r\n");



    return EXECUTE_COMMAND_SUCCESS;
}

EXECUTE_COMMAND_RESULT TurnTrackingOff(GPSTracker* device)
{
    (void)device;
    (void)printf("Turning GPS Tracking off.\r\n");



    return EXECUTE_COMMAND_SUCCESS;
}

EXECUTE_COMMAND_RESULT SetTrackingFrequency(GPSTracker* device, int IntervalSeconds)
{
    (void)device;
    (void)printf("Setting GPS Position reporting frequency to %d seconds.\r\n", IntervalSeconds);
    


    return EXECUTE_COMMAND_SUCCESS;
}





static IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubMessage_Callback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char* buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
    {
        printf("unable to IoTHubMessage_GetByteArray\r\n");
        result = IOTHUBMESSAGE_ABANDONED;
    }
    else
    {
        /*buffer is not zero terminated*/
        char* temp = (char*)malloc(size + 1);
        if (temp == NULL)
        {
            printf("failed to malloc\r\n");
            result = IOTHUBMESSAGE_ABANDONED;
        }
        else
        {
            (void)memcpy(temp, buffer, size);
            temp[size] = '\0';
            EXECUTE_COMMAND_RESULT executeCommandResult = EXECUTE_COMMAND(userContextCallback, temp);
            result =
                (executeCommandResult == EXECUTE_COMMAND_ERROR) ? IOTHUBMESSAGE_ABANDONED :
                (executeCommandResult == EXECUTE_COMMAND_SUCCESS) ? IOTHUBMESSAGE_ACCEPTED :
                IOTHUBMESSAGE_REJECTED;
            free(temp);
        }
    }
    return result;
}


void sendMessageCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    unsigned int messageTrackingId = (unsigned int)(uintptr_t)userContextCallback;

    (void)printf("Message Id: %u Received.\r\n", messageTrackingId);

    (void)printf("Result Call Back Called! Result is: %s \r\n", ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));

    //StartBlinking(1);
}


//Initialize the IoT Hub Connection
void InitializeIoTHubConnection(SystemConfiguration systemConfig)
{
    if (serializer_init(NULL) != SERIALIZER_OK)
    {
        (void)printf("Failed on serializer_init\r\n");
    }
    else
    {
        (void)printf("Initializing IoT Hub Connection...\r\n");

        const char* ioTHubConnectionString = systemConfig.AzureIoTHubConnectionString;

        iotHubClientHandle = 
                IoTHubClient_LL_CreateFromConnectionString(ioTHubConnectionString, MQTT_Protocol);
        
        if (iotHubClientHandle == NULL)
        {
            (void)printf("Failed on IoTHubClient_LL_Create\r\n");
        }
        else
        {
            (void)printf("IOTHUB_CLIENT_LL_HANDLE created\r\n");

            IOTHUB_CLIENT_RESULT messageCallbackResult = IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, IoTHubMessage_Callback, NULL);

            if (messageCallbackResult != IOTHUB_CLIENT_OK)
            {
                printf("unable to IoTHubClient_SetMessageCallback\r\n");
                if ( messageCallbackResult == IOTHUB_CLIENT_INVALID_ARG) printf("IOTHUB_CLIENT_INVALID_ARG");
                if ( messageCallbackResult == IOTHUB_CLIENT_ERROR) printf("IOTHUB_CLIENT_ERROR");
                if ( messageCallbackResult == IOTHUB_CLIENT_INVALID_SIZE) printf("IOTHUB_CLIENT_INVALID_SIZE");
                if ( messageCallbackResult == IOTHUB_CLIENT_INDEFINITE_TIME) printf("IOTHUB_CLIENT_INDEFINITE_TIME");
            }
            else
            {
                printf("IoTHubClient_LL_SetMessageCallback configured\r\n");

            }

        }
    }
}


void SendGPSData(GPSPosition gpsPositionUpdate)
{
    if ( iotHubClientHandle == NULL)
    {
        (void)printf("iotHubClientHandle is NULL in SendGPSData\r\n");
    }

    GPSTracker* positionUpdate = CREATE_MODEL_INSTANCE(GPSTrackerSystem, GPSTracker);
    positionUpdate->SatInView = gpsPositionUpdate.SatInView;
    positionUpdate->Latitude = gpsPositionUpdate.Lat;
    positionUpdate->Longitude = gpsPositionUpdate.Lon;
    positionUpdate->hDoP = gpsPositionUpdate.hDoP;
    positionUpdate->Altitude = gpsPositionUpdate.Altitude;

    if (positionUpdate == NULL)
    {
        (void)printf("Failed send GPS Data data is NULL\r\n");
    }
    else
    {
        unsigned char* destination;

        size_t destinationSize;

        if (SERIALIZE(&destination, &destinationSize, 
                positionUpdate->Latitude, 
                positionUpdate->Longitude,
                positionUpdate->SatInView,
                positionUpdate->Altitude,
                positionUpdate->hDoP) != CODEFIRST_OK)
        {
            (void)printf("Failed to serialize\r\n");
        }
        else
        {
            //(void)printf("Destination Size: %d", destinationSize);
            //(void)printf((char*)destination);

            IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(destination, destinationSize);

            if (messageHandle == NULL)
            {
                printf("unable to create a new IoTHubMessage\r\n");
            }
            else
            {
                //MAP_HANDLE propMap = IoTHubMessage_Properties(messageHandle);
                //char str[2];
                //sprintf(str, "%d", positionUpdate->SatInView);
                //if (Map_AddOrUpdate(propMap, "SatInView", str)  != MAP_OK)
                //{
                //    (void)printf("ERROR: Map_AddOrUpdate Failed!\r\n");
                //}

                if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendMessageCallback, (void*)(uintptr_t)messageTrackingId) != IOTHUB_CLIENT_OK)
                {
                    printf("failed to hand over the message to IoTHubClient");
                }
                else
                {
                    printf("IoTHubClient accepted the message for delivery\r\n");
                }
                
                IoTHubMessage_Destroy(messageHandle);
            }

            messageTrackingId++;
            
            free(destination);
        }
        
        IoTHubClient_LL_DoWork(iotHubClientHandle);
        
        DESTROY_MODEL_INSTANCE(positionUpdate);
    }
}

void DoIoTHubClientWork()
{
    //IoTHubClient_LL_DoWork(iotHubClientHandle);

    //IOTHUB_CLIENT_STATUS Status;

    //while ((IoTHubClient_LL_GetSendStatus(iotHubClientHandle, &Status) == IOTHUB_CLIENT_OK) && (Status == IOTHUB_CLIENT_SEND_STATUS_BUSY))
    //{
        IoTHubClient_LL_DoWork(iotHubClientHandle);
        ThreadAPI_Sleep(100);
    //}
}
