#include <WiFi.h>
#include <WebSocketClient.h>
#include <Adafruit_NeoPixel.h>

#define PIN 15
#define NUMLED 4

//char data = 0;

// WIFI connection
const char* ssid     = "Jamas";
const char* password = "jamajama";
WiFiClient client;

// Socket connection
const char* colString = "C-1";
const char* vibString = "V-1";
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
int motorPin = 21; // motor control pin

// Set neopixel
Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);
int pixelColour[NUMLED] = {1,1,1,1};

int updateStrength(){

  // Make socket connection and update connection status
  if (!client.connect(host, port)) {
    Serial.println("Can't connect to client");
    return '0';
  }
  
  // send vibration signal
  client.write(vibString);
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

/**
 * Function that updates device colour from server
 */
int updateColour(){
  
  // Make socket connection and update connection status
  if (!client.connect(host, port)) {
    Serial.println("Can't connect to client");
    return 1;
  }
  client.write(colString);
  delay(50);
  char recvData;
  bool received = 0;
  int colour = 0;
  while(!received){
    if(client.available()){
      for(int i = 0; i < NUMLED; i++){
        recvData = client.read();
        // convert to integer
        colour = recvData - '0';
        pixelColour[i] = colour;
        Serial.print(recvData);
      }
      Serial.print("\n");
      received = 1;
    }
  }
  set_led();
  return 0;
}

void set_led(){
  pixels.clear(); //sets all the pixel colours off
  for(int i = 0 ; i < NUMLED; i++){
    switch(pixelColour[i]){
      case 0:
        pixels.setPixelColor(i, pixels.Color(150, 0, 0));   //red 
        break;
      case 1:
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));   //green
        break;
      case 2:
        pixels.setPixelColor(i, pixels.Color(0, 0, 150));   //blue
        break;
      case 3:
        pixels.setPixelColor(i, pixels.Color(150, 150, 0)); //yellow
        break;
      case 4:
        pixels.setPixelColor(i, pixels.Color(150, 0, 150)); //pink
        break;  
    }
  }  
  pixels.show();
}

void vibrate(int strength){
  
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
  
  // neopixel set up
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  
  pixels.begin();
  pixels.clear();
  // initialise pins
  pinMode(motorPin, OUTPUT);
  
  // Connect to wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  set_led();
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  updateColour();
}

void loop() {
//  updateStrength();
  
  strengthChar = updateStrength();
  // change vibration strength based on strength
  int strength = strengthChar - '0';
  vibrate(strength);
  delay(1000);
  
}
