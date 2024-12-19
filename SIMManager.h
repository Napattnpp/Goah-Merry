class SIMManager {
  private:
    void sendAtCommand(String toSend, const int timeout);

  public:
    String apn = "";
    String usernameApn = "";
    String passwrodApn = "";

    // Set constructor
    SIMManager(String _apn, String _usernameApn, String _passwrodApn) {
      apn = _apn;
      usernameApn = _usernameApn;
      passwrodApn = _passwrodApn;
    }

    void init();
    void rawCommand();
    void sendDataToServer(String URL, String toSend);
};

void SIMManager::sendAtCommand(String toSend, const int timeout) {
  SIMSerial.println(toSend);
  // Serial.println(toSend);

  long time = millis();
  while ((time+timeout) >= millis()) {
    while (SIMSerial.available()) {
      char currentChar = SIMSerial.read();
      Serial.write(currentChar);
    }
  }
  Serial.println("");

  delay(300);
}

void SIMManager::init() {
  SIMSerial.begin(9600);
  delay(1000);
  sendAtCommand("AT", 5000);
  sendAtCommand("AT+SAPBR=3,1,Contype,GPRS", 3000);
  sendAtCommand("AT+SAPBR=3,1,APN," + apn, 3000);

  if (usernameApn != "") {
    sendAtCommand("AT+SAPBR=3,1,USER," + usernameApn, 3000);
  }
  if (passwrodApn != "") {
    sendAtCommand("AT+SAPBR=3,1,PWD," + passwrodApn, 3000);
  }

  sendAtCommand("AT+CSQ", 4000);
}

void SIMManager::rawCommand() {
  if (Serial.available()) {
    SIMSerial.write(Serial.read());
  }
  if (SIMSerial.available()) {
    Serial.write(SIMSerial.read());
  }
}

// URL must be http not https
void SIMManager::sendDataToServer(String URL, String toSend) {
  sendAtCommand("AT+SAPBR=1,1", 3000);
  sendAtCommand("AT+SAPBR=2,1", 3000);
  // Initialize HTTP Service
  sendAtCommand("AT+HTTPINIT", 3000);
  // Set URL
  sendAtCommand("AT+HTTPPARA=URL," + URL, 3000);
  sendAtCommand("AT+HTTPPARA=CID,1", 3000);
  // Set content type
  sendAtCommand("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded", 3000);

  sendAtCommand("AT+HTTPDATA=256,3000", 3000);
  sendAtCommand(toSend, 3000);
  sendAtCommand("AT+HTTPACTION=1", 3000);
  sendAtCommand("AT+HTTPREAD", 3000);

  sendAtCommand("AT+HTTPTERM", 3000);
  sendAtCommand("AT+SAPBR=0,1", 3000);
}