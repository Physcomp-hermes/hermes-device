#include <WiFi.h>
#include <WebSocketClient.h>
#include <Adafruit_NeoPixel.h>

#define PIN 15
#define NUMPIXEL 4

//char data = 0;

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

// Set neopixel
Adafruit_NeoPixel pixels(NUMPIXEL, PIN, NEO_GRB + NEO_KHZ800);
int pixelColour[4] = {1,0,0,0};

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
  
//  client.write(thisID);
  client.write('C');
  client.write('-');
  client.write('2');
  delay(50);
  char recvData;
  bool received = 0;
  // Wait for message to be received
  while(!received){
    if(client.available()){
      for(int i = 0; i < 5; i++){
        recvData = client.read();
        Serial.print(recvData);
      }
      Serial.print("\n");
      received = 1;
    }
  }
  // close socket
  client.stop();
  return recvData;
}

void update_led(int* input){
  pixels.clear(); //sets all the pixel colours off
  int led_num = 4; // number of led
  for(int i =0 ; i < 4; i++){
    switch(input[i]){
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
//  
//  // initialise pins
//  pinMode(motorPin, OUTPUT);
//  pinMode(connPin, OUTPUT);
//  pinMode(wifiPin, OUTPUT);
//  
//  // Connect to wifi
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  
//  WiFi.begin(ssid, password);
//  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  digitalWrite(wifiPin, HIGH);
//  Serial.println("");
//  Serial.println("WiFi connected");  
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//  delay(1000);

  // neopixel set up
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  pixels.begin();
  update_led(pixelColour);
}

void loop() {
  
//  strengthChar = updateStrength();
//  // change vibration strength based on strength
//  int strength = strengthChar - '0';
//  Serial.println(strength);
//  vibrate(strength);
  delay(200);
  
}
