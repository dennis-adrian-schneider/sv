

#ifndef SV_APP_H
#define SV_APP_H
#define SDA_PIN 15
#define RST_PIN 2

#include "credentials.h"

int authLevel = 2;

String checkID(String id);

int convertAuthLevel(String authLevel);

#endif //SV_APP_H
