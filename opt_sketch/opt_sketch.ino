#include "HX711.h"

// Define HX711 sensor settings
#define calibration_factor 50 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define HX711_DOUT  4
#define HX711_CLK  5

// Define stepper motor:
#define dirPin 2
#define stepPin 3



// User defined Sketch Variables
int stepperDelay = 10;               //Set the stepper duration (ms)
float maxAllowedForce = 99999;      //Sets a max allowed force for your system
bool useMaxAllowedForce = false;



//Set to true to start testing
bool    idle = true;

// Test variables
int     mode = 1;
bool    stepDirection = 0;
float   measuringIntervall = 1;
float   maxForce = 500;
float   timeAtMaxForce = 0;
float   restForce = 0;
float   timeAtRestForce = 0;
int     repeatsDone = 0;           

//Other variables
bool restTime;


long tareValue;

int testRepeats = 0;

long currentMillis =  millis();
long lastMeasuredMillis = 0;
long lastLoadValue = 0;

HX711 scale;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  scale.begin(HX711_DOUT, HX711_CLK); 
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch

  tareValue = scale.get_units();
  scale.tare(); //Sets the current reading as the offset, "tearing" the scale to 0
 
  
}

void loop() {
  if (!idle){
    //Idle read mode
    if (mode == 0){
      while(true){
       digitalWrite(stepPin, LOW);
       delayMicroseconds(stepperDelay);
        
       printMeasure();
      }
    }
    
    //Default test mode
    if (mode == 1){
      while(true){
       digitalWrite(dirPin, stepDirection);
       digitalWrite(stepPin, HIGH);
       delayMicroseconds(stepperDelay);
       digitalWrite(stepPin, LOW);
       delayMicroseconds(stepperDelay);
  
       
        printMeasure();
      }
    }

    //Test mode with a max allowed force
    if (mode == 2){
      while(true){
       digitalWrite(dirPin, stepDirection);
       digitalWrite(stepPin, HIGH);
       delayMicroseconds(stepperDelay);
       digitalWrite(stepPin, LOW);
       delayMicroseconds(stepperDelay);
  
        
       printMeasure();
       if (lastLoadValue >= maxForce){
        Serial.println("Max force reached, end of testing");
        while(1);
       }
     }
  }
    
  


  //Test mode with repeats
    if (mode == 3){
      while(true)
       restTime = false;
       if (!restTime){
         digitalWrite(dirPin, stepDirection);
         digitalWrite(stepPin, HIGH);
         delayMicroseconds(stepperDelay);
         digitalWrite(stepPin, LOW);
          
         printMeasure();
         
         if (maxForce <= scale.get_units()){
            repeatsDone ++;
            delayMicroseconds(timeAtMaxForce);
             
            printMeasure();
            restTime = true;
         }
       }
       if (restTime){
        while (restForce <= scale.get_units()) {
           digitalWrite(dirPin, !stepDirection);
           digitalWrite(stepPin, HIGH);
           delayMicroseconds(stepperDelay);
           digitalWrite(stepPin, LOW);
        }
        delayMicroseconds(timeAtRestForce);
        restTime = false;
       }
    }
    if(useMaxAllowedForce && maxAllowedForce >= lastLoadValue){
      Serial.println("Max allowed force reached, please reset arduino");
      while(1){
        
      }
    }
  }
}


//Prints the reading every interval
void printMeasure(){
  currentMillis =  millis();
  if (currentMillis - lastMeasuredMillis >= measuringIntervall * 1000) {
    lastLoadValue = scale.get_units();
    delay(3);
    Serial.println(lastLoadValue, 2);
    delay(3);
    lastMeasuredMillis = currentMillis;
    
  }
}
