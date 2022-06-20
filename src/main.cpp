#include <Arduino.h>
#include "app.h"
#include "../lib/rfid-master/MFRC522.h"
#include <SPI.h>



//Global Variables
WiFiClient client;
MFRC522 mfrc522(SDA_PIN,RST_PIN);

void setup() {
    Serial.begin(115200);
    SPI.begin();
    mfrc522.PCD_Init();
//Connect with local Wi-Fi.
    connectWiFi(ssid_wifi, passwd);

//Connect with Database-Server.
    connectServer(dbServerIP, dbPort);

}

void loop() {
    while (checkWiFiConnection() && checkServerConnection()) {
        //TODO test RFID implementation
        String id;
        for (byte i = 0; i < mfrc522.uid.size; ++i) {
            id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            id.concat(String(mfrc522.uid.uidByte[i], HEX));

        }
        client.println("GET /check-id/" + id + " HTTP/1.1");
    }

}

bool connectWiFi(char ssid[], char pass[]) {
    WiFi.begin(ssid, pass);
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected successfully to " + WiFi.SSID());
        return true;
    }
    return false;
}

bool connectServer(const IPAddress &serverIP, uint16_t port) {
    if (client.connect(serverIP, port)) {
        Serial.println(
                "Connected successfully to {}" + client.remoteIP().toString() + " at Port " + client.remotePort());
        return true;
    }
    return false;
}

//TODO Test Database send.
bool checkID(const String& id) {
    client.println("GET /check-id/" + id + " HTTP/1.1");
    return false;
}

//Check Wi-Fi Connection
bool checkWiFiConnection() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    Serial.println("WiFi timeout");
    return false;
}


bool checkServerConnection() {
    if (client.connected() == 1) {
        return true;
    }
    Serial.println("Database-Connection failed");
    client.stop();
    return false;
}