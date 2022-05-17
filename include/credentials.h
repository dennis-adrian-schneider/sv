

#ifndef SV_CREDENTIALS_H
#define SV_CREDENTIALS_H

#include <ESP8266WiFi.h>

char ssid_wifi[] = "your_ssid";
char passwd[] = "your_password";
//Database Server Constants
const IPAddress dbServerIP(0, 0, 0, 0); //Replace with your destination IP.
const uint16_t dbPort = 0; //Replace with your destination port.
#endif //SV_CREDENTIALS_H
