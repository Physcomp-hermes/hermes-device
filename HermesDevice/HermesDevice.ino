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

// Vibration related values
const int pwmChannel = 0;
const int pwmFreq = 1000;
const int pwmResolution = 8; // 8-bit
int signal_strength = 0; // vibration strength
//int vib_strength = 0;
int motorPin = 21; // motor control pin
bool vibrating = false;
int vib_freq = 0; // number of ticks the thing is on/off
int freq_counter = 0;
int prev_strength = 0;

int connPin = 23;


int updateStrength(){
  
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
  while(!received){
    if(client.available()){
      recvData = client.read();
      received = 1;
    }
  }
//  Serial.println(recvData);
  client.stop();
  return recvData;
}
void vibrate(){
  if(vib_freq == 0){
    vibrating = false;
    ledcWrite(pwmChannel, 0);
    return;
  }
  if(freq_counter == vib_freq){
    vibrating = !vibrating;
    freq_counter = 0;
  } else{
    freq_counter++;
  }
  if(vibrating){
    ledcWrite(pwmChannel, 255);
  } else{
    ledcWrite(pwmChannel, 0);
  }
  return;
}

void setup() {
  Serial.begin(115200);
  delay(10);

  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(motorPin, pwmChannel);
  pinMode(connPin, OUTPUT);
  
  
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  
}

void loop() {
  
  char strengthChar;
  strengthChar = updateStrength();
  // change vibration strength based on strength
  
  int strength = strengthChar - '0';
  Serial.println(strength);
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
