#include <Arduino.h>
#include "app.h"
#include "../lib/rfid-master/MFRC522.h"
#include <SPI.h>
#include <ESP8266HTTPClient.h>

//Global Variables
WiFiClient client;
MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
    Serial.begin(115200);
    SPI.begin();
    WiFi.begin(ssid_wifi, passwd);
    mfrc522.PCD_Init();

}

void loop() {
    ESP.wdtFeed();
    if (WiFi.status() == WL_CONNECTED) {
        ESP.wdtFeed();

        // Look for new cards
        if (!mfrc522.PICC_IsNewCardPresent()) {
            return;
        }
        // Select one of the cards
        if (!mfrc522.PICC_ReadCardSerial()) {
            return;
        }

        String content = "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        if (!content.isEmpty()) {
            int cardAuth = convertAuthLevel(checkID(content));

            if (cardAuth >= authLevel) {
                Serial.println("AuthSuccessful");
            } else {
                Serial.println("Invalid permissions");
            }
            delay(2500);
        }
    }
}

int convertAuthLevel(String authLevel) {
    if (authLevel.equals("HIGH")) {
        return 3;
    } else if (authLevel.equals("MEDIUM")) {
        return 2;
    } else if (authLevel.equals("LOW")) {
        return 1;
    } else {
        return 0;
    }
}

String checkID(String id) {
    HTTPClient httpClient;
    id.trim();
    String msg = "http://" + authServerIP + ":" + authServerPort + "/check-id/";
    msg.concat(id);
    Serial.println(msg);
    httpClient.begin(client, msg);
    int respC = httpClient.GET();
    if (respC > 0) {
        Serial.print("Response code: ");
        Serial.println(respC);
        String respMsg = httpClient.getString();
        Serial.println(respMsg);
        httpClient.end();
        return respMsg;
    } else {
        Serial.print("Error code: ");
        Serial.println(respC);
        httpClient.end();
        return "HTTP ERROR";
    }

}


