class LocalWebServer {
  private:
    String htmlCode = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    </head>
    <body>
    <div class="slide-container">
    <dic class="value-container">
    <samp id="direction-text">0</samp>
    </dic>
    <input type="range" min="65" max="135" value="90" id="direction">
    </div>

    <script>
    var slider = document.getElementById("direction");
    var text = document.getElementById("direction-text");
    text.innerHTML = slider.value;
    slider.oninput = function() {
        text.innerHTML = this.value;
    }
    </script>
    </body>
    </html>
    )";

  public:
    // Start local web server at port 80.
    WiFiServer myLocalWebServer;

    // Constructor
    LocalWebServer(int port);

    void init();
    void start();
};

// Constructor implementation.
LocalWebServer::LocalWebServer(int port) : myLocalWebServer(port) {}

void LocalWebServer::init() {
  myLocalWebServer.begin();
}

void LocalWebServer::start() {
  // Get number of bytes available for reading from myLocalWebServer.
  WiFiClient client = myLocalWebServer.available();

  // Check if client has connected.
  if (client) {
    String currentLine = "";

    Serial.println("New client connected");
    Serial.println("HTTP request: ");
    while (client.connected()) {
      if (client.available()) {
        // Read HTTP request header
        char currentChar = client.read();
        Serial.write(currentChar);

        if (currentChar == '\n') {
          if (currentLine.length() == 0) {
            // Response HTTP header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println();

            // Show HTML page
            client.println();
            client.println(htmlCode);

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (currentChar != '\r') {
          currentLine += currentChar;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
  }
}