// include Libraries
#include <LiquidCrystal_I2C.h> // Library for LCD-I2C Board
#include <DFRobot_DHT11.h> // Library for DHT Sensor

// Initialize DHT data pin
DFRobot_DHT11 DHT;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

// Declare all pins and variables
int DHT11_PIN = 7; // DHT11 Sensor Pin
float Hum;  //Stores humidity value
float Temp; //Stores temperature value

int SoilSensorPin = A0; // Pin for soil sensor
int SoilSensorValue; // variable to store the value coming from the sensor

int Water_Sensor = A1;  // Pin for water level sensor
int water_val; // Variable to store water sensor readings
int Buzzer_Pin = 8; // Arduino pin connected to Buzzer's pin

int LDR_Pin = 5;
int LDR = 0;
int LED = 2;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  Serial.begin(9600);
  
 // lcd.begin(16, 2);
  pinMode(SoilSensorPin, INPUT);
  pinMode(LDR_Pin, INPUT);
  pinMode(Water_Sensor, INPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  // DHT Sensor
  DHT.read(DHT11_PIN);
  Temp = DHT.temperature;
  Hum = DHT.humidity;

  // Soil Sensor
  SoilSensorValue = analogRead(SoilSensorPin);

  // Water Level Sensor
  water_val = analogRead(Water_Sensor); // read input value
   
   // LDR reading 
   LDR = digitalRead(LDR_Pin); 

  // Water Sensor Response
  if(water_val >250)  
  {  
    tone(Buzzer_Pin, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
    delay(100);
  } 
  else{
    noTone(Buzzer_Pin); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
    delay(100);
  }
  if(SoilSensorValue > 800 && Hum < 1000){
    digitalWrite(3,LOW);
  }
  else{
    digitalWrite(3,HIGH);
  }
   // LDR Sensor Response
  if(LDR == 1 )  
  {  
   digitalWrite(LED,HIGH); // LED ON  
   delay(2000);  
  }  
  else  
  {  
   digitalWrite(LED,LOW); // LED OFF 
  } 

 //Display readings on serial monitor
  Serial.print("Temperature: ");
  Serial.println(Temp);
  Serial.print("Humidity: ");
  Serial.println(Hum);
  Serial.print("Moisture Sensor Value: ");
  Serial.println(SoilSensorValue); 
  Serial.print("Water Level: ");
  Serial.println(water_val);

  Serial.println("**************************************************");
  
  
 // Display readings on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Temp);
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(Hum);
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Moisture: ");
  //lcd.setCursor(12,0);
  lcd.print(SoilSensorValue);
  lcd.setCursor(0,1);
  lcd.print("Water Level: ");
  lcd.print(water_val);
  delay(2000);
  lcd.clear();
  
} 
