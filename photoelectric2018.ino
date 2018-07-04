// pinout association
const int ledRed = 3;
const int ledGreen = 5;
const int ledBlue = 6;
const int ldr = 2;

char comand;
float ilumADC;
float base;


void setup() {
Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ldr, INPUT);
  explain();
}

void loop() {
if (Serial.available()) {
    comand = Serial.read();
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

void calibration(){
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue, HIGH);
  Serial.println("Starting Calibration....   ");
  Serial.println("Insert the White Sheet");
  delay(2000);
  Serial.println("Acquiring data...");
  delay(2000);
  for (int i = 0; i<=9; i++){
   //Serial.print(i); 
   //Serial.print("\t");
   //Serial.println(base);
   base +=analogRead(ldr);
   }
   base = base / 10;
   base = constrain(base, 0, 1023);
   Serial.println(base);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledBlue, LOW);
   
   }

//active sensor for obtain data
void leitura() {
  ilumADC = 0;
  Serial.println(" Acquiring Data... ");
  Serial.println("Data Read         Reflected Intensity");
  for (int i = 0; i <=9; i++) {
    ilumADC += analogRead(ldr);
    }
    ilumADC = ilumADC / 10;
    ilumADC = constrain(ilumADC,0,base);
    float percent = ilumADC / base;
    Serial.print(ilumADC);
    Serial.print("      ");
    Serial.println(percent, 3);
    delay(10);
  
 explain();
}


// Explanation show in the serial monitor
void explain(){
delay(700);
Serial.println();
Serial.println("Activity for photoelectric effect starting ");
Serial.println("from the measure of light reflectivity");
Serial.println("+++++++++++++++++++++++++++++++++++++++++++");
Serial.println("Choose the options: ");
Serial.println("c = calibration, r = led Red, g = led Green, b= Blue, s = Start Experiment");
}

