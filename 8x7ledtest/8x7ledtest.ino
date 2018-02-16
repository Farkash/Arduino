#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

byte led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins for LEDs

void setup() {
  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();


}

void loop() {

//  Plex.pixel(0,1,1);
//  Plex.display();
//  delay(500);
//
// 
//  Plex.clear();
//  Plex.display();


  for(int i=0; i<8; i++){
    for(int j=0; j<7; j++){
      Plex.pixel(i,j,1);
      Plex.display();
    }
  }

//  delay(500);
    
  
}



