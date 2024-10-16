/* Programa: Robô Autônomo */

/* Inclui a Biblioteca AFMotor */
#include <AFMotor.h>

/* Inclui a Biblioteca Ultrasonic */
#include <Ultrasonic.h>

/* Define os pinos para o sensor ultrassônico */
int pino_Trig = 10;
int pino_Echo = 9;

/* Define a potência dos motores: 0 a 255. */
int potencia = 255;

/* Define as portas da Motor Shield que estão sendo utilizadas. */
AF_DCMotor Motor_Esquerda(3);  // Motor conectado na porta M3
AF_DCMotor Motor_Direita(2);   // Motor conectado na porta M2

/* Adiciona um terceiro motor que ficará sempre ligado */
AF_DCMotor Motor_Terceiro(4);  // Motor conectado na porta M4

/* Define o nome da função que realizará a medida da distância. */
Ultrasonic Sensor(pino_Trig, pino_Echo);

/* Variável para armazenar a distância. */
int distancia;

void setup() {
  /* Inicia com os motores parados */
  Motor_Esquerda.run(RELEASE);
  Motor_Direita.run(RELEASE);
  
  /* Configura o terceiro motor para ficar sempre ligado */
  Motor_Terceiro.setSpeed(200);  // Define a velocidade máxima
  Motor_Terceiro.run(FORWARD);   // Faz o motor girar para frente

  /* Inicia a comunicação serial (opcional, para debug) */
  Serial.begin(9600);

  /* Espera 3 segundos para iniciar o robô */
  delay(3000);
}

/* Função para mover o robô para frente */
void frente(int potencia) {
  Motor_Esquerda.setSpeed(potencia);
  Motor_Direita.setSpeed(potencia);
  Motor_Esquerda.run(FORWARD);
  Motor_Direita.run(FORWARD);
}

/* Função para realizar uma manobra */
void manobra(int potencia) {
  /* Função que realiza a manobra com 60% da potência dos motores. */
  Motor_Esquerda.setSpeed(potencia * 0.6);
  Motor_Direita.setSpeed(potencia * 0.6);

  /* Para os motores por um momento */
  Motor_Esquerda.run(RELEASE);
  Motor_Direita.run(RELEASE);
  delay(500);

  /* Gira o robô (um motor para frente e outro para trás) */
  Motor_Esquerda.run(FORWARD);
  Motor_Direita.run(BACKWARD);
  delay(1000);

  /* Para os motores novamente */
  Motor_Esquerda.run(RELEASE);
  Motor_Direita.run(RELEASE);
  delay(500);
}

/* Função principal que será executada continuamente */
void loop() {
  /* Medir a distância do obstáculo */
  distancia = Sensor.distanceRead();

  /* Exibe a distância no monitor serial (para depuração) */
  Serial.print("Distancia: ");
  Serial.println(distancia);

  /* Se a distância for maior que 20 cm, o robô anda para frente */
  if (distancia > 20) {
    frente(potencia);
  } 
  /* Caso contrário, realiza uma manobra */
  else {
    manobra(potencia);
  }

  /* Pequena pausa entre as medições */
  delay(100);
}
