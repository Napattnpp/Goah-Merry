class WiFiManager {
  private:
    bool skipPinState = 0;

    int counter = 0;
    const int timeout = 100;

    const char* apSSID = "Goah-Merry";
    const char* apPassword = "12123121211";

  public:
    const char* ssid = "";
    const char* password = "";

    // Set constructor.
    WiFiManager(const char* _ssid, const char* _password) {
      ssid = _ssid;
      password = _password;
    }

    void connect();
    void info();
};

void WiFiManager::connect() {
  Serial.print("Connecting to WiFi");
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Timeout is 300ms * 100times = 30000ms --> 30 seconds
  while (WiFi.status() != WL_CONNECTED && counter <= timeout) {
    Serial.print(".");

    if (!digitalRead(SKIP_PIN)) {
      // skip pin is enable.
      skipPinState = 1;
      break;
    }

    counter++;
    delay(300);
  }
  Serial.println();

  if (skipPinState) {
    onBoardSign.skipTask();
    Serial.println("[Task was skipped]");
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    Serial.println("Change wifi mode to AP");
    delay(1000);
    WiFi.softAP(apSSID, apPassword);
  } else if (counter > timeout) {
    Serial.println("Timeout");
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    Serial.println("Change wifi mode to AP");
    WiFi.softAP(apSSID, apPassword);
  } else {
    Serial.println("WiFi connected"); 
  }
}

void WiFiManager::info() {
  Serial.print("WiFi Mode: ");
  Serial.println(WiFi.getMode());
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Password: ");
  Serial.println(password);

  // Infomation about softAP mode.
  Serial.print("AP SSID: ");
  Serial.println(apSSID);
  Serial.print("AP password: ");
  Serial.println(apPassword);

  Serial.print("WiFi status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected");  
  } else {
    Serial.println("disconnect");
  }
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Soft AP IP: ");
  Serial.println(WiFi.softAPIP());
}