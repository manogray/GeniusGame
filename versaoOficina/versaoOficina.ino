#define D4 294
#define G4 392
#define A4 440
#define A5 880

int leds[4] = {4,5,6,7};
int botoes[4] = {13,12,11,10};
int sons[4] = {A5, A4, G4, D4};
int buzzer = 8;

int sequencia[100] = {};

int rodadaAtual = 0;
int passoAtual = 0;

int botaoPress = 0;
boolean perdeu = false;

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

void startTrack(){
  tone(buzzer, sons[0]);
  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);
  delay(500);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);
  delay(500);
  noTone(buzzer);
}

void setup() {
  Serial.begin();

  int i = 0;
  while(i < 4){
    pinMode(led[i],OUTPUT);
    pinMode(botoes[i],INPUT);

    i++;
  }

  pinMode(buzzer,OUTPUT);
  randomSeed(analogRead(0));
}

void proximaRodada(){
  int numero = random(0,4);
  sequencia[rodadaAtual] = numero;
  Serial.println(sequencia[rodadaAtual]);
  rodadaAtual = rodadaAtual + 1;
}

void reproduzirSequencia(){
  int i = 0;
  while(i < rodadaAtual){
    tone(buzzer,sons[sequencia[i]]);
    digitalWrite(leds[sequencia[i]],HIGH);
    delay(400);
    noTone(buzzer);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(400);

    i++;
  }
}

void esperaJogador(){
  int i = 0;
  while(i < rodadaAtual && !perdeu){
    botaoPress = verificaBotao();
    delay(150);
    tone(buzzer, sons[botaoPress]);
    digitalWrite(leds[botaoPress],HIGH);
    delay(600);
    noTone(buzzer);
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











void loop() {
  if(rodadaAtual == 0){
    startTrack();
  }

  proximaRodada();
  reproduzirSequencia();
  esperaJogador();
 
}
