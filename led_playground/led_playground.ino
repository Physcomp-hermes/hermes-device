#include <Adafruit_CircuitPlayground.h>

#define NUMLED 4
int pixelColour[NUMLED] = {3,0,0,2};


void set_led(){
  
  for(int i = 0 ; i < NUMLED; i++){
    switch(pixelColour[i]){
      case 0:
        
        CircuitPlayground.setPixelColor(i, 150, 0, 150);      // red
        break;
      case 1:
        
        CircuitPlayground.setPixelColor(i, 150, 150, 0);      // red
        break;
      case 2:
        
        CircuitPlayground.setPixelColor(i, 0, 100, 200);      // red
        break;
      case 3:
        
        CircuitPlayground.setPixelColor(i, 0, 0, 150);      // red
        break;
      case 4:
        
        CircuitPlayground.setPixelColor(i, 150, 0, 0);      // red
        break;  
    }
  }  
  CircuitPlayground.show();
}

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); 
  
  set_led();
}


void loop() {
  // put your main code here, to run repeatedly:
  
  delay(1000);

}
