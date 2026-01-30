#include "api_client.h"
#include "config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

bool api_post_weight(const String &uid, float weight) {
    HTTPClient http;

    String url = String(API_BASE_URL) + "/api/spools/" + uid + "/weight";
    Serial.print("POST ");
    Serial.println(url);

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    JsonDocument doc;
    doc["weight"] = weight;
    String body;
    serializeJson(doc, body);

    int httpCode = http.POST(body);
    String response = http.getString();
    http.end();

    Serial.print("HTTP ");
    Serial.print(httpCode);
    Serial.print(" — ");
    Serial.println(response);

    if (httpCode == 200) {
        return true;
    }

    Serial.print("API error: ");
    Serial.println(response);
    return false;
}
