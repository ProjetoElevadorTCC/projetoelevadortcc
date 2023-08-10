#include <Arduino.h>

// Pinos de controle do movimento do elevador
int motorUpPin = 2;
int motorDownPin = 3;

// Pinos dos sensores indutivos para cada andar
int sensorFloor1 = 4;
int sensorFloor2 = 5;
int sensorFloor3 = 6;

// Pino do sensor de presença no elevador
int sensorPresence = 7;

// Pinos dos botões em cada andar
int buttonFloor1 = 8;
int buttonFloor2 = 9;
int buttonFloor3 = 10;

void setup() {
  Serial.begin(9600);

  // Configura os pinos de controle do movimento como saídas
  pinMode(motorUpPin, OUTPUT);
  pinMode(motorDownPin, OUTPUT);

  // Inicialmente, os motores estão desligados
  digitalWrite(motorUpPin, LOW);
  digitalWrite(motorDownPin, LOW);

  // Configura os pinos dos sensores indutivos como entradas
  pinMode(sensorFloor1, INPUT);
  pinMode(sensorFloor2, INPUT);
  pinMode(sensorFloor3, INPUT);

  // Configura o pino do sensor de presença como entrada
  pinMode(sensorPresence, INPUT);

  // Configura os pinos dos botões como entradas
  pinMode(buttonFloor1, INPUT_PULLUP);
  pinMode(buttonFloor2, INPUT_PULLUP);
  pinMode(buttonFloor3, INPUT_PULLUP);
}

void loop() {
  // Verifica o sensor de presença no elevador
  int presence = digitalRead(sensorPresence);

  // Se não houver ninguém no elevador, desliga a Alexa (LED no display)
  if (presence == LOW) {
    // Código para desativar a Alexa (opcional)
  } else {
    // Se houver alguém no elevador, libera a Alexa para funcionar
    if (Serial.available() > 0) {
      char command = Serial.read();
      if (command == '1') {
        moveUp();
      } else if (command == '2') {
        moveDown();
      }
    }
  }

  // Verifica os botões em cada andar para chamar o elevador
  if (digitalRead(buttonFloor1) == LOW) {
    if (current_floor != 1) {
      target_floor = 1;
      move_elevator();
    }
  } else if (digitalRead(buttonFloor2) == LOW) {
    if (current_floor != 2) {
      target_floor = 2;
      move_elevator();
    }
  } else if (digitalRead(buttonFloor3) == LOW) {
    if (current_floor != 3) {
      target_floor = 3;
      move_elevator();
    }
  }
}

void moveUp() {
  // Implementação do movimento para cima
}

void moveDown() {
  // Implementação do movimento para baixo
}

void move_elevator() {
  // Implementação do movimento para o andar de destino,
  // considerando paradas intermediárias se necessário
}
