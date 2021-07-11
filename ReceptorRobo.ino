/**o
 * Projeto Robô com módulo de rádio frequência
 * Receptor Módulo NRF24L01
 */
#include <SPI.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10); 

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

struct Meujoystick  {
  byte Motor_D;
  byte Motor_E;
};
Meujoystick joystick;

byte MotorDireito = 0;
byte MotorEsquerdo = 0;
int Temp = 0;

void setup(){
  Serial.begin(9600);
  delay(1000);
  Serial.println("Codigo RECEPTOR Nrf24L01");
  
  radio.begin(); 
  radio.setAutoAck(false);   
  radio.setDataRate(RF24_250KBPS);  
  radio.startListening();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){    
  radio.startListening();
  RX();
}

void RX(){
  Serial.println(" Iniciando Recepcao Nrf24L01");
  radio.openReadingPipe(1,pipe);

  if ( radio.available() ){
    boolean sinal = false;    
    while (!sinal){
      sinal = radio.read( &joystick, sizeof(joystick) ); 
      movimentaRobo();
      //debbug();
    }
  } else{   
   semSinal();
  }
 }

 void movimentaRobo(){
      MotorEsquerdo = joystick.Motor_E;
      MotorDireito = joystick.Motor_D;

      if((MotorEsquerdo == 125)&&(MotorDireito == 125)){
        parado();
      }else if((MotorEsquerdo == 0)&&(MotorDireito == 0)){
        re();
      }else if((MotorEsquerdo == 255)&&(MotorDireito == 255)){
        frente();      
      }else if((MotorEsquerdo == 252)&&(MotorDireito == 125)){
        direita();
      }else if((MotorEsquerdo == 125)&&(MotorDireito == 252)){
        esquerda();
      }else if((MotorEsquerdo == 128)&&(MotorDireito == 255)){
        motor_direito_pra_frente();
      }else if((MotorEsquerdo == 255)&&(MotorDireito == 128)){
        motor_esquerdo_pra_frente();
      }else if((MotorEsquerdo == 0)&&(MotorDireito == 127)){
        motor_direito_pra_tras();
      }else if((MotorEsquerdo == 127)&&(MotorDireito == 0)){
        motor_esquerdo_pra_tras();
      }
 }
 
 void semSinal(){
    radio.stopListening();
    Serial.println("Sem Sinal do Radio");
    Temp = Temp ++;
    if (Temp > 50){
      parado();
    }
 }
 
 void debbug(){
      Serial.print("Motor Esquerdo: "); 
      Serial.print(MotorEsquerdo); 
      Serial.print(" | Motor Direito: "); 
      Serial.print(MotorDireito);
      Serial.print("   -   ");
 }

  void parado(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("Esquerdo parado | Direito parado");
 }

 void frente(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);  
    Serial.println("Esquerdo frente | Direito frente");
 }
 
 void re(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Esquerdo para trás | Direito para trás");
 }

 void esquerda(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);  
    Serial.println("Esquerdo para trás | Direito para frente");
 }

 void direita(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Esquerdo para frente | Direito para trás");
 }

 void motor_direito_pra_frente(){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Esquerdo parado | Direito para frente");    
 }

 void motor_esquerdo_pra_frente(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);  
    Serial.println("Esquerdo para frente | Direito parado");  
 }

  void motor_direito_pra_tras(){
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);  
    Serial.println("Esquerdo parado | Direito para trás");  
 }

 void motor_esquerdo_pra_tras(){
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);    
    Serial.println("Esquerdo para trás | Direito parado");
 }
