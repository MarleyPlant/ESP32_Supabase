#include <WiFi.h>
#include <WiFiMulti.h>

#include <WebSocketsClient.h>

class SUPABASERealtimeTableEntry
{
public:
    WiFiMulti wifi;
    WebSocketsClient webSocket;
    std::function<void(JsonDocument)> handleEvent; // Changed to std::function
    String jsonRealtimeConfig;
    String key;
    String hostname;
    void setupHandler(std::function<void(JsonDocument)> handler)
    { // Changed to std::function
        handleEvent = handler;
    }

    SUPABASERealtimeTableEntry(String key, String hostname)
    {
          hostname.replace("https://", "");
        this->key = key;
        this->hostname = hostname;
    }

    void setupListener(String table, String event, SUPABASEQuery queries[], int numqueries)
    {


      this->jsonRealtimeConfig = generateRealtimeConfig(table, event, queries, numqueries);

        Serial.println(this->jsonRealtimeConfig);

        // Server address, port and URL
        // 1st param: Enter your project URL there
        // 2nd param: I have no idea, but it does not work with others than 443
        // Port number found here: https://github.com/esp8266/Arduino/issues/1442
        // 3rd param: url containing you anon key
        webSocket.beginSSL(
            this->hostname,
            443,
            "/realtime/v1/websocket?apikey=" + this->key + "&vsn=1.0.0");
        // If you want you can test with this one:
        // webSocket.beginSSL("echo.websocket.org",443);

        // event handler
        webSocket.onEvent(std::bind(&SUPABASERealtimeTableEntry::webSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    void processMessage(uint8_t *payload, size_t length, JsonDocument result)
    {
        String table = getEventTable(result);
        if (table != "null")
        {
            String data = result["payload"]["data"]["record"];
            deserializeJson(result, data);
            handleEvent(result);
        };
    }

    void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
    {
        JsonDocument result;

        switch (type)
        {
        // case WStype_DISCONNECTED:
        //     Serial.printf("[WSc] Disconnected!\n");
        //     break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n", payload);
            // // send message to server when Connected
            // Serial.println(this->jsonRealtimeConfig);
            // webSocket.sendTXT(jsonRealtimeConfig);
            // Some sort of error with storing the jsonRealtimeConfig
            // When executing the above line, the ESP32 crashes
            // Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.
            Serial.println("Sent config");
            break;
        case WStype_TEXT:
            deserializeJson(result, payload);
            processMessage(payload, length, result);
            // send message to server
            // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);
            // hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
        case WStype_ERROR:
            Serial.printf("[WSc] Error: %s\n", payload);
            break;
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
        }
    }

    void loop()
    {
        webSocket.loop();
    }
};

// void SUPABASERealtimeTableEntry::setupHandler(void (*handler)(JsonDocument))
// {
//     handleEvent = handler;
// }