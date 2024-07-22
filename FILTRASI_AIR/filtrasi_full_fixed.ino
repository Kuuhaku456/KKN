#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


#define PH_OFFSET -1.00   
float calibration_value = 20.24 - 0.7;
LiquidCrystal_I2C lcd (0x27, 16, 2);
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
// Pin sensor dan LED
const int turbiditySensorPin = 32;
const int pHSensorPin = 33;
const int redLEDPin = 5;
const int yellowLEDPin = 18;
const int greenLEDPin = 19;


// Rentang nilai ADC dan NTU
const int adcMinTurbidity = 0;       // Nilai ADC untuk air sangat jernih
const int adcMaxTurbidity = 4096;    // Nilai ADC untuk air sangat keruh
const int ntuMin = 0;                // Nilai NTU untuk air sangat jernih
const int ntuMax = 3000;             // Nilai NTU untuk air sangat keruh


// Nilai ADC untuk kalibrasi pH sensor
const float pH7_ADC = 1500.0;        // Gantilah dengan nilai ADC aktual untuk pH 7
const float pH4_ADC = 820.0;         // Gantilah dengan nilai ADC aktual untuk pH 4


// Hitung gradien (m) dan intercept (b) untuk pH
// const float m = (7.0 - 4.0) / (pH7_ADC - pH4_ADC);
// const float b = 7.0 - (m * pH7_ADC);


// Rentang pH dan NTU untuk menentukan kondisi air
const float pHMin = 6.5;
const float pHMax = 8.5;
const int ntuThresholdGood = 20;     // Rentang 0-100% untuk kekeruhan baik
const int ntuThresholdSoSo = 66;     // Rentang 0-100% untuk kekeruhan sedang



void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // Mengatur resolusi ADC ke 12 bit


  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);


  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
}


void loop() {
  // Baca nilai sensor turbidity
  int rawTurbidity = analogRead(turbiditySensorPin);
  
  float voltageTurbidity = rawTurbidity * (3.3 / 4095.0); // Konversi ke tegangan
  int ntuValue = map(rawTurbidity, adcMinTurbidity, adcMaxTurbidity, ntuMin, ntuMax);
  // // Konversi nilai NTU ke persentase kejernihan (0% hingga 100%)
  int turbidityPercent = map(ntuValue, ntuMin, ntuMax, 100, 0);
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(33);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*3.3/4095.0/6+0.25; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value


  float phValues =  - phValue + calibration_value;


  // Serial.print("Nilai ADC Turbidity: ");
  // Serial.print(rawTurbidity);
  // Serial.print("\t Tegangan Turbidity: ");
  // Serial.print(voltageTurbidity, 2);
  // Serial.print("V\t Nilai NTU: ");
  // Serial.print(ntuValue);
  Serial.print("\t Persentase Kekeruhan: ");
  Serial.println(turbidityPercent);


  // Serial.print("Nilai ADC pH: ");
  // Serial.print(rawPH);
  Serial.print("\t Tegangan pH: ");
  Serial.print(phValues, 2);


  // Tentukan kondisi air dan nyalakan LED yang sesuai
  if (turbidityPercent <= ntuThresholdGood && phValues >= pHMin && phValues <= pHMax) {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
  } else if (turbidityPercent <= ntuThresholdSoSo || (phValues < pHMin || phValues > pHMax)) {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  } else {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  }


  // Tampilkan nilai NTU dan pH pada LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kekeruhan: ");
  lcd.print(turbidityPercent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(phValues, 2);


  delay(500);
}

