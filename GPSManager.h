HardwareSerial GPSSerial(1);

class GPSManager {
  private:
    bool skipPinState = 0;

  public:
    double latitude = 0.0;
    double longitude = 0.0;

    TinyGPSPlus gps;
    
    void init();
    void rawCommand();
    void getCoordinate();
};

void GPSManager::init() {
  GPSSerial.begin(9600, SERIAL_8N1, ON_BOARD_RX_PIN1, ON_BOARD_TX_PIN1);
  Serial.println("GPS-Serial begin at 9600 baud");
  Serial.print("Waiting for satellites");
  while (gps.satellites.value() < 3) {
    Serial.print(".");

    if (!digitalRead(SKIP_PIN)) {
      skipPinState = 1;
      break;
    }

    delay(300);
  }
  Serial.println("");

  if (skipPinState) {
    onBoardSign.skipTask();
    Serial.println("[Task was skipped]");
    delay(1000);
  }

  Serial.print("Number of satellites: ");
  Serial.println(gps.satellites.value());
}

void GPSManager::rawCommand() {
  if (Serial.available()) {
    GPSSerial.write(Serial.read());
  }
  if (GPSSerial.available()) {
    Serial.write(GPSSerial.read());
  }
}

void GPSManager::getCoordinate() {
  if (GPSSerial.available()) {
    gps.encode(GPSSerial.read());

    latitude = gps.location.lat(), 6;
    longitude = gps.location.lng(), 6;
  }
}