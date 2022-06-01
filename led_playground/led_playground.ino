#include <Adafruit_CircuitPlayground.h>

int pixelColour[NUMLED] = {3,0,0,2};

void set_led(){
  pixels.clear(); //sets all the pixel colours off
  for(int i = 0 ; i < NUMLED; i++){
    switch(pixelColour[i]){
      case 0:
        CircuitPlayground.setPixelColor(i, pixels.Color(150, 0, 150));   //pink
        break;
      case 1:
        CircuitPlayground.setPixelColor(i, pixels.Color(150, 150, 0));   //yellow
        break;
      case 2:
        CircuitPlayground.setPixelColor(i, pixels.Color(0, 100, 200));   //cyan
        break;
      case 3:
        CircuitPlayground.setPixelColor(i, pixels.Color(0, 0, 150)); //blue
        break;
      case 4:
        CircuitPlayground.setPixelColor(i, pixels.Color(150, 0, 0)); //red
        break;  
    }
  }  
  CircuitPlayground.show();
}

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); 
  CircuitPlayground.clear();
  set_led();
}


void loop() {
  // put your main code here, to run repeatedly:

  // First
//  CircuitPlayground.setPixelColor(0, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(0, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(0, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(0, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(0, 150, 0, 150);    // pink

  // Second
  //CircuitPlayground.setPixelColor(1, 150, 0, 0);      // red
//  CircuitPlayground.setPixelColor(1, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(1, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(1, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(1, 150, 0, 150);    // pink

  // Third
  //CircuitPlayground.setPixelColor(2, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(2, 0, 150, 0);      // green
//  CircuitPlayground.setPixelColor(2, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(2, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(2, 150, 0, 150);    // pink

  // Fourth
  //CircuitPlayground.setPixelColor(3, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(3, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(3, 0, 0, 150);      // blue
//  CircuitPlayground.setPixelColor(3, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(3, 150, 0, 150);    // pink
  
  
  delay(1000);

}
