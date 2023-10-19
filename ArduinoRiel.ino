const int directionPin = 8;   // Pin de dirección
const int pulsePin = 9;       // Pin de pulso
const int urxPin = A2;        // Pin analógico para el eje X del joystick
const int aux5VPin = 6;       // Pin PWM para generar 5V auxiliar
const int enablePin = 12;     // Pin para habilitar o deshabilitar el motor
const int threshold = 512;    // Umbral para detectar movimiento en el eje X
const int stopThreshold = 100; // Umbral para detener el motor 

void setup() {
  pinMode(directionPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);
  pinMode(4, INPUT); 
  pinMode(urxPin, INPUT);
  pinMode(aux5VPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(2, INPUT); // Configura el pin 2 como entrada sin resistencia pull-up
  analogWrite(aux5VPin, 255); // Generar 5V en el pin auxiliar
  digitalWrite(directionPin, LOW); // Establece la dirección inicial
  digitalWrite(enablePin, LOW); // Desactiva el motor por defecto
}

void loop() {
  int urxValue = analogRead(urxPin);
  int estado = digitalRead(2); // Lee el estado del pin 2
  int enableJoy = digitalRead(4); // Lee estado del pin 4
    if (estado == LOW && urxValue > 600 && enableJoy == LOW) {
      digitalWrite(enablePin, HIGH); // Activa el motor
      digitalWrite(directionPin, HIGH); // Cambia la dirección si el joystick se mueve hacia arriba
    } else if (urxValue < 400 && enableJoy == LOW) {
      digitalWrite(enablePin, HIGH); // Activa el motor
      digitalWrite(directionPin, LOW);  // Cambia la dirección si el joystick se mueve hacia abajo (negativo)
    } else {
      digitalWrite(enablePin, LOW); // Desactiva el motor si el joystick está en reposo
    }
  // Generar el pulso para el motor
  digitalWrite(pulsePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pulsePin, LOW);
  delayMicroseconds(1000); // Ajusta este retardo según sea necesario
}

