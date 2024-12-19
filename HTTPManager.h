class HTTPManager {
  public:
    const char* URL = "";

    // Set constructor.
    HTTPManager(const char* _URL) {
      URL = _URL;
    }

    void sendData(String toSend);
    String convertToHttpHeader(double latitude, double longitude, String any, String method, String APIKEY);
};

void HTTPManager::sendData(String toSend) {
  HTTPClient httpClient;

  // Try to connect to server.
  if (httpClient.begin(URL)) {
    Serial.println("Connected to server");

    // Set HTTP header.
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Send data and get response code.
    int httpResponseCode = httpClient.POST(toSend);
    if (httpResponseCode) {
      // Successfully.
      Serial.print("HTTP response code: ");
      Serial.println(httpResponseCode);
      Serial.print("HTTP response: ");
      Serial.println(httpClient.getString());

    } else {
      // Unsuccessfully.
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
  } else {
    Serial.println("Can't connect to server");
  }
}

String HTTPManager::convertToHttpHeader(double latitude, double longitude, String any, String method, String APIKEY) {
  return String("id=" + String(BOAT_ID) + "&name=" + "'" + String(BOAT_NAME) + "'" + "&lat=" + String(latitude) + "&lng=" + String(longitude) + "&any=" + any + "&method=" + method + "&APIKEY=" + APIKEY);
}


