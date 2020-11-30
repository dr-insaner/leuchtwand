#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//define Neopixel LED Stripe
#define LED_PIN     8
#define LED_COUNT  300
// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255 // Set BRIGHTNESS to about 1/5 (max = 255)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed


// PINs of white stripes
const int GPIOstrip_L1 = 1; // 16 corresponds to GPIO16
const int GPIOstrip_L2 = 2; // 17 corresponds to GPIO16
const int GPIOstrip_R1 = 3; // 18 corresponds to GPIO16
const int GPIOstrip_R2 = 4; // 19 corresponds to GPIO16

// setting PWM properties
int helligkeit = 50;

//definitions of buttons
const int WhiteButton = 10;
int WhiteButton_state = 0;
int Whitestate = 0;

const int ColorButton = 11;
int ColorButton_state = 0;
int ColorState = 0;

const int EffectButton = 12;
int EffectButton_state = 0;
int EffectState = 0;

int lastButton = 0;


void setup(){
  Serial.begin(9600);
  // configure LED PWM functionalitites
  pinMode(GPIOstrip_L1, OUTPUT);
  pinMode(GPIOstrip_L2, OUTPUT);
  pinMode(GPIOstrip_R1, OUTPUT);
  pinMode(GPIOstrip_R2, OUTPUT);  

  //PMW for White
  pinMode(WhiteButton, INPUT);
  pinMode(ColorButton, INPUT);
  pinMode(EffectButton, INPUT);

  //init NeoPixelStripe
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop(){
  
  //button
  WhiteButton_state = digitalRead(WhiteButton);
  ColorButton_state = digitalRead(ColorButton);
  EffectButton_state = digitalRead(EffectButton);
  
  if (WhiteButton_state == 1){
    delay(500);
    lastButton = 0;
    Whitestate = Whitestate +1;
    if (Whitestate == 5){
      Whitestate = 0;
    }
  Serial.print("Choice White: ");
  Serial.println(WhiteButton);
  }
  else if (ColorButton_state == 1){
    delay(500);
    lastButton = 1;
    ColorState = ColorState +1;
    if (ColorState == 5){
      ColorState = 0;
    }
  Serial.print("Choice Color: ");
  Serial.println(ColorButton);
  }
  else if (EffectButton_state == 1){
    delay(500);
    lastButton = 2;
    EffectState = EffectState +1;
    if (EffectState == 5){
      EffectState = 0;
    }
  Serial.print("Choice Effect: ");
  Serial.println(EffectButton);
  }
  
// white light
  if (lastButton == 0){
    switch (Whitestate){
      case 0:
        helligkeit= 50;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show();  
        break;
      case 1:
        helligkeit= 100;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show();  
        break;    
      case 2:
        helligkeit= 150;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;    
      case 3:
        helligkeit= 200;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;  
      case 4:
        helligkeit= 255;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;   
      default:
        helligkeit= 1;
        analogWrite(GPIOstrip_L1, helligkeit);
        analogWrite(GPIOstrip_L2, helligkeit);
        analogWrite(GPIOstrip_R1, helligkeit);
        analogWrite(GPIOstrip_R2, helligkeit);
        strip.fill(strip.Color(  helligkeit/10,   0,   0, 50),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;
    }
  }

//coloreffects
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
  if (lastButton == 1){
    //first turn white stripes off
    helligkeit= 0;
    analogWrite(GPIOstrip_L1, helligkeit);
    analogWrite(GPIOstrip_L2, helligkeit);
    analogWrite(GPIOstrip_R1, helligkeit);
    analogWrite(GPIOstrip_R2, helligkeit);
    switch (ColorState){
      case 0:
        helligkeit= 50;
        strip.fill(strip.ColorHSV(1*65535/6, 255, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show();  
        break;
      case 1:
        helligkeit= 100;
        strip.fill(strip.ColorHSV(2*65535/6, 255, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show();  
        break;    
      case 2:
        helligkeit= 150;
        strip.fill(strip.ColorHSV(3*65535/6, 255, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;    
      case 3:
        helligkeit= 200;
        strip.fill(strip.ColorHSV(5*65535/6, 255, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;  
      case 4:
        helligkeit= 255;
        strip.fill(strip.ColorHSV(65535, 255, helligkeit),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;   
      default:
        helligkeit= 1;
        strip.fill(strip.ColorHSV(25000, 1, 10),  0, LED_COUNT);        //  Set pixel's color (in RAM)
        strip.show(); 
        break;
    }
  }
}
