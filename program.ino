#include <LiquidCrystal.h>
#include <Servo.h>

//Initializare pini

const int rs=8, en=9, d4=4, d5=5, d6=6, d7=7;    
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buzzer = A3; 
const int pump = 13;  
int watersensor;
int light;
const int bec = 12;
const int trigPin = 2;
const int echoPin = 3;
int servoPin = 11;
Servo servo;

float duration, distance;

//Setarea fiecarui pin la momenul initial

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); 
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("AQUA SENSE"); 
  delay(800);

  pinMode(watersensor, INPUT); 
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(light, INPUT); 
  pinMode(bec, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(pump, HIGH);
  digitalWrite(buzzer,LOW);
  digitalWrite(bec,LOW);

  servo.attach(servoPin);
  servo.write(0);
}

//Verificarile facute in fiecare secunda

void loop() {
  watersensor = analogRead(A0);
  light = analogRead(A1);
  
  //Afisajul LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NIVEL APA:");
  lcd.setCursor(0, 1);
  lcd.print(watersensor);

//Senzorul de nivel al apei
  if(watersensor<=500)   { 
    lcd.setCursor(11, 0);
    lcd.print("GOL"); 
    digitalWrite(pump, HIGH);
  }
    
  if(watersensor>500){ 
    digitalWrite(pump, LOW);
    lcd.setCursor(10, 0);
    lcd.print("AVARIE");
    tone(buzzer, 3000);
    delay(500);
    noTone(buzzer); 
  }

//Senzorul de luminozitate
  if(light>1000){
    digitalWrite(bec, HIGH);
  }

  if(light<1000){
    digitalWrite(bec, LOW);
  }

//Senzorul ultrasonic de distanta
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  if(distance<15){
    lcd.clear();
    lcd.print("PERICOL IMPACT");
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    servo.write(90);
    delay(3000);
    servo.write(0);
  }

  delay(1000);
}


