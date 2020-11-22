// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  200

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:

//Die LEDs der einzelnen Buchstaben definieren für irgendwelche Effekte
int oskar_O[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
int oskar_S[] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38};
int oskar_K[] = {39,40,41,42,43,44,45,46,47,48,49,50,51,52};
int oskar_A[] = {53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72};
int oskar_R[] = {73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92};

int iva_1[] = {0,1,2,3,4,5};
int iva_I[] = {6,7,8,9,10,11,12,13,14,15,16};
int iva_V[] = {17,18,19,20,21,22,23,24,25,26,27,28,29,30};
int iva_A[] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
int iva_2[] = {51,52,53,54,55,56};

//Hier möchte ich eine MAtrix definieren die aus den folgenden Spalten besteht. Da wo -1 ist gibt es keine LED
int c1[] = {0,1,2,3,4,5,6,7};
int c2[] = {7,-1,-1,-1,-1,-1,19};
int c3[] = {8,-1,-1,-1,-1,-1,18};
int c4[] = {9,-1,-1,-1,-1,-1,17};
int c5[] = {10,11,12,13,14,15,16};
int c6[] = {39,40,41,42,43,44,45};
int c7[] = {-1,-1,-1,46,-1,-1,-1};
int c8[] = {-1,-1,47,-1,50,-1,-1};
int c9[] = {-1,48,-1,-1,-1,51,-1};
int c10[]= {49,-1,-1,-1,-1,-1,52};

const int rows = 7;
const int columns = 10;

int matrix[rows][columns];

void setup() {
  Serial.begin(9600);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);

//hier der erste Versuch aus den 1D arrays ein 2D array zu machen
  for(int r = 0; r<rows; r++) {
    for (int c = 0; c<columns; c++) {
      matrix[r][c] = c1[r];
    }
  }
  
}

void loop() {

  show_letter(strip.Color(255,   0,   0, 0), oskar_O, *(&oskar_O + 1) - oskar_O, "oskar");
  delay(1000);
  show_letter(strip.ColorHSV(65000, 255, 200), oskar_S, *(&oskar_S + 1) - oskar_S, "oskar");
  delay(1000);
  show_letter(strip.ColorHSV(60000, 255, 200), oskar_K, *(&oskar_K + 1) - oskar_K, "oskar");
  delay(1000);
  show_letter(strip.ColorHSV(55000, 255, 200), oskar_A, *(&oskar_A + 1) - oskar_A, "oskar");
  delay(1000);
  show_letter(strip.ColorHSV(50000, 255, 200), oskar_R, *(&oskar_R + 1) - oskar_R, "oskar");
  delay(1000);
  show_letter(strip.ColorHSV(45000, 255, 200), iva_1, *(&iva_1 + 1) - iva_1, "iva");
  delay(1000);
  show_letter(strip.ColorHSV(40000, 255, 200), iva_I, *(&iva_I + 1) - iva_I, "iva");
  delay(1000);
  show_letter(strip.ColorHSV(35000, 255, 200), iva_V, *(&iva_V + 1) - iva_V, "iva");
  delay(1000);
  show_letter(strip.ColorHSV(30000, 255, 200), iva_A, *(&iva_A + 1) - iva_A, "iva");
  delay(1000);
  show_letter(strip.ColorHSV(25000, 255, 200), iva_2, *(&iva_2 + 1) - iva_2, "iva");
  delay(1000);
  strip.clear();

  
  colorZini(strip.Color(255,   0,   0)     , 50); // Red
  strip.clear();
    
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0)     , 50); // Red
  colorWipe(strip.Color(  0,   0,   0, 255), 50); // True white (not RGB white)

  whiteOverRainbow(75, 5);

  pulseWhite(5);

  rainbowFade2White(3, 3, 1);
}

void show_letter(uint32_t color, int letter[], int laenge, char* namen) { //hier kommt es zur Fehlermeldung, da ich string zu char mache. Das darf man wohl nicht in c++
    Serial.print(namen);
    Serial.println(":"); 
    Serial.println(letter[0]);
    Serial.println(laenge);
    strip.clear();
    if (namen=="iva") letter[0]=letter[0]+93;
    strip.fill(color,  letter[0], laenge);        //  Set pixel's color (in RAM)
    strip.show();  
}

void colorZini(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.clear();
    strip.setPixelColor(i, strip.ColorHSV(i*1000, 255, 250));         //  Set pixel's color (in RAM)
    strip.setPixelColor(i-1,strip.ColorHSV(i*1000, 255, 150));         //  Set pixel's color (in RAM)
    strip.setPixelColor(i-2,strip.ColorHSV(i*1000, 255, 130));         //  Set pixel's color (in RAM)
    strip.setPixelColor(i-3,strip.ColorHSV(i*1000, 255, 100));         //  Set pixel's color (in RAM)
    strip.setPixelColor(i-4,strip.ColorHSV(i*1000, 255, 80));         //  Set pixel's color (in RAM) 
    strip.setPixelColor(i-4,strip.ColorHSV(i*1000, 255, 40));         //  Set pixel's color (in RAM
    strip.setPixelColor(i-4,strip.ColorHSV(i*1000, 255, 10));         //  Set pixel's color (in RAM) 
             
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if(whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for(;;) { // Repeat forever (or until a 'break' or 'return')
    for(int i=0; i<strip.numPixels(); i++) {  // For each pixel in strip...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
    }

    strip.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= strip.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= strip.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}

void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}

void rainbowFade2White(int wait, int rainbowLoops, int whiteLoops) {
  int fadeVal=0, fadeMax=100;

  // Hue of first pixel runs 'rainbowLoops' complete loops through the color
  // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to rainbowLoops*65536, using steps of 256 so we
  // advance around the wheel at a decent clip.
  for(uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops*65536;
    firstPixelHue += 256) {

    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      uint32_t pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue, 255,
        255 * fadeVal / fadeMax)));
    }

    strip.show();
    delay(wait);

    if(firstPixelHue < 65536) {                              // First loop,
      if(fadeVal < fadeMax) fadeVal++;                       // fade in
    } else if(firstPixelHue >= ((rainbowLoops-1) * 65536)) { // Last loop,
      if(fadeVal > 0) fadeVal--;                             // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

  for(int k=0; k<whiteLoops; k++) {
    for(int j=0; j<256; j++) { // Ramp up 0 to 255
      // Fill entire strip with white at gamma-corrected brightness level 'j':
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
    delay(1000); // Pause 1 second
    for(int j=255; j>=0; j--) { // Ramp down 255 to 0
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
  }

  delay(500); // Pause 1/2 second
}
