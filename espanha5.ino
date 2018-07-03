// it's necessary for average calculus
#define NUMREADINGS 50
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;

//calibration variables
int calreadings[100];
int caltotal = 0;
int calaverage = 0;
float base = 1;

// pinout association
const int ledRed = 3;
const int ledGreen = 5;
const int ledBlue = 6;
const int ldr = A0;
int valueLdr = 0;
char comand;

// start code of this sketch
void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ldr, INPUT);
  Serial.begin(9600);
  delay(125);
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;
  delay(500);
  explain();
}

void loop() {
  if (Serial.available()) {
    comand = Serial.read();
    Serial.flush();

    if (comand == 'r') {
      digitalWrite(ledRed, !digitalRead(ledRed));
    }
    if (comand == 'g') {
      digitalWrite(ledGreen, !digitalRead(ledGreen));
    }
    if (comand == 'b') {
      digitalWrite(ledBlue, !digitalRead(ledBlue));
    }
    if (comand == 'c') {
      calibration();
    }
    else if (comand == 's') {
      leitura();
    }

  }
}

//Explanation
void explain(){
delay(700);
Serial.println();
Serial.println("Activity for photoelectric effect starting ");
Serial.println("from the measure of light reflectivity");
Serial.println("+++++++++++++++++++++++++++++++++++++++++++");
Serial.println("Choose the options: ");
Serial.println("c = calibration, r = led Red, g = led Green, b= Blue");
}

//sensor calibration
void calibration() {
  Serial.println("Calibration...   ");
  Serial.println("Insert the white sheet...");
  delay(1000);
  Serial.println("Acquiring Data...");
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledBlue, HIGH);
  
  for (int u = 0; u <= 10; u++) {
    caltotal -= calreadings[index];
    calreadings[index] = analogRead(ldr);
    caltotal += readings[index];
    index = (index + 1);
    if (index >= 100)
      index = 0;
    base = total / 100;

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);
  }
    Serial.print(base);
    Serial.print(" ....Done");
explain();
 }
//active sensor for obtain data
void leitura() {
  Serial.println(" Acquiring Data... ");
  Serial.println("Data         Reflected Intensity");
  for (int i = 0; i <= 10; i++) {
    total -= readings[index];
    readings[index] = analogRead(ldr);
    total += readings[index];
    index = (index + 1);
    if (index >= NUMREADINGS)
      index = 0;
    average = total / NUMREADINGS;
    float percent = ( average / base)*100;
    Serial.print(i);
    Serial.print("\t");
    Serial.print(average);
    Serial.print("\t");
    Serial.println(percent);
    delay(10);
  }
 explain();
}
