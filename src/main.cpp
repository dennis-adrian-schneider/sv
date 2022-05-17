#include <Arduino.h>
#include "app.h"

//Variables
WiFiClient client;


void setup() {
    Serial.begin(115200);
//Connect with local Wi-Fi.
    connectWiFi(ssid_wifi, passwd);

//Connect with Database-Server.
    connectServer(dbServerIP, dbPort);

}

void loop() {
    while (checkWiFiConnection() && checkServerConnection()) {
        //TODO RFID implementation

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

//TODO Research Database send.
bool checkID(String id) {
    client.println();
}

//Check Wi-Fi Connection
bool checkWiFiConnection() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    Serial.println("WiFi timeout");
    return false;
}

//TODO Research client.stop(), client.connected() and reconnect mechanics.
bool checkServerConnection() {
    if (client.connected() == 1) {
        return true;
    }
    Serial.println("Database-Connection failed");
    client.stop();
    return false;
}