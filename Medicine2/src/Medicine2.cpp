/* 
 * Project Take your Medicine
 * Author: Monica Waikaniwa
 * Date: 
 * 
 * 
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include <Adafruit_MPR121.h>



SYSTEM_MODE(AUTOMATIC);

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
const int PIXELCOUNT = 8;
int pixelNum;
int r;
int g;
String days [8]= (["Sunday"],["Monday"],["Tuesday"],["Wednesday"],["Thursday"],["Friday"],["Saturday"];
Adafruit_NeoPixel;
pixel(PIXELCOUNT,SPI1,WS2812B);


void readTouchState();




void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  Serial.printf("Adafruit MPR121 Capacitive Touch sensor test"); 
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.printf("MPR121 not found, check wiring?\n");
    //while (1)
  }
  Serial.printf("MPR121 found!");

  pixel.begin();
  pixel.setBrightness(100);
  pixel.show();

  r = random(255);
  g = random(255);
  
  for(pixelNum=0;pixelNum<=8;pixelNum++){
    pixel.setPixelColor(pixelNum, r, g);
    pixel.show();
    delay(100);
    pixel.clear();
  }
}
  for(pixelNum=8, pixelNum>=0, pixelNum--){
    pixel.setPixelColor(pixelNum, r, g);
    pixel.show();
    delay(100);
    pixel.clear();


void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

}

void readTouchState(){ 
   for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.printf("%i touched\n",i); 
    }
     // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.printf("%i",i); 
      Serial.printf("released");
    }
  }
  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;

}


