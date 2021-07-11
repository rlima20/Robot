
/*                         ###############################
                           #      PROJETO AEROINO        #
                           #  TUTORIAL FAÇA VOCÊ MESMO!  #
                           ###############################
                         AVIÃO DE CONTROLE REMOTO COM ARDUINO
                         
   ****************************CODIGO FONTE DO TRANSMISSOR****************************

   Desenvolvido por Aldeir de Souza Moreira - aldeirsm@gmail.com
   2015 - Todos os direitos reservados

***Siga atentamente as instruções do Tutorial para a montagem do hardware
*/

// Importando Bibliotecas
#include <SPI.h>
#include <RF24.h>

// Declarando constantes joystick_x como sendo porta analogica A0 e joystick_y como sendo porta analogica A2
#define JOYSTICK_X A3
#define JOYSTICK_y A5

//Configurando endereço de comunicação entre os MÓDULOS. "LL" no final do endereço define a constante como sendo do tipo "LongLong".
const uint64_t pipe = 0xE8E8F0F0E1LL;

//Instanciando uma classe RF24 e informando que os pinos CE e CSN do Módulo NRF24L01 estão ligados aos pinos digitais 9 e 10 do Arduino
RF24 radio(9, 10);

//Criando uma estrutura de dados que contem duas variaveis do tipo byte
struct Meujoystick  {
  byte Motor_D;
  byte Motor_E;
};
//Declarando uma Variável do tipo Meujoystick
Meujoystick joystick;

// Declarando variaveis do tipo booleana e iniciando com o valor logico false
boolean sinal_D = false;
boolean sinal_E = false;

void setup()
{
  Serial.begin(9600);   //configurando a comunicação via porta serial à uma velocidade de 9600bps(baud).

  delay(1000);// aguardando um tempo em milissegundos.

  Serial.println("Codigo TRANSMISSOR Nrf24L01");   // Imprimindo na tela via serial o texto entre aspas

  radio.begin();   //Inicialidando o MÓDULO RF24l01 para comunicação.

  radio.setAutoAck(false);    // Desativando pacotes ACK (Pacote de Reconhecimento de Mensagem)
  radio.setDataRate(RF24_250KBPS);    // Configurando Módulo para iperar em uma taxa de 250kbps


  // declarando o modo de operação dos pinos digitais 2 e 6 e inicializando-os com nivel baixo
  pinMode(2, INPUT);
  pinMode(3, INPUT);

}

void loop()
{

  radio.stopListening();  // Interrompendo mecanismos de recpção "escuta" do Módulo
  TX();    // Chamando a função TX responsavel pela transmissão dos dados
}



void TX()
{
  // Serial.println("Iniciando TRANSMICAO Nrf24L01"); // Imprimindo na tela via serial o texto entre aspas

  radio.openWritingPipe(pipe);   // abrindo o meio de comunicação entre transmissor e recptor com o mesmo endeço definido no ínicio do programa

  int Direcao = analogRead(JOYSTICK_X); // Variável Direção sendo declarada e recebendo os valores analogicos do potenciometro Eixo X do JoyStick B

  int Aceleracao = analogRead(JOYSTICK_y);  // Variável Aceleração sendo declarada e recebendo os valores analogicos do potenciometro Eixo Y do JoyStick A

  // Declarando demais variaveis
  int Velocidade_D;   // Armazena variaveis responsaveis por controlar o motor Direito
  int Velocidade_E;   // Armazena variaveis responsaveis por controlar o motor Esquerdo
  int auxVE;   // Variável temporaria que auxilia no calculo da proporção de velocidade do motor Esquerdo para fazer curvas
  int auxVD;   // Variável temporaria que auxilia no calculo da proporção de velocidade do motor Direito para fazer curvas


  int aux_Direcao = map (Direcao, 0, 1023, 0, 510); // Convertendo valores analogicos recebidos do Joystick entre 0 e 1023 para entre 0 e 510 para controle da Direção


  int aux_Velocidade = map (Aceleracao, 0, 1023, 0, 255); // Convertendo valores analogicos recebidos do Joystick entre 0 e 1023 para entre 0 e 255 para controle da Aceleração

  Velocidade_E = aux_Velocidade;
  Velocidade_D = aux_Velocidade;

  // Controlando proporção da Aceleração do motor Direito e Esquerdo de acordo com a movimentação do JoyStick para controle da direção
  if (aux_Direcao < 245) {

    auxVD = 255 - aux_Direcao;

    Velocidade_D = aux_Velocidade + (auxVD / 2); // Aumenta aceleração do motor Direito  ***A divisão por 2 é para deixar as curvas mais suaves
    if (Velocidade_D > 253) {
      Velocidade_D = 255;

      Velocidade_E = aux_Velocidade - (auxVD / 2); // Diminui aceleração do motor Esquerdo
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

    Velocidade_E = aux_Velocidade + (auxVE / 2); // Aumenta aceleração do motor Esquerdo
    if (Velocidade_E > 253) {
      Velocidade_E = 255;

      Velocidade_D = aux_Velocidade - (auxVE / 2); // Diminui aceleração do motor Direito
      if (Velocidade_D < 24) {
        Velocidade_D = 0;
      }
    }

  }
  else {
    auxVE = 0;
  }

  // As variaveis joystick.Motor_D e joystick.Motor_E pertencentes a struct joystick recebem os valores de aceleração conjunta e individual (direção) para serem transmitidos ao receptor
  joystick.Motor_D =  Velocidade_D;  
  joystick.Motor_E =  Velocidade_E;

    Serial.print("Velocidade esquerdo: ");
    Serial.print(Velocidade_E);
    Serial.print(" | Velocidade direito: ");
    Serial.println(Velocidade_D);


// Transmitindo variaveis, este comando foi repetido 30 vezes para corrigir erros que possam ocorer na transmição desta forma consigui-se um maior alcance com maior confiabilidade
// Esta repetição só é necessária, pois os pacotes ACK (Pacote de Reconhecimento de Mensagem) foram desativados, caso eles sejam ativados não será necessário repetir este comando
// Um laço for() pode subistiuira as 30 repetições, que estão desta forma para melhorar o entendimento dos iniciantes. 

  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );
  radio.write( &joystick, sizeof(joystick) );

}

// FIM
