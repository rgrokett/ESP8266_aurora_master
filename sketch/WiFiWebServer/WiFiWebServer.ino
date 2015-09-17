/*
 *  Controller for modified Aurora Master projector
 *  Version 0.9 - 2015.09.17 Russell Grokett
 *
 *  See the Documentation for required hardware modifications
 *
 *  This sketch sets up a web server on port 80 of the ESP8266
 *  It will set High/Low a GPIO pin depending on the request
 *  http://server_ip/gpio/step will set the GPIO pin high then back low  
 *  server_ip is the IP address of the ESP8266 module. The IP will be 
 *  printed to Serial and the LED blinked when the module is connected.
 *  Each time the URL is called, it will step the Aurora Master to the 
 *  next pattern setting.
 *
 *  When you turn on the ESP8266 or reset it, if it succeeds in connecting
 *  to your WiFi network, you will see 4 blinks of the red LED.
 *  Else, use the IDE Serial Monitor set to 115,200 baud and reset ESP
 */

#include <ESP8266WiFi.h>

const char* ssid     = "MY_SSID";    // YOUR WIFI SSID
const char* password = "MY_PASS";    // YOUR WIFI PASSWORD

int PIN = 12;     // GPIO 12 connected to Aurora
int LED = 0;      // GPIO 0 (built-in LED)

// Create an instance of the server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);		// Use IDE Serial Monitor for debugging
  delay(10);

  // prepare GPIO
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, 0);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Blink onboard LED to signify its connected
  blink();
  blink();
  blink();
  blink();
}

// MAIN LOOP 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request 
  // 0 = low;  1 = high;  10 = high/low
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else if (req.indexOf("/gpio/step") != -1)
    val = 10;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO according to the request
  if (val == 10) {
    digitalWrite(PIN, 1);
    blink();
    digitalWrite(PIN, 0);
  }
  else 
    digitalWrite(PIN, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nGPIO is now ";
  if (val == 10)
    s += "stepped";
  else
    s += (val)?"high":"low";
  s += "\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void blink() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
}

