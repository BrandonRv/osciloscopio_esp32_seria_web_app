#define LED_PIN 17       // Pin para el LED

unsigned long previousMillisRead = 0;  // Para controlar el tiempo de lectura del serial
unsigned long previousMillisBlink = 0; // Para controlar el tiempo de parpadeo del LED

const long intervalRead = 50;    // Intervalo para la lectura del estado del serial (50 ms)
const long intervalBlink = 500;  // Intervalo para el parpadeo del LED (500 ms)

bool ledBlinkState = LOW; // Estado actual del LED para parpadeo

void setup() {
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);

  // Inicializar la comunicación serial
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  // Tarea 1: Lectura del puerto serial cada 50 ms
  if (currentMillis - previousMillisRead >= intervalRead) {
    previousMillisRead = currentMillis;

    if (Serial.available() > 0) {
      // Leer el dato del serial (aunque no haremos nada específico con el dato recibido)
      char incomingByte = Serial.read();

      // Enviar el estado del LED al puerto serial
      if (ledBlinkState == HIGH) {
        Serial.println("Encendido");
      } else {
        Serial.println("Apagado");
      }
    }
  }
    if (currentMillis - previousMillisBlink >= intervalBlink) {
    previousMillisBlink = currentMillis;

    // Alternar el estado del LED
    ledBlinkState = !ledBlinkState;
    digitalWrite(LED_PIN, ledBlinkState);
  }
}
