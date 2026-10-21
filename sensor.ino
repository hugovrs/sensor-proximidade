/* Sistema de detecção de presença com HC-SR04
   LED verde: presença detectada
   LED vermelho: ausência de presença
*/

// Definição dos pinos
const int trigPin = 9;
const int echoPin = 10;
const int ledVerde = 6;
const int ledVermelho = 7;

// Distância máxima para detectar presença (em cm)
const int distanciaLimite = 50;

void setup() {
  // Configura os pinos do sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configura os LEDs como saídas
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Inicia a comunicação serial para monitoramento
  Serial.begin(9600);
}

void loop() {
  // Envia um pulso ultrassônico para iniciar a medição
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede o tempo de retorno do eco
  long duracao = pulseIn(echoPin, HIGH, 30000);

  // Converte o tempo em distância (cm)
  float distancia = duracao * 0.0343 / 2;

  // Verifica se houve uma leitura válida
  if (duracao > 0) {
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Se houver um objeto a até 400 cm
    if (distancia <= distanciaLimite) {
      digitalWrite(ledVerde, HIGH);     // Acende o verde
      digitalWrite(ledVermelho, LOW);   // Apaga o vermelho
    } else {
      // Se não houver objeto dentro do limite
      digitalWrite(ledVerde, LOW);      // Apaga o verde
      digitalWrite(ledVermelho, HIGH);  // Acende o vermelho
    }
  } else {
    // Se não houver eco, considera ausência de presença
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  // Pequena pausa entre as medições
  delay(200);
}
