#include <WiFi.h>
#include <WebSocketClient.h>

// WIFI connection
const char* ssid     = "Jamas";
const char* password = "jamajama";
WiFiClient client;

// Socket connection
char thisID = '2';
char host[] = "192.168.142.53";
int port = 5050;
WebSocketClient webSocketClient;

// Motor control
bool vibrating = false;
int vib_freq = 0; // number of ticks the thing is on/off
int freq_counter = 0;
int prev_strength = 0;
char strengthChar; // character used to represent the vibration strength

// Pins used
int connPin = 23;
int wifiPin = 22;
int motorPin = 21; // motor control pin


int updateStrength(){

  // Make socket connection and update connection status
  if (client.connect(host, port)) {
//    Serial.println("Connected");
    digitalWrite(connPin, LOW);
  } else {
//    Serial.println("Connection failed.");
    digitalWrite(connPin, HIGH);
    return '0';
  }
  
  client.write(thisID);
  delay(50);
  
  char recvData;
  bool received = 0;
  // Wait for message to be received
  while(!received){
    if(client.available()){
      recvData = client.read();
      received = 1;
    }
  }
  // close socket
  client.stop();
  return recvData;
}

void vibrate(){
  // Vibrate using updated frequency. 
  // Each execution of the loop can be considered sa a tick
  if(vib_freq == 0){
    // No vibration
    vibrating = false;
    digitalWrite(motorPin, LOW);
    return;
  }
  
  if(freq_counter == vib_freq){
    vibrating = !vibrating;
    freq_counter = 0;
  } else{
    freq_counter++;
  }
  
  digitalWrite(motorPin, vibrating);
  return;
}

void setup() {
  // This function starts the serial and wireless connection
  Serial.begin(115200);
  delay(10);

  pinMode(motorPin, OUTPUT);
  pinMode(connPin, OUTPUT);
  pinMode(wifiPin, OUTPUT);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(wifiPin, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  
}

void loop() {
  
  strengthChar = updateStrength();
  
  // change vibration strength based on strength
  int strength = strengthChar - '0';
  Serial.println(strength);
  // only update strength when it changed
  if(prev_strength != strength){
    prev_strength = strength;
    if(strength == 0){
      vib_freq = 0;
    } else{
      vib_freq = 4 - strength;
    }
    freq_counter = 0;
  }
  vibrate();
  delay(200);
  
}
