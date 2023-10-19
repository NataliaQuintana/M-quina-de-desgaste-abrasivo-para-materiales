#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>

// Declaración de variables globales
LiquidCrystal_I2C lcd(0x27, 20, 4);
const byte NumMenuP = 5;
int x = 0;
bool motorActivado = false;
unsigned long startTime = millis();
unsigned long motorStartTime = 0;

const int urxPin = A2;
const int press = 2;
bool joystickReleased = true;
const int threshold = 50;

//Motor configuracion 
AccelStepper miMotor(1, 10, 12); 
float pasos = 400.0; //pasos del motor
float t[NumMenuP] = {3600, 1800, 10, 10, 10}; //(tiempo en segundos) 
float v[NumMenuP] = {499, 999, 750, 1000, 10}; //(RPM)
float duration[NumMenuP];
void setup() {
  pinMode(press, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("MAQUINA DE ");
  lcd.setCursor(6, 1);
  lcd.print("DESGASTE");
  lcd.setCursor(6, 2);
  lcd.print("ABRASIVO");
  lcd.setCursor(2, 3);
  lcd.print("PARA  MATERIALES");
  delay(3000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(1, 1);
  lcd.print("MEMORIA DE TITULO");
  lcd.setCursor(2, 2);
  lcd.print("NATALIA QUINTANA");
  delay(2000);
  lcd.clear();
  mostrarMenu();
  for (int i = 0; i < NumMenuP; i++) {
    duration[i] = t[i] * 1000;
  }
}

void loop() {
  int urxValue = analogRead(urxPin);
  
  if (abs(urxValue - 512) > threshold) {
    if (urxValue < 512) {
      if (x > 0 && joystickReleased) {
        x--;
        mostrarMenu();
        joystickReleased = false;
        delay(200);
      }
    } else {
      if (x < NumMenuP - 1 && joystickReleased) {
        x++;
        mostrarMenu();
        joystickReleased = false;
        delay(200);
      }
    }
  } else {
    joystickReleased = true;
  }

  int botonPresionado = digitalRead(press);
  if (botonPresionado == LOW) {
    botonPresionado = HIGH;
   motorActivado = true;
   digitalWrite(4, HIGH);
   if (x == 0) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print(" Ensayo 1 en curso");
    Cancelar(botonPresionado);
    miMotor.setMaxSpeed((v[x]/60)*pasos);
    miMotor.setAcceleration(500);
    miMotor.setSpeed(((v[x]/60)*pasos));
   motorStartTime = millis();
   while (millis() - motorStartTime < duration[x]) {
    miMotor.runSpeed();
    unsigned long tiempoTranscurrido = millis() - motorStartTime;
    if(digitalRead(2)==LOW){
      break;
    }
     //if (tiempoTranscurrido % 600000 == 0) { // Imprimir cada 60000 milisegundos (1 segundo)
     // lcd.setCursor(0, 1);
      //lcd.print("Tiempo:");
      //lcd.print(tiempoTranscurrido / 600000); // Mostrar el tiempo en segundos
      //lcd.print("min       "); // Borrar caracteres extras si el tiempo disminuye
     //}
   }
   miMotor.stop();
    lcd.clear();
    delay(1000);
    digitalWrite(4, LOW);
    unsigned long motorStartTime = 0;
    mostrarMenu();
   } else if (x == 1) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print(" Ensayo 2 en curso");
    Cancelar(botonPresionado);
    miMotor.setMaxSpeed((v[x]/60)*pasos);
    miMotor.setAcceleration(1000);
    miMotor.setSpeed((v[x]/60)*pasos);
   motorStartTime = millis();
  while (millis() - motorStartTime < duration[x]) {
    miMotor.runSpeed();
    unsigned long tiempoTranscurrido = millis() - motorStartTime;
     if (tiempoTranscurrido % 600000 == 0) { // Imprimir cada 60000 milisegundos (1 segundo)
      lcd.setCursor(0, 1);
      lcd.print("Tiempo:");
      lcd.print(tiempoTranscurrido / 600000); // Mostrar el tiempo en segundos
      lcd.print("min       "); // Borrar caracteres extras si el tiempo disminuye
     }
     if(digitalRead(2)==LOW){
      break;
    }
   }
   miMotor.stop();
    lcd.clear();
    delay(1000);
    digitalWrite(4, LOW);
    unsigned long motorStartTime = 0;
    mostrarMenu();
   }else if (x == 2) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print(" Ensayo 3 en curso");
    Cancelar(botonPresionado);
    miMotor.setMaxSpeed((v[x]/60)*pasos);
    miMotor.setAcceleration(100);
    miMotor.setSpeed((v[x]/60)*pasos);
   motorStartTime = millis();
  while (millis() - motorStartTime < duration[x]) {
    miMotor.runSpeed();
    unsigned long tiempoTranscurrido = millis() - motorStartTime;
     if (tiempoTranscurrido % 60000 == 0) { // Imprimir cada 60000 milisegundos (1 segundo)
      lcd.setCursor(0, 1);
      lcd.print("Tiempo:");
      lcd.print(tiempoTranscurrido / 60000); // Mostrar el tiempo en segundos
      lcd.print("min       "); // Borrar caracteres extras si el tiempo disminuye
     }
     if(digitalRead(2)==LOW){
      break;
    }
   }
   miMotor.stop();
    lcd.clear();
    delay(1000);
    digitalWrite(4, LOW);
    unsigned long motorStartTime = 0;
    mostrarMenu();
   }else if (x == 3) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print(" Ensayo 4 en curso");
    Cancelar(botonPresionado);
    miMotor.setMaxSpeed((v[x]/60)*pasos);
    miMotor.setAcceleration(100);
    miMotor.setSpeed((v[x]/60)*pasos);
   motorStartTime = millis();
  while (millis() - motorStartTime < duration[x]) {
    miMotor.runSpeed();
    unsigned long tiempoTranscurrido = millis() - motorStartTime;
     if (tiempoTranscurrido % 60000 == 0) { // Imprimir cada 60000 milisegundos (1 segundo)
      lcd.setCursor(0, 1);
      lcd.print("Tiempo:");
      lcd.print(tiempoTranscurrido / 60000); // Mostrar el tiempo en segundos
      lcd.print("min       "); // Borrar caracteres extras si el tiempo disminuye
     }
     if(digitalRead(2)==LOW){
      break;
    }
  }
   
   miMotor.stop();
    lcd.clear();
    delay(1000);
    digitalWrite(4, LOW);
    unsigned long motorStartTime = 0;
    mostrarMenu();
   }else if (x == 4) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print(" Ensayo 4 en curso");
    Cancelar(botonPresionado);
    miMotor.setMaxSpeed((v[x]/60)*pasos);
    miMotor.setAcceleration(100);
    miMotor.setSpeed((v[x]/60)*pasos);
   motorStartTime = millis();
  while (millis() - motorStartTime < duration[x]) {
    miMotor.runSpeed();
    unsigned long tiempoTranscurrido = millis() - motorStartTime;
     if (tiempoTranscurrido % 60000 == 0) { // Imprimir cada 60000 milisegundos (1 segundo)
      lcd.setCursor(0, 1);
      lcd.print("Tiempo:");
      lcd.print(tiempoTranscurrido / 60000); // Mostrar el tiempo en segundos
      lcd.print("min       "); // Borrar caracteres extras si el tiempo disminuye
     }
     if(digitalRead(2)==LOW){
      break;
    }
  }
   
   miMotor.stop();
    lcd.clear();
    delay(1000);
    digitalWrite(4, LOW);
    unsigned long motorStartTime = 0;
    mostrarMenu();
   }
  }
}

void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DETERMINA ENSAYO:");
  lcd.setCursor(0, 1);
  lcd.print("ENSAYO");
  lcd.setCursor(7, 1);
  lcd.print(x+1);
  lcd.setCursor(0, 2);
  lcd.print("Velocidad:");
  lcd.setCursor(10, 2);
  lcd.print(v[x]);
  lcd.setCursor(15, 2);
  lcd.print("[rpm]");
  lcd.setCursor(0, 3);
  lcd.print("Tiempo:");
  lcd.setCursor(10, 3);
  lcd.print(t[x]);
  lcd.setCursor(15, 3);
  lcd.print("[s]");
}

void Cancelar(int botonPresionado) {
  lcd.setCursor(0, 3);
  lcd.print("Press para cancelar");
  delay(1000);
} 
