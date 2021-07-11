#include <SoftwareSerial.h>
SoftwareSerial BT(0,1);//rx;tx
#include <Servo.h>
 
#define LANTERNA 11

Servo s; // Variável Servo
int pos; // Posição Servo

//motor_A
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;
  
//motor_B
int IN3 = 6 ;
int IN4 = 7 ;
int velocidadeB = 5;

int velocidadeIni = 255;
int velocidade = 0;

void setup()
{  
//Configuramos os pinos como saídas
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
analogWrite(velocidadeA,velocidadeIni);
analogWrite(velocidadeB,velocidadeIni);
pinMode(LANTERNA, OUTPUT);
digitalWrite(LANTERNA, HIGH);

//Velocidade de comando do módulo Bluetooth
BT.begin(9600);
Serial.begin(9600); 
}

void loop(){
char z;
z = Serial.read();
/*============================================================*/
//DEFINE VELOCIDADE
if(z == 'E'){
  velocidade = 50;
  analogWrite(velocidadeA, velocidade);
  analogWrite(velocidadeB, velocidade);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);
 }

if(z == 'A'){
  velocidade = 100;
  analogWrite(velocidadeA, velocidade);
  analogWrite(velocidadeB, velocidade);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);
 }

 if(z == 'B'){
  velocidade = 150;
  analogWrite(velocidadeA, velocidade);
  analogWrite(velocidadeB, velocidade);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);}

 if(z == 'C'){
  velocidade = 200;
  analogWrite(velocidadeA, velocidade);
  analogWrite(velocidadeB, velocidade);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);}

 if(z == 'D'){
  velocidade = 255;
  analogWrite(velocidadeA, velocidade);
  analogWrite(velocidadeB, velocidade);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);
 }

/*============================================================*/
//DEFINE POSIÇÃO DO MOTOR3 (GARRA)
//RECEBE N,O
//N = 110, O = 176

 if(z == 'N'){
  digitalWrite(LANTERNA, HIGH);
 }
 
 if(z == 'O'){
  digitalWrite(LANTERNA, LOW);
 }

/*PROGRAMA QUE MOVIMENA O MOTOR
** COM CONTROLE DE VELOCIDADE
*///FRENTE - Movimenta os dois motores para frente
if(z == 'X'){
    Serial.println(z);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

if(z == 'x'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}


//RÉ - Movimenta os dois motores para trás
if(z == 'W'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
if(z == 'w'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

//ESQUERDA - Movimenta o robô para a esquerda
//Ou seja, o motor da esquerda para trás
// e o motor da direita para frente
if(z == 'Y'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

if(z == 'y'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

//DIREITA - Movimenta o robô para a direita
//Ou seja, o motor da esquerda para frente
// e o motor da direita para trás
if(z == 'Z'){
    Serial.println(z);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

if(z == 'z'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

//========================================================
//SEGUNDA PARTE
//MOTOR ESQUERDA FRENTE T
if(z == 'T'){
    Serial.println(z);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

if(z == 't'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

//MOTOR ESQUERDA RÉ U
if(z == 'U'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

if(z == 'u'){
    Serial.println(z);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

//MOTOR DIREITA FRENTE V
if(z == 'V'){
    Serial.println(z);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

if(z == 'v'){
    Serial.println(z);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

//MOTOR DIREITA RÉ S
if(z == 'S'){
    Serial.println(z);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

if(z == 's'){
    Serial.println(z);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
