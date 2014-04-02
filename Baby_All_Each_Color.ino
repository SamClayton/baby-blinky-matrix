
#include "Tlc5940.h"

// For hue calc
int R, G, B;

void setup()
{
  /* Call Tlc.init() to setup the tlc.
     You can optionally pass an initial PWM value (0 - 4095) for all channels.*/
  Tlc.init();
  hueToRGB(288, 89);
  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Hello world!");  // prints hello with ending line break 
}

/* This loop will create a Knight Rider-like effect if you have LEDs plugged
   into all the TLC outputs.  NUM_TLCS is defined in "tlc_config.h" in the
   library folder.  After editing tlc_config.h for your setup, delete the
   Tlc5940.o file to save the changes. */
 
void loop() {
  /*
  for (int TLC = 0; TLC < NUM_TLCS; TLC++) {
    for (int LED = 0; LED < 16; LED+=3) {
      Tlc.clear();
      
      Tlc.set(((TLC * 16) + LED), 4095);
      
      Tlc.update();
      //Serial.println ((TLC * 16) + LED);
      delay(500);
    }
  }
  */
  /*
  //Serial.println("end loop");
  for (int TLC = 0; TLC < NUM_TLCS; TLC++) {
    for (int LED = 0; LED < 16; LED++) {
      Tlc.clear();
    
      Tlc.set(((TLC * 16) + LED), 4095);
    
      Tlc.update();
      delay(500);
    }
  }
  */
  
  // First 2 set to blue
  /*
  Tlc.clear();
  Tlc.set(2, 4095);
  Tlc.update();
  delay(5000);
  Tlc.set(5, 4095);
  Tlc.update();
  delay(5000);
  */
  setAllBlue();
  Serial.println("Waiting...");
  delay(500);
}

void setAllBlue() {
  int blue[3] = {0,0,4095};
  Tlc.clear();
  int physLEDs = NUM_TLCS / 3 * 16;
  for (int physLED = 0; physLED < physLEDs; physLED++) {
    //Serial.println(physLED);
    //setPhysLED(physLED, 116);
    setPhysLED(physLED, blue);
  }
  Tlc.update();
}

void setPhysLED(int physLEDnum, int color[3]) {
  Serial.print(physLEDnum*3); Serial.print(": "); Serial.print(color[0]); Serial.print(", "); Serial.print(color[1]); Serial.print(", "); Serial.print(color[2]); 
  Tlc.set(physLEDnum * 3, color[0]);
  Tlc.set((physLEDnum * 3)+1, color[1]);
  Tlc.set((physLEDnum * 3)+2, color[2]);
  //Tlc.update();
  Serial.println("");
}
/*
void setPhysLED(int physLEDnum, int hue) {
  
}
*/

void setLED(int LEDnum, int color[3]) {
  Tlc.set(LEDnum * 3, color[0]);
  Tlc.set((LEDnum * 3) + 1, color[1]);
  Tlc.set((LEDnum * 3) + 2, color[2]);
}

void hueToRGB( int hue, int brightness)
{
    unsigned int scaledHue = (hue * 6);
    unsigned int segment = scaledHue / 256; // segment 0 to 5 around the 
                                            // color wheel
    unsigned int segmentOffset = 
      scaledHue - (segment * 256); // position within the segment

    unsigned int complement = 0;
    unsigned int prev = (brightness * ( 255 -  segmentOffset)) / 256;
    unsigned int next = (brightness *  segmentOffset) / 256;

    /*
    if(invert)
    {
      brightness = 255-brightness;
      complement = 255;
      prev = 255-prev;
      next = 255-next;
    }
    */

    switch(segment ) {
    case 0:      // red
        R = brightness;
        G = next;
        B = complement;
    break;
    case 1:     // yellow
        R = prev;
        G = brightness;
        B = complement;
    break;
    case 2:     // green
        R = complement;
        G = brightness;
        B = next;
    break;
    case 3:    // cyan
        R = complement;
        G = prev;
        B = brightness;
    break;
    case 4:    // blue
        R = next;
        G = complement;
        B = brightness;
    break;
   case 5:      // magenta
    default:
        R = brightness;
        G = complement;
        B = prev;
    break;
    }
}
