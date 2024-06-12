struct SUPABASEQuery
{
  String key;
  String comparator;
  String value;
};

void hexdump(const void *mem, uint32_t len, uint8_t cols = 16)
{
  const uint8_t *src = (const uint8_t *)mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for (uint32_t i = 0; i < len; i++)
  {
    if (i % cols == 0)
    {
      Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}

String getEventTable(JsonDocument result)
{
  String table = result["payload"]["data"]["table"];
  return table;
}

String getEventType(JsonDocument result)
{
  String type = result["payload"]["data"]["type"];
  return type;
}

String generateRealtimeConfig(String table, String type, SUPABASEQuery query[], int numQuery)
{
  JsonDocument jsonRealtimeConfig;
  deserializeJson(jsonRealtimeConfig, R"({
          "event": "phx_join",
          "topic": "realtime:ESP",
          "payload": {
            "config": {
              "broadcast": {
                "self": false
              },
              "presence": {
                "key": ""
              },
              "postgres_changes": [
                {
                  "event": "event",
                  "schema": "public",
                  "table": "table"
                }
              ]
            }
          },
          "ref": "sentRef"
        })");

  jsonRealtimeConfig["payload"]["config"]["postgres_changes"][0]["table"] = table;
  jsonRealtimeConfig["payload"]["config"]["postgres_changes"][0]["event"] = type;

  if (numQuery != 0)
  {
    JsonDocument where;
    for (int i = 0; i < numQuery; i++)
    {
      where[query[i].key][query[i].comparator] = query[i].value;
    }

    jsonRealtimeConfig["payload"]["config"]["postgres_changes"][0]["where"] = where;
  }

  String config;
  serializeJson(jsonRealtimeConfig, config);

  return config;
}