#include <Arduino.h>
#include "app.h"
#include "../lib/rfid-master/MFRC522.h"
#include <SPI.h>
#include <ESP8266HTTPClient.h>

//Global Variables
WiFiClient client;
MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
    delay(15000);
    Serial.begin(115200);
    Serial.println("Serial.Begin");
    SPI.begin();
    Serial.println("SPI.Begin");
    WiFi.begin(ssid_wifi, passwd);
    Serial.println("Connected to Wifi");
    ESP.wdtFeed();
    mfrc522.PCD_Init();
    ESP.wdtFeed();
    Serial.println("MFRC.Init");

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
        //Show UID on serial monitor
        String content = "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        if (!content.isEmpty()) {
            if (checkID(content).equals(authLevel)) {
                Serial.println("AuthSuccessful");
            }
        }
    }
}

//TODO Test Database send.
String checkID(String id) {
    ESP.wdtFeed();
    HTTPClient httpClient;
    String msg = "http://202.61.246.240:8080/check-id/";
    msg.concat(id);
    Serial.println(msg);
    httpClient.begin(client, msg);
    int respC = httpClient.GET();
    if (respC > 0) {
        Serial.print("Response code: ");
        Serial.println(respC);
        Serial.println(httpClient.getString());
        httpClient.end();
        return httpClient.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(respC);
        httpClient.end();
        return "HTTP ERROR";
    }

}


