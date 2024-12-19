#include "SystemFile.h"

// Servoback {65, 100, 135}
Servo servoFront;
Servo servoBack;

// Ultrasonic
float distance = 0.0;
float obstacleRange = 20.0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Init WiFi and HTTP manager
WiFiManager wifiManager("jane_2.4GHz", "0868638303");
HTTPManager httpManager("https://mywebservermld.000webhostapp.com/index.php");
// Init Local web server
LocalWebServer localWebServer(80);
// Init GPS manager
GPSManager gpsManager;
// Init SIM800L manager
SIMManager simManager("internet", "true", "true");  // "internet", "true", "true" or "www.dtac.co.th", "", ""

String dataToSendToServer = "";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SERVO_FRONT_PIN, OUTPUT);
  pinMode(SERVO_BACK_PIN, OUTPUT);
  pinMode(SKIP_PIN, INPUT_PULLUP);

  servoFront.attach(SERVO_FRONT_PIN);
  servoBack.attach(SERVO_BACK_PIN);

  Serial.begin(115200);

  simManager.init();
  // gpsManager.init();
  // wifiManager.connect();
  // wifiManager.info();
  // localWebServer.init();

  servoFront.write(90);
  servoBack.write(90);
  digitalWrite(LED_BUILTIN, 0);
  delay(3000);

  // Ready to start main program.
  onBoardSign.ready();

  dataToSendToServer = httpManager.convertToHttpHeader(gpsManager.latitude, gpsManager.longitude, "GoahMerry", "insert", "NEFxBGk6cDyJ3STI");
  // httpManager.sendData(dataToSendToServer);
}

void loop() {
  // checkObs180D();
  // gpsManager.getCoordinate();
  // gpsManager.rawCommand();
  // simManager.rawCommand();

  simManager.sendDataToServer("http://mywebservermld.000webhostapp.com/index.php", dataToSendToServer);
}
