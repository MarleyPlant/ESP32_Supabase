
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>

class SUPABASERealtime {
public:
  String hostname;
  String key;
  // Define an array to store SUPABASERealtimeTableEntry objects
  std::vector<SUPABASERealtimeTableEntry> entries;

  SUPABASERealtime() {
  }

  void setupConnection(String hostname, String key) {
    Serial.println("Setup Realtime Connection");
    this->hostname = hostname;
    this->key = key;
  }

  // Function to add a SUPABASERealtimeTableEntry object to the array
  void addEntry(String table, String event, SUPABASEQuery queries[], int numqueries, std::function<void(JsonDocument)> handler) {
    SUPABASERealtimeTableEntry entry = SUPABASERealtimeTableEntry(this->key, this->hostname);
    entry.setupHandler(handler);
    entry.setupListener(table, event, queries, numqueries);
    entries.push_back(entry);
  }

  void loop() {
    if(entries.size() == 0) {
      return;
    }
    for (int i = 0; i < entries.size(); i++) {
      // entries[i].webSocket.loop();
      // Serial.println();
      entries[i].loop();
    }
  }
};