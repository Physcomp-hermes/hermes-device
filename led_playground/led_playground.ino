#include <Adafruit_CircuitPlayground.h>

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // First
  CircuitPlayground.setPixelColor(0, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(0, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(0, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(0, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(0, 150, 0, 150);    // pink

  // Second
  //CircuitPlayground.setPixelColor(1, 150, 0, 0);      // red
  CircuitPlayground.setPixelColor(1, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(1, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(1, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(1, 150, 0, 150);    // pink

  // Third
  //CircuitPlayground.setPixelColor(2, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(2, 0, 150, 0);      // green
  CircuitPlayground.setPixelColor(2, 0, 0, 150);      // blue
  //CircuitPlayground.setPixelColor(2, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(2, 150, 0, 150);    // pink

  // Fourth
  //CircuitPlayground.setPixelColor(3, 150, 0, 0);      // red
  //CircuitPlayground.setPixelColor(3, 0, 150, 0);      // green
  //CircuitPlayground.setPixelColor(3, 0, 0, 150);      // blue
  CircuitPlayground.setPixelColor(3, 150, 150, 0);    // yellow
  //CircuitPlayground.setPixelColor(3, 150, 0, 150);    // pink
  
  
  

}
