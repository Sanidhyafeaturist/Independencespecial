#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Motor control pins
const int motor1Forward = D1;
const int motor1Backward = D2;
const int motor2Forward = D3;
const int motor2Backward = D4;

// Ultrasonic sensor pins
const int triggerPin = D5;
const int echoPin = D6;

// Toy gun control pin
const int gunPin = D7;

ESP8266WebServer server(80);

// Function to initialize hardware
void initializeHardware() {
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(gunPin, OUTPUT);
}

// Function to connect to Wi-Fi
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Connected!");
  } else {
    Serial.println(" Failed to connect.");
  }
}

// Function to get the HTML for the web interface
String getHTML() {
  String html = "<html><body><h1>Military-Style Robot Control</h1>";
  html += "<button onclick=\"move('forward')\">Forward</button><br>";
  html += "<button onclick=\"move('backward')\">Backward</button><br>";
  html += "<button onclick=\"move('left')\">Left</button><br>";
  html += "<button onclick=\"move('right')\">Right</button><br>";
  html += "<button onclick=\"move('stop')\">Stop</button><br>";
  html += "<button onclick=\"move('check')\">Check Obstacle</button><br>";
  html += "<button onclick=\"move('fire')\">Fire</button><br>";
  html += "<script>function move(direction) { fetch('/move?dir=' + direction); }</script>";
  html += "</body></html>";
  return html;
}

// Handle root URL
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// Handle movement commands
void handleMove() {
  String direction = server.arg("dir");
  if (direction == "forward") {
    moveForward();
  } else if (direction == "backward") {
    moveBackward();
  } else if (direction == "left") {
    turnLeft();
  } else if (direction == "right") {
    turnRight();
  } else if (direction == "stop") {
    stopMovement();
  } else if (direction == "check") {
    checkObstacle();
  } else if (direction == "fire") {
    fireGun();
  }
  server.send(200, "text/plain", "Moving " + direction);
}

// Move functions
void moveForward() {
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
}

void moveBackward() {
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
}

void turnRight() {
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, HIGH);
}

void stopMovement() {
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
}

void checkObstacle() {
  long duration, distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; // Convert to cm
  
  if (distance < 20) {
    Serial.println("Obstacle detected!");
    stopMovement();
  } else {
    Serial.println("Path clear.");
  }
}

void fireGun() {
  digitalWrite(gunPin, HIGH); // Activate the gun
  delay(1000);                 // Fire duration
  digitalWrite(gunPin, LOW);  // Deactivate the gun
  Serial.println("Fired!");
}

// Setup function
void setup() {
  Serial.begin(115200);
  initializeHardware();
  connectWiFi();
  
  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
}
