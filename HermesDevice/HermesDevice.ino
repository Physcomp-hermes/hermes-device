#include <WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "Jamas";
const char* password = "jamajama";

// This is the ip of the host. I personally set static ip for host.
char host[] = "192.168.142.53";

// Port used for connection
int port = 5050;

WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;
char thisID = '2';
int strength = 0;
int updateStrength(){
  
  if (client.connect(host, port)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
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
  Serial.println(recvData);
  client.stop();
  return recvData;
}

void setup() {
  Serial.begin(115200);
  delay(10);

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
  Serial.println(strengthChar);
  
  // wait to fully let the client disconnect
  delay(1000);
  
}
