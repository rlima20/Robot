/**
 * Transmissor Módulo NRF24L01
 */
#include <SPI.h>
#include <RF24.h>

#define JOYSTICK_X A0
#define JOYSTICK_y A2
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9, 10);

struct Meujoystick  {
  byte Motor_D;
  byte Motor_E;
};
Meujoystick joystick;

boolean sinal_D = false;
boolean sinal_E = false;

void setup(){
  Serial.begin(9600);  
  delay(1000);
  Serial.println("TRANSMISSOR NRF24L01");
  radio.begin(); 
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop(){
  radio.stopListening();
  TX();
}

void TX(){
  Serial.println("Iniciando transmissão NRF24L01");
  radio.openWritingPipe(pipe);
  int Direcao = analogRead(JOYSTICK_X);
  int Aceleracao = analogRead(JOYSTICK_y);
  int Velocidade_D;   
  int Velocidade_E;
  int auxVE;
  int auxVD;
  int aux_Direcao = map (Direcao, 0, 1023, 0, 510); // Convertendo valores analogicos recebidos do Joystick entre 0 e 1023 para entre 0 e 510 para controle da Direção
  int aux_Velocidade = map (Aceleracao, 0, 1023, 0, 255); // Convertendo valores analogicos recebidos do Joystick entre 0 e 1023 para entre 0 e 255 para controle da Aceleração
  Velocidade_E = aux_Velocidade;
  Velocidade_D = aux_Velocidade;

 if (aux_Direcao < 245) {
    auxVD = 255 - aux_Direcao;
    Velocidade_D = aux_Velocidade + (auxVD / 2); 
    if (Velocidade_D > 253) {
      Velocidade_D = 255;
      Velocidade_E = aux_Velocidade - (auxVD / 2);
      if (Velocidade_E < 24) {
        Velocidade_E = 0;
      }
    }
  }
  else {
    auxVD = 0;
  }

  if (aux_Direcao > 265) {
    auxVE = aux_Direcao - 255;
    Velocidade_E = aux_Velocidade + (auxVE / 2); 
    if (Velocidade_E > 253) {
      Velocidade_E = 255;
      Velocidade_D = aux_Velocidade - (auxVE / 2); 
      if (Velocidade_D < 24) {
        Velocidade_D = 0;
      }
    }
  }
  else {
    auxVE = 0;
  }

  joystick.Motor_D =  Velocidade_D;  
  joystick.Motor_E =  Velocidade_E;

  for(int i = 0; i <= 30; i++){
      radio.write( &joystick, sizeof(joystick) );    
  }
}
