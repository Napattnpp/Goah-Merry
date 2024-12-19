#include "Definition.h"
#include "OnBoardSign.h"
// WiFi and Webserver library.
#include <WiFi.h>
#include <HTTPClient.h>
#include "WiFiManager.h"
#include "HTTPManager.h"
#include "LocalWebServer.h"
// GPS library.
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include "GPSManager.h"
// SIM800L
#include "SIMManager.h"
// Other.
#include <Servo.h>
#include <NewPing.h>