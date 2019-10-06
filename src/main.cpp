#include <Arduino.h>

int leds[4] = {4,5,6,7};
int botoes[4] = {13,12,11,10};

int sequencia[100] = {};

int rodadaAtual = 0;
int passoAtual = 0;

int botaoPress = 0;
boolean perdeu = false;

void reproduzirSequencia(){
  int i = 0;
  while(i < rodadaAtual){
    delay(400);
    digitalWrite(leds[sequencia[i]],HIGH);
    delay(400);
    digitalWrite(leds[sequencia[i]],LOW);
    delay(400);

    i++;
  }

}

void proximaRodada(){
  int numero = random(0,4);
  sequencia[rodadaAtual] = numero;
  Serial.println(sequencia[rodadaAtual]);
  rodadaAtual = rodadaAtual + 1;
}

void gameOver(){

  int i = 0;
  while(i < 4){
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
    i++;
  }

  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);
  delay(2000);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);

  sequencia[100] = {};
  rodadaAtual = 0;
  passoAtual = 0;
  perdeu = true;
}

int verificaBotao(){
  int i = 0;
  while(true){
    if(digitalRead(botoes[i]) == HIGH){
      return i;
    }

    i++;
    if(i == 4) {
      i = 0;
    }
  }
}

void esperaJogador(){
  int i = 0;
  while(i < rodadaAtual && !perdeu){
    botaoPress = verificaBotao();
    delay(150);
    digitalWrite(leds[botaoPress],HIGH);
    delay(600);
    digitalWrite(leds[botaoPress],LOW);

    if(sequencia[passoAtual] != botaoPress){
      gameOver();
    }

    passoAtual++;
    i++;
  }

  perdeu = false;
  passoAtual = 0;
}

void setup() {

  Serial.begin(9600);

  int i = 0;
  while(i < 4){
    pinMode(leds[i],OUTPUT);
    pinMode(botoes[i],INPUT);

    i++;
  }

  randomSeed(analogRead(0));
}

void loop() {

  proximaRodada();
  reproduzirSequencia();
  esperaJogador();
  
}