#include <Arduino.h>

int vermelhoLed = 7;
int verdeLed = 6;
int azulLed = 5;
int amareloLed = 4;

int vermelhoBto = 10;
int verdeBto = 11;
int azulBto = 12;
int amareloBto = 13;

int sequencia[100] = {};

int rodadaAtual = 0;
int passoAtual = 0;

int botaoPress = 0;
int gameOver = false;

void setup() {
  pinMode(vermelhoLed, OUTPUT);
  pinMode(verdeLed, OUTPUT);
  pinMode(azulLed, OUTPUT);
  pinMode(amareloLed, OUTPUT);

  pinMode(vermelhoBto, INPUT);
  pinMode(verdeBto, INPUT);
  pinMode(azulBto, INPUT);
  pinMode(amareloBto, INPUT);

  randomSeed(analogRead(0));
}

void loop() {

  if(gameOver) {
    sequencia[100] = {};
    rodadaAtual = 0;
    passoAtual = 0;
    gameOver = false;

  }

  proximaRodada();
  reproduzirSequencia();
  esperaJogada();
  
}

void proximaRodada(){
  int numero = random(0,4);
}

void reproduzirSequencia(){

}

void esperaJogada(){

}