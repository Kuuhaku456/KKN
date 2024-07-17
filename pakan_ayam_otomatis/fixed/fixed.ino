//turn on an LED based on distance measured by
//ultrasonic sensor
  // Include the Servo library 
  #include <Servo.h> 
  #include <LiquidCrystal_I2C.h>
  #include  <Wire.h>
  // Declare the Servo pin 
  int servoPin = 3; 
  int pinled=8;
  int pinleds=10;
  const  int trigger=6;
  const  int echo=7;
  float  distance;
  float dist_inches;
  Servo Servo1;
  LiquidCrystal_I2C lcd(0x27,  16, 2);

  void setup(){
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(pinled,OUTPUT);
    pinMode(pinleds,OUTPUT);
    Servo1.attach(servoPin);
  }
  
  void loop(){
    // Trigger the sensor to start measurement
    // Set up trigger
    digitalWrite(trigger,LOW);
    delayMicroseconds(5);
    
    //Start Measurement
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    
    // Acquire and convert to inches
    distance=pulseIn(echo,HIGH);
    distance=distance*0.0001657;
    dist_inches=distance*39.37;
    Serial.print(dist_inches);
    Serial.print(" cm\n");
    if(dist_inches < 6){ //if distance of object is less than 6 inches
      lcd.setCursor(0,0);
      lcd.print("Pakan dibuka!");
      digitalWrite(pinleds,HIGH);
      digitalWrite(pinled,LOW);
      Servo1.write(180); 
      delay(3000);
      lcd.clear();
    }
    else if ( dist_inches >= 6 ){ 
      digitalWrite(pinleds,LOW);
      digitalWrite(pinled,HIGH);
      
      Servo1.write(90);
    }
    delay(100);
  }