#include <ESP8266WiFi.h>

// Replace with your WIFI credentials
const char* ssid     = "YOUR WIFI NAME";
const char* password = "YOUR WIFI PASSWORD";

// Smart home board relay
const uint8_t RELAY_ID[4] = {5, 4, 15, 12};
bool relay_state[4] = {0, 0, 0, 0};
String relay_status_str[4] ={"OFF", "OFF", "OFF", "OFF"};
String relay_url_str[4] ={"ON", "ON", "ON", "ON"};

WiFiServer server(80); // HTTP port 80

void setup() {
  Serial.begin(115200);

  // Set relay pinout
  for (int8_t i = 0; i < 4; i++) {
    pinMode(RELAY_ID[i], OUTPUT);
  }

  for (int8_t i = 0; i < 4; i++) {
    digitalWrite(RELAY_ID[i], relay_state[i]);
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  // Check if there's a new connection
  if (client) {
    if (client.available() && client.connected()) {
      String clientRead = client.readStringUntil('\n');
      clientRead.trim();  // keep out \r
      Serial.println(clientRead);
      String buttonId = clientRead.substring(clientRead.indexOf('=', clientRead.indexOf('?')) + 1, clientRead.indexOf('=', clientRead.indexOf('?')) + 2);
      String buttonValue = clientRead.substring(clientRead.indexOf('=', clientRead.indexOf('&')) + 1, clientRead.indexOf(' ', clientRead.indexOf('&')));
      Serial.println(buttonId);
      Serial.println(buttonValue);

      //relay_value_str[] = buttonValue;
      relay_state[buttonId.toInt() - 1] = buttonValue=="ON";

      Serial.print("Relay status: ");
      for (int8_t i = 0; i < 4; i++) {
        Serial.print("-");
        Serial.print(relay_state[i]);
        relay_status_str[i] = relay_state[i]? "ON" : "OFF";
        relay_url_str[i] = relay_state[i]? "OFF" : "ON";
        digitalWrite(RELAY_ID[i], relay_state[i]);
      }
      Serial.println();

      Serial.print("Relay status string: ");
      for (int8_t i = 0; i < 4; i++) {
        Serial.print("-");
        Serial.print(relay_status_str[i]);
        //digitalWrite(RELAY_ID[buttonId.toInt() - 1], relay_state[i]);
      }
      Serial.println();

      // Response to client: connection is OK
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println("Connection: close");
      client.println();

      // Response to client: Web veiw
      client.println("<!DOCTYPE html>");
      client.println("<html>");
      client.println("<head>");
      client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
      client.println("<style>");
      client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println(".button {border-radius: 5px; color: white; padding: 16px 20px; font-size: 14px; margin: 2px; cursor: pointer; width:300px;}");
      client.println(".button-ON {background-color: #F66B5D; border: 1px solid #F66B5D;}");
      client.println(".button-OFF {background-color: #77878A; border: 1px solid #77878A;}");
      client.println(".button-ON:hover{background-color: white; border: 1px solid black; color:black;}");
      client.println(".button-OFF:hover{background-color: white; border: 1px solid #F66B5D; color:#F66B5D;}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<h1>ESP Smart Home</h1>");
      client.println("<p><a href=\"https://www.etronicskh.com/\"</a>www.etronicskh.com</p>");
      client.println("</br>");
      client.println("<p><a href=\"/button?id=1&value="+ relay_url_str[0] +"\"><button class=\"button button-"+ relay_status_str[0] +"\">Light 1 "+ relay_status_str[0] +"</button></a></p>");
      client.println("<p><a href=\"/button?id=2&value="+ relay_url_str[1] +"\"><button class=\"button button-"+ relay_status_str[1] +"\">Light 2 "+ relay_status_str[1] +"</button></a></p>");
      client.println("<p><a href=\"/button?id=3&value="+ relay_url_str[2] +"\"><button class=\"button button-"+ relay_status_str[2] +"\">Light 3 "+ relay_status_str[2] +"</button></a></p>");
      client.println("<p><a href=\"/button?id=4&value="+ relay_url_str[3] +"\"><button class=\"button button-"+ relay_status_str[3] +"\">Light 4 "+ relay_status_str[3] +"</button></a></p>");
      client.println("<p><a href=\"/\"</a>Refresh</p>");
      client.println("</body>");
      client.println("</html>");
      
      server.flush(); // Clean server buffer
    }
    client.stop();  // Stop the connection
  }

}
