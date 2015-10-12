// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include <Wire.h>

// I2Cdev and BMA150 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "BMA150.h"

// class default I2C address is 0x38

BMA150 accel;

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

int16_t ax, ay, az;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(9600);

    // initialize device
    //Serial.println("Initializing I2C devices...");
    accel.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(accel.testConnection() ? "BMA150 connection successful" : "BMA150 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
    pinMode(12, OUTPUT);
}

void loop() {
  int pz = 0; //Previous z value
  int ppz = 0; //Previous previous z value;
  int da = 0;
  int db = 0;
  int difftot = 0;
  int top = 0;
  while (true){
    // read raw gyro measurements from device
    accel.getAcceleration(&ax, &ay, &az);
    /*
    // display tab-separated accel x/y/z values
    Serial.print("accel:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.println(az);
    Serial.print("\n");*/

    da = abs(az - pz);
    db = abs(az -ppz);
    difftot = da * db;

    /*
    if (da > 12) {
      top = da;
      Serial.println(da);
    }
    //Serial.print("Delta-z: ");
    //Serial.println(da);
    ppz = pz;
    pz = az;*/
    
    
    if(az > 5 || az < -30){
      digitalWrite(12, HIGH);
      //Serial.print("Pling");
      buf[2] = 106;
      Serial.write(buf, 8); // Send keypress
      releaseKey();
      delay(200);
      
      digitalWrite(12, LOW);
    }
    

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  // Release key  
}
