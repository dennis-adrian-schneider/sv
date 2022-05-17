

#ifndef SV_APP_H
#define SV_APP_H

#include "credentials.h"

//Method Declarations
bool connectWiFi(char ssid[], char pass[]);

bool connectServer(const IPAddress &serverIP, uint16_t port);

bool checkID(char id[]);

bool checkWiFiConnection();

bool checkServerConnection();

#endif //SV_APP_H
